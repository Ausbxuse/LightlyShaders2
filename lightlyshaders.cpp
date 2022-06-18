/*
 *   Copyright © 2015 Robert Metsäranta <therealestrob@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; see the file COPYING.  if not, write to
 *   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *   Boston, MA 02110-1301, USA.
 */

#include "dbus.h"
#include "lightlyshaders.h"
#include <QPainter>
#include <QPainterPath>
#include <QImage>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <kwinglplatform.h>
#include <kwinglutils.h>
#include <QMatrix4x4>
#include <KConfigGroup>
#include <QtDBus/QDBusConnection>
#include <QRegularExpression>

namespace KWin {

#ifndef KWIN_PLUGIN_FACTORY_NAME
KWIN_EFFECT_FACTORY_SUPPORTED_ENABLED(LightlyShadersFactory, LightlyShadersEffect, "lightlyshaders.json", return LightlyShadersEffect::supported();, return LightlyShadersEffect::enabledByDefault();)
#else
KWIN_EFFECT_FACTORY_SUPPORTED_ENABLED(LightlyShadersEffect, "lightlyshaders.json", return LightlyShadersEffect::supported();, return LightlyShadersEffect::enabledByDefault();)
#endif


LightlyShadersEffect::LightlyShadersEffect() : Effect(), m_shader(0)
{
    new EffectAdaptor(this);
    QDBusConnection::sessionBus().registerObject("/LightlyShaders", this);
    for (int i = 0; i < NTex; ++i)
    {
        m_tex[i] = 0;
        m_rect[i] = 0;
        m_dark_rect[i] = 0;
    }
    reconfigure(ReconfigureAll);

    QString shadersDir(QStringLiteral("kwin/shaders/1.10/"));
    const qint64 version = kVersionNumber(1, 40);
    if (GLPlatform::instance()->glslVersion() >= version)
        shadersDir = QStringLiteral("kwin/shaders/1.40/");

    const QString shader = QStandardPaths::locate(QStandardPaths::GenericDataLocation, shadersDir + QStringLiteral("lightlyshaders.frag"));
    const QString diff_shader = QStandardPaths::locate(QStandardPaths::GenericDataLocation, shadersDir + QStringLiteral("lightlyshaders_diff.frag"));

    QFile file_shader(shader);
    QFile file_diff_shader(diff_shader);

    if (!file_shader.open(QFile::ReadOnly) || !file_diff_shader.open(QFile::ReadOnly))
    {
        qDebug() << "LightlyShaders: no shaders found! Exiting...";
        deleteLater();
        return;
    }

    QByteArray frag = file_shader.readAll();
    m_shader = ShaderManager::instance()->generateCustomShader(ShaderTrait::MapTexture, QByteArray(), frag);
    file_shader.close();

    QByteArray diff_frag = file_diff_shader.readAll();
    m_diff_shader = ShaderManager::instance()->generateCustomShader(ShaderTrait::MapTexture, QByteArray(), diff_frag);
    file_diff_shader.close();

    if (m_shader->isValid() && m_diff_shader->isValid())
    {
        const int background_sampler = m_shader->uniformLocation("background_sampler");
        const int shadow_sampler = m_shader->uniformLocation("shadow_sampler");
        const int radius_sampler = m_shader->uniformLocation("radius_sampler");
        const int sampler_size = m_shader->uniformLocation("sampler_size");
        const int flip_shadow = m_shader->uniformLocation("flip_shadow");
        ShaderManager::instance()->pushShader(m_shader);
        m_shader->setUniform(flip_shadow, 4);
        m_shader->setUniform(sampler_size, 3);
        m_shader->setUniform(radius_sampler, 2);
        m_shader->setUniform(shadow_sampler, 1);
        m_shader->setUniform(background_sampler, 0);
        ShaderManager::instance()->popShader();

        const int shadow_sampler_diff = m_diff_shader->uniformLocation("shadow_sampler");
        const int background_sampler_diff = m_diff_shader->uniformLocation("background_sampler");
        const int corner_number_diff = m_diff_shader->uniformLocation("corner_number");
        const int sampler_size_diff = m_diff_shader->uniformLocation("sampler_size");
        ShaderManager::instance()->pushShader(m_diff_shader);
        m_diff_shader->setUniform(sampler_size_diff, 3);
        m_diff_shader->setUniform(corner_number_diff, 2);
        m_diff_shader->setUniform(background_sampler_diff, 1);
        m_diff_shader->setUniform(shadow_sampler_diff, 0);
        ShaderManager::instance()->popShader();

        const auto stackingOrder = effects->stackingOrder();
        for (EffectWindow *window : stackingOrder) {
            windowAdded(window);
        }

        connect(effects, &EffectsHandler::windowAdded, this, &LightlyShadersEffect::windowAdded);
        connect(effects, &EffectsHandler::windowDeleted, this, &LightlyShadersEffect::windowDeleted);
        connect(effects, &EffectsHandler::windowMaximizedStateChanged, this, &LightlyShadersEffect::windowMaximizedStateChanged);
}
    else
        qDebug() << "LightlyShaders: no valid shaders found! LightlyShaders will not work.";
}

LightlyShadersEffect::~LightlyShadersEffect()
{
    if (m_shader)
        delete m_shader;
    if (m_diff_shader)
        delete m_diff_shader;
    for (int i = 0; i < NTex; ++i)
    {
        if (m_tex[i])
            delete m_tex[i];
        if (m_rect[i])
            delete m_rect[i];
        if (m_dark_rect[i])
            delete m_dark_rect[i];
    }
    m_clip.clear();
    m_diff.clear();
    m_diff_update.clear();
}

void
LightlyShadersEffect::windowDeleted(EffectWindow *w)
{
    m_managed.removeOne(w);
    m_skipEffect.removeOne(w);
    m_clip.remove(w);
    m_diff.remove(w);
    m_diff_update.remove(w);
}

static bool hasShadow(EffectWindow *w)
{
    if(w->expandedGeometry().size() != w->frameGeometry().size())
        return true;
    return false;
}

void
LightlyShadersEffect::windowAdded(EffectWindow *w)
{
    if (m_managed.contains(w)
            || w->windowType() == NET::OnScreenDisplay
            || w->windowType() == NET::Dock
            || w->windowType() == NET::Menu
            || w->windowType() == NET::DropdownMenu
            || w->windowType() == NET::Tooltip
            || w->windowType() == NET::ComboBox
            || w->windowType() == NET::Splash)
        return;
//    qDebug() << w->windowRole() << w->windowType() << w->windowClass();
    if (!w->hasDecoration() && (w->windowClass().contains("plasma", Qt::CaseInsensitive)
            || w->windowClass().contains("krunner", Qt::CaseInsensitive)
            || w->windowClass().contains("latte-dock", Qt::CaseInsensitive)
            || w->windowClass().contains("lattedock", Qt::CaseInsensitive)
            || w->windowClass().contains("albert", Qt::CaseInsensitive)
            || w->windowClass().contains("ksplash", Qt::CaseInsensitive)
            || w->windowClass().contains("ksmserver", Qt::CaseInsensitive)
            || (w->windowClass().contains("reaper", Qt::CaseInsensitive) && !hasShadow(w))))
        return;

    if(w->windowClass().contains("jetbrains", Qt::CaseInsensitive) && w->caption().contains(QRegularExpression ("win[0-9]+")))
        return;

    if (w->windowClass().contains("plasma", Qt::CaseInsensitive) && !w->isNormalWindow() && !w->isDialog() && !w->isModal())
        return;

    if (w->isDesktop()
            || w->isFullScreen()
            || w->isPopupMenu()
            || w->isTooltip() 
            || w->isSpecialWindow()
            || w->isDropdownMenu()
            || w->isPopupWindow()
            || w->isLockScreen()
            || w->isSplash())
        return;

    QRect maximized_area = effects->clientArea(MaximizeArea, w);
    if (maximized_area == w->frameGeometry() && m_disabled_for_maximized)
        m_skipEffect << w;

    m_managed << w;
    m_diff_update[w] = true;
}

void 
LightlyShadersEffect::windowMaximizedStateChanged(EffectWindow *w, bool horizontal, bool vertical) 
{
    if (!m_disabled_for_maximized) return;

    if ((horizontal == true) && (vertical == true)) {
        m_skipEffect << w;
        m_diff_update[w] = true;
    } else {
        m_skipEffect.removeOne(w);
    }
}

void
LightlyShadersEffect::drawSquircle(QPainter *p, float size, int translate)
{
    QPainterPath squircle;
    float squircleSize = size * 2 * (float(m_squircle_ratio)/24.0 * 0.25 + 0.8); //0.8 .. 1.05
    float squircleEdge = (size * 2) - squircleSize;

    squircle.moveTo(size, 0);
    squircle.cubicTo(QPointF(squircleSize, 0), QPointF(size * 2, squircleEdge), QPointF(size * 2, size));
    squircle.cubicTo(QPointF(size * 2, squircleSize), QPointF(squircleSize, size * 2), QPointF(size, size * 2));
    squircle.cubicTo(QPointF(squircleEdge, size * 2), QPointF(0, squircleSize), QPointF(0, size));
    squircle.cubicTo(QPointF(0, squircleEdge), QPointF(squircleEdge, 0), QPointF(size, 0));

    squircle.translate(translate,translate);

    p->drawPolygon(squircle.toFillPolygon());
}

QImage
LightlyShadersEffect::genMaskImg(int size, bool mask, bool outer_rect)
{
    QImage img(size*2, size*2, QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::transparent);
    QPainter p(&img);
    QRect r(img.rect());
    int offset_decremented = m_shadow_offset-1;

    if(mask) {
        p.fillRect(img.rect(), Qt::black);
        p.setCompositionMode(QPainter::CompositionMode_DestinationOut);
        p.setPen(Qt::NoPen);
        p.setBrush(Qt::black);
        p.setRenderHint(QPainter::Antialiasing);
        if (m_corners_type == SquircledCorners) {
            drawSquircle(&p, (size-m_shadow_offset), m_shadow_offset);
        } else {
            p.drawEllipse(r.adjusted(m_shadow_offset,m_shadow_offset,-m_shadow_offset,-m_shadow_offset));
        }
    } else {
        p.setPen(Qt::NoPen);
        p.setRenderHint(QPainter::Antialiasing);
        r.adjust(offset_decremented, offset_decremented, -offset_decremented, -offset_decremented);
        if(outer_rect) {
            if(m_dark_theme) 
                p.setBrush(QColor(0, 0, 0, 240));
            else 
                p.setBrush(QColor(0, 0, 0, m_alpha));
        } else {
            p.setBrush(QColor(255, 255, 255, m_alpha));
        }
        if (m_corners_type == SquircledCorners) {
            drawSquircle(&p, (size-offset_decremented), offset_decremented);
        } else {
            p.drawEllipse(r);
        }
        p.setCompositionMode(QPainter::CompositionMode_DestinationOut);
        p.setBrush(Qt::black);
        r.adjust(1, 1, -1, -1);
        if (m_corners_type == SquircledCorners) {
            drawSquircle(&p, (size-m_shadow_offset), m_shadow_offset);
        } else {
            p.drawEllipse(r);
        }
    }
    p.end();

    return img;
}

void
LightlyShadersEffect::genMasks()
{
    for (int i = 0; i < NTex; ++i)
        if (m_tex[i])
            delete m_tex[i];

    int size = m_size_scaled + m_shadow_offset;

    QImage img = genMaskImg(size, true, false);
    
    m_tex[TopLeft] = new GLTexture(img.copy(0, 0, size, size), GL_TEXTURE_RECTANGLE);
    m_tex[TopRight] = new GLTexture(img.copy(size, 0, size, size), GL_TEXTURE_RECTANGLE);
    m_tex[BottomRight] = new GLTexture(img.copy(size, size, size, size), GL_TEXTURE_RECTANGLE);
    m_tex[BottomLeft] = new GLTexture(img.copy(0, size, size, size), GL_TEXTURE_RECTANGLE);
}

void
LightlyShadersEffect::genRect()
{
    for (int i = 0; i < NTex; ++i) {
        if (m_rect[i])
            delete m_rect[i];
        if (m_dark_rect[i])
            delete m_dark_rect[i];
    }

    int size = m_size_scaled + (m_shadow_offset-1);

    QImage img = genMaskImg(size, false, false);

    m_rect[TopLeft] = new GLTexture(img.copy(0, 0, size, size));
    m_rect[TopRight] = new GLTexture(img.copy(size, 0, size, size));
    m_rect[BottomRight] = new GLTexture(img.copy(size, size, size, size));
    m_rect[BottomLeft] = new GLTexture(img.copy(0, size, size, size));

    size = m_size_scaled + m_shadow_offset;
    QImage img2 = genMaskImg(size, false, true);

    m_dark_rect[TopLeft] = new GLTexture(img2.copy(0, 0, size, size));
    m_dark_rect[TopRight] = new GLTexture(img2.copy(size, 0, size, size));
    m_dark_rect[BottomRight] = new GLTexture(img2.copy(size, size, size, size));
    m_dark_rect[BottomLeft] = new GLTexture(img2.copy(0, size, size, size));
}

void
LightlyShadersEffect::setRoundness(const int r)
{
    m_size = r;
    m_size_scaled = r*m_scale;
    m_corner = QSize(m_size+(m_shadow_offset-1), m_size+(m_shadow_offset-1));
    genMasks();
    genRect();
}

void
LightlyShadersEffect::reconfigure(ReconfigureFlags flags)
{
    Q_UNUSED(flags)
    KConfigGroup conf = KSharedConfig::openConfig("lightlyshaders.conf")->group("General");
    m_alpha = int(conf.readEntry("alpha", 15)*2.55);
    m_outline = conf.readEntry("outline", false);
    m_dark_theme = conf.readEntry("dark_theme", false);
    m_disabled_for_maximized = conf.readEntry("disabled_for_maximized", false);
    m_corners_type = conf.readEntry("corners_type", int(RoundedCorners));
    m_squircle_ratio = int(conf.readEntry("squircle_ratio", 12));
    m_shadow_offset = int(conf.readEntry("shadow_offset", 2));
    m_roundness = int(conf.readEntry("roundness", 5));
    if(m_shadow_offset>=m_roundness) {
        m_shadow_offset = m_roundness-1;
    }
    int roundness = m_roundness;
    if(m_scale!=1.0) {
        roundness /= m_scale;
    }
    setRoundness(roundness);
}

void
LightlyShadersEffect::prePaintWindow(EffectWindow *w, WindowPrePaintData &data, std::chrono::milliseconds time)
{
    if (!isValidWindow(w))
    {
        effects->prePaintWindow(w, data, time);
        return;
    }

    const QRect s(effects->virtualScreenGeometry());
    const QRect geo(w->frameGeometry());
    const QRegion exp_geo(w->expandedGeometry());
    const QRegion shadow = exp_geo - geo;

    if(shadow.intersects(data.paint) && geo.width() != s.width()) {
        m_diff_update[w] = true;
        //qDebug() << "shadow repainted";
    }

    int offset_decremented = m_shadow_offset-1;

    const QRect rect[NTex] =
    {
        QRect(geo.topLeft()-QPoint(offset_decremented,offset_decremented), m_corner),
        QRect(geo.topRight()-QPoint(m_size-offset_decremented, offset_decremented), m_corner),
        QRect(geo.bottomRight()-QPoint(m_size-offset_decremented, m_size-offset_decremented), m_corner),
        QRect(geo.bottomLeft()-QPoint(offset_decremented, m_size-offset_decremented), m_corner)
    };
    QRegion repaintRegion(QRegion(geo.adjusted(-m_shadow_offset, -m_shadow_offset, m_shadow_offset, m_shadow_offset))-geo.adjusted(m_shadow_offset, m_shadow_offset, -m_shadow_offset, -m_shadow_offset));

    for (int i = 0; i < NTex; ++i)
    {
        repaintRegion += rect[i];
    }

    QRegion clip = QRegion();
    QRegion clip_scaled = QRegion();

    const auto stackingOrder = effects->stackingOrder();
    bool bottom_w = true;
    for (EffectWindow *window : stackingOrder) {
        if(!window->isVisible()
            || window->isDeleted()
            || window->opacity() != 1.0
            || window->isUserMove()
            || window->isUserResize()
            || window->windowClass().contains("latte-dock", Qt::CaseInsensitive)
            || window->windowClass().contains("lattedock", Qt::CaseInsensitive)
            || window->windowClass().contains("peek", Qt::CaseInsensitive)
            || (bottom_w && window != w)
        ) continue;

        const void *addedGrab = window->data(WindowAddedGrabRole).value<void *>();
        if (addedGrab) continue;
        const void *unminimizedGrab = window->data(WindowUnminimizedGrabRole).value<void *>();
        if (unminimizedGrab) continue;

        bottom_w = false;
        if(window != w) {
            /*const QRect r = window->frameGeometry().adjusted(m_size, m_size, -m_size, -m_size);
            clip += r;
            clip_scaled += scale(r);*/

            QRect w_geo = window->frameGeometry();

            clip += w_geo;
            clip_scaled += scale(w_geo);

            const QRect w_rect[NTex] =
            {
                QRect(w_geo.topLeft()-QPoint(offset_decremented,offset_decremented), m_corner),
                QRect(w_geo.topRight()-QPoint(m_size-offset_decremented, offset_decremented), m_corner),
                QRect(w_geo.bottomRight()-QPoint(m_size-offset_decremented, m_size-offset_decremented), m_corner),
                QRect(w_geo.bottomLeft()-QPoint(offset_decremented, m_size-offset_decremented), m_corner)
            };

            for (int i = 0; i < NTex; ++i)
            {
                clip -= w_rect[i];
                clip_scaled -= scale(w_rect[i]);
            }
        }
    }

    if(m_clip[w] != clip_scaled) {
        m_clip[w] = clip_scaled;
        m_diff_update[w] = true;
    }

    repaintRegion -= clip;

    for (int i = 0; i < NTex; ++i)
    {
        if(!clip.contains(rect[i])) {
            repaintRegion += rect[i];
            clip -= rect[i];
            clip_scaled -= scale(rect[i]);
        }
    }

#if KWIN_EFFECT_API_VERSION < 234
    data.clip -= repaintRegion;
#else
    data.opaque -= repaintRegion;
#endif
    data.paint += repaintRegion;

    if(shadow.isEmpty()) {
        data.paint = infiniteRegion();
        GLTexture tex = GLTexture(GL_TEXTURE_RECTANGLE);
        m_diff[w] = QList<GLTexture>();
        m_diff_update[w] = false;
        for (int i = 0; i < NTex; ++i)
        {
            m_diff[w].append(tex);
        }
    }

    effects->prePaintWindow(w, data, time);
}

void
LightlyShadersEffect::paintScreen(int mask, const QRegion &region, ScreenPaintData &data)
{
    effects->paintScreen(mask, region, data);
#if KWIN_EFFECT_API_VERSION < 234
    qreal scale = GLRenderTarget::virtualScreenScale();
#else
    qreal scale = effects->renderTargetScale();
#endif
    qreal zoom = data.xScale();
    if(scale*zoom != m_scale) {
        if(zoom == 1.0 && scale>m_scale) {
            m_scale = scale*zoom;
            int roundness = m_roundness;
            if(m_scale!=1.0) {
                roundness /= m_scale;
            }
            setRoundness(roundness);
        } else {
            m_scale = scale*zoom;
        }
    }
}

bool
LightlyShadersEffect::isValidWindow(EffectWindow *w)
{
    if (!m_shader->isValid()
            || !w->isOnCurrentDesktop()
            || !m_managed.contains(w)
        /*#if KWIN_EFFECT_API_VERSION < 234
            || !w->isPaintingEnabled()
        #endif*/
            || effects->hasActiveFullScreenEffect()
            || w->isFullScreen()
            || w->isDesktop()
            || w->isSpecialWindow()
            || m_skipEffect.contains(w))
    {
        return false;
    }
    return true;
}


void
LightlyShadersEffect::paintWindow(EffectWindow *w, int mask, QRegion region, WindowPaintData &data)
{
    if (!isValidWindow(w) || (mask & (PAINT_WINDOW_TRANSFORMED|PAINT_SCREEN_WITH_TRANSFORMED_WINDOWS)))
    {
        effects->paintWindow(w, mask, region, data);
        return;
    }

    bool use_outline = m_outline;
    if(mask & PAINT_WINDOW_TRANSFORMED) {
        use_outline = false;
    }

#if KWIN_EFFECT_API_VERSION < 234
    const QRect screen = GLRenderTarget::virtualScreenGeometry();
#else
    const QRect screen = effects->renderTargetRect();
#endif
    qreal xTranslation = data.xTranslation() + screen.x();
    qreal yTranslation = data.yTranslation() + effects->virtualScreenSize().height() - screen.height() - screen.y();
    
    //map the corners
    const QRect geo(w->frameGeometry());
    const QRect geo_scaled = scale(geo);
    const QSize size_scaled(m_size_scaled+m_shadow_offset, m_size_scaled+m_shadow_offset);
    const QRect big_rect_scaled[NTex] =
    {
        QRect(geo_scaled.topLeft()-QPoint(m_shadow_offset,m_shadow_offset), size_scaled),
        QRect(geo_scaled.topRight()-QPoint(m_size_scaled-1, m_shadow_offset), size_scaled),
        QRect(geo_scaled.bottomRight()-QPoint(m_size_scaled-1, m_size_scaled-1), size_scaled),
        QRect(geo_scaled.bottomLeft()-QPoint(m_shadow_offset, m_size_scaled-1), size_scaled)
    };

    const QRect s(effects->virtualScreenGeometry());
    const QRect s_scaled = scale(s);

    //check if one of the corners is out of screen
    bool out_of_screen = ! (
        s_scaled.contains(big_rect_scaled[TopLeft], true)
        && s_scaled.contains(big_rect_scaled[TopRight], true)
        && s_scaled.contains(big_rect_scaled[BottomRight], true)
        && s_scaled.contains(big_rect_scaled[BottomLeft], true)
    );

    if(w->isDeleted() && out_of_screen) {
        effects->paintWindow(w, mask, region, data);
        return;
    }

    //copy the empty corner regions
    QList<GLTexture> empty_corners_tex = getTexRegions(w, big_rect_scaled, s_scaled, NTex, xTranslation, yTranslation);

    //paint the actual window
    effects->paintWindow(w, mask, region, data);

    //get shadows
    getShadowDiffs(w, big_rect_scaled, empty_corners_tex, xTranslation, yTranslation, out_of_screen);

    //Draw rounded corners with shadows    
    glEnable(GL_BLEND);
    const int mvpMatrixLocation = m_shader->uniformLocation("modelViewProjectionMatrix");
    const int samplerSizeLocation = m_shader->uniformLocation("sampler_size");
    const int flipShadowLocation = m_shader->uniformLocation("flip_shadow");
    ShaderManager *sm = ShaderManager::instance();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    sm->pushShader(m_shader);
    for (int i = 0; i < NTex; ++i)
    {
        if(m_clip[w].contains(big_rect_scaled[i].adjusted(m_size_scaled, m_size_scaled, -m_size_scaled, -m_size_scaled))) {
            continue;
        }

        QMatrix4x4 mvp = data.screenProjectionMatrix();
        mvp.scale(1.0/m_scale);
        mvp.translate(big_rect_scaled[i].x(), big_rect_scaled[i].y());
        QVector2D samplerSize = QVector2D(big_rect_scaled[i].width(), big_rect_scaled[i].height());
        m_shader->setUniform(mvpMatrixLocation, mvp);
        m_shader->setUniform(samplerSizeLocation, samplerSize);
        m_shader->setUniform(flipShadowLocation, out_of_screen && (i==1 || i==2));
        glActiveTexture(GL_TEXTURE2);
        m_tex[i]->bind();
        glActiveTexture(GL_TEXTURE1);
        m_diff[w][i].bind();
        glActiveTexture(GL_TEXTURE0);
        empty_corners_tex[i].bind();
        empty_corners_tex[i].render(region, big_rect_scaled[i]);
        empty_corners_tex[i].unbind();
        m_diff[w][i].unbind();
        m_tex[i]->unbind();
    }
    sm->popShader();

    // outline
    if (use_outline && data.brightness() == 1.0 && data.crossFadeProgress() == 1.0)
    {
        const float o(data.opacity());

        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

        //Outer corners
        GLShader *shader = ShaderManager::instance()->pushShader(ShaderTrait::MapTexture|ShaderTrait::UniformColor|ShaderTrait::Modulate);
        shader->setUniform(GLShader::ModulationConstant, QVector4D(o, o, o, o));
        for (int i = 0; i < NTex; ++i)
        {
            if(m_clip[w].contains(big_rect_scaled[i].adjusted(m_size_scaled, m_size_scaled, -m_size_scaled, -m_size_scaled))) {
                continue;
            }

            QMatrix4x4 modelViewProjection = data.screenProjectionMatrix();
            modelViewProjection.scale(1.0/m_scale);
            modelViewProjection.translate(big_rect_scaled[i].x(), big_rect_scaled[i].y());
            shader->setUniform("modelViewProjectionMatrix", modelViewProjection);
            m_dark_rect[i]->bind();
            m_dark_rect[i]->render(region, big_rect_scaled[i]);
            m_dark_rect[i]->unbind();
        
        }
        ShaderManager::instance()->popShader();

        //Inner corners
        int offset_decremented = m_shadow_offset-1;
        const QSize i_size = QSize(m_size_scaled+offset_decremented, m_size_scaled+offset_decremented);
        const QRect rect_scaled[NTex] =
        {
            QRect(geo_scaled.topLeft()-QPoint(offset_decremented,offset_decremented), i_size),
            QRect(geo_scaled.topRight()-QPoint(m_size_scaled-1, offset_decremented), i_size),
            QRect(geo_scaled.bottomRight()-QPoint(m_size_scaled-1, m_size_scaled-1), i_size),
            QRect(geo_scaled.bottomLeft()-QPoint(offset_decremented, m_size_scaled-1), i_size)
        };

        shader = ShaderManager::instance()->pushShader(ShaderTrait::MapTexture|ShaderTrait::UniformColor|ShaderTrait::Modulate);
        shader->setUniform(GLShader::ModulationConstant, QVector4D(o, o, o, o));

        for (int i = 0; i < NTex; ++i)
        {
            if(m_clip[w].contains(rect_scaled[i].adjusted(m_size_scaled, m_size_scaled, -m_size_scaled, -m_size_scaled))) {
                continue;
            }

            QMatrix4x4 modelViewProjection = data.screenProjectionMatrix();
            modelViewProjection.scale(1.0/m_scale);
            modelViewProjection.translate(rect_scaled[i].x(), rect_scaled[i].y());
            shader->setUniform("modelViewProjectionMatrix", modelViewProjection);
            m_rect[i]->bind();
            m_rect[i]->render(region, rect_scaled[i]);
            m_rect[i]->unbind();
        }
        ShaderManager::instance()->popShader();

        QRect geo_scaled = scale(geo);
        
        QRegion reg = geo_scaled;
        QMatrix4x4 mvp = data.screenProjectionMatrix();
        mvp.scale(1.0/m_scale);

        //Outline
        shader = ShaderManager::instance()->pushShader(ShaderTrait::UniformColor);
        shader->setUniform("modelViewProjectionMatrix", mvp);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        reg -= QRegion(geo_scaled.adjusted(1, 1, -1, -1));
        reg -= m_clip[w];
        for (int i = 0; i < NTex; ++i)
            reg -= rect_scaled[i];
        fillRegion(reg, QColor(255, 255, 255, m_alpha*data.opacity()));
        ShaderManager::instance()->popShader();

        //Borderline
        shader = ShaderManager::instance()->pushShader(ShaderTrait::UniformColor);
        shader->setUniform("modelViewProjectionMatrix", mvp);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        reg = QRegion(geo_scaled.adjusted(-1, -1, 1, 1));
        reg -= geo_scaled;
        reg -= m_clip[w];
        for (int i = 0; i < NTex; ++i)
            reg -= rect_scaled[i];
        if(m_dark_theme)
            fillRegion(reg, QColor(0, 0, 0, 255*data.opacity()));
        else
            fillRegion(reg, QColor(0, 0, 0, m_alpha*data.opacity()));
        ShaderManager::instance()->popShader();
    }

    glDisable(GL_BLEND);
}

void
LightlyShadersEffect::fillRegion(const QRegion &reg, const QColor &c)
{
    GLVertexBuffer *vbo = GLVertexBuffer::streamingBuffer();
    vbo->reset();
    vbo->setUseColor(true);
    vbo->setColor(c);
    QVector<float> verts;
    for (const QRect &r : reg)
    {
        verts << r.x() + r.width() << r.y();
        verts << r.x() << r.y();
        verts << r.x() << r.y() + r.height();
        verts << r.x() << r.y() + r.height();
        verts << r.x() + r.width() << r.y() + r.height();
        verts << r.x() + r.width() << r.y();
    }
    vbo->setData(verts.count() / 2, 2, verts.data(), NULL);
    vbo->render(GL_TRIANGLES);
}

void
LightlyShadersEffect::getShadowDiffs(EffectWindow *w, const QRect* rect, QList<GLTexture> &empty_corners_tex, qreal xTranslation, qreal yTranslation, bool out_of_screen)
{
    // if we already have diff cache and there's no need to update it, return
    if(m_diff.contains(w) && (m_diff_update.contains(w) && !m_diff_update[w])) return;

    //else do 1 offscreen paint if needed and get the cache for topleft and bottomleft corners
    m_diff_update[w] = false;
    const QRect w_exgeo = w->expandedGeometry();
    const QRect w_exgeo_scaled = scale(w_exgeo);

    //map corners
    const QRect r4[NTex] =
    {
        QRect(QPoint(rect[TopLeft].x()-w_exgeo_scaled.x(),rect[TopLeft].y()-w_exgeo_scaled.y()), rect[TopLeft].size()),
        QRect(QPoint(rect[TopRight].x()-w_exgeo_scaled.x(),rect[TopRight].y()-w_exgeo_scaled.y()), rect[TopRight].size()),
        QRect(QPoint(rect[BottomRight].x()-w_exgeo_scaled.x(),rect[BottomRight].y()-w_exgeo_scaled.y()), rect[BottomRight].size()),
        QRect(QPoint(rect[BottomLeft].x()-w_exgeo_scaled.x(),rect[BottomLeft].y()-w_exgeo_scaled.y()), rect[BottomLeft].size())
    };
    const QRect r2[NShad] =
    {
        r4[TopLeft],
        r4[BottomLeft]
    };

    const QRect s_geo = effects->virtualScreenGeometry();
    const QRect s_geo_scaled = scale(s_geo);
    QList<GLTexture> shadow_tex;
    //if window is not out of screen, get shadow samplers from the buffer for 4 corners
    if(!out_of_screen) {
        shadow_tex = getTexRegions(w, rect, s_geo_scaled, NTex, xTranslation, yTranslation, true);
    //else do offscreen render and get shadow samplers from 2 corners
    } else {
        QImage img(w_exgeo_scaled.width(), w_exgeo_scaled.height(), QImage::Format_ARGB32_Premultiplied);
        img.fill(Qt::white);
        GLTexture target = GLTexture(img.copy(0, 0, w_exgeo_scaled.width(), w_exgeo_scaled.height()), GL_TEXTURE_RECTANGLE);
        
    #if KWIN_EFFECT_API_VERSION < 234
        GLRenderTarget renderTarget(target);
        GLRenderTarget::pushRenderTarget(&renderTarget);
    #else
        GLFramebuffer renderTarget(&target);
        GLFramebuffer::pushFramebuffer(&renderTarget);
    #endif

    #if KWIN_EFFECT_API_VERSION < 234
        WindowPaintData d(w);
    #else
        WindowPaintData d;
    #endif
        d += QPoint(-w_exgeo.x(), -w_exgeo.y());
        QMatrix4x4 projection;
        projection.ortho(QRect(0, 0, w_exgeo.width(), w_exgeo.height()));
        d.setProjectionMatrix(projection);

        int mask = PAINT_WINDOW_TRANSFORMED | PAINT_WINDOW_TRANSLUCENT;

    #if KWIN_EFFECT_API_VERSION < 234
        GLVertexBuffer::setVirtualScreenGeometry(QRect(0, 0, w_exgeo_scaled.width(), w_exgeo_scaled.height()));
    #endif

        effects->drawWindow(w, mask, infiniteRegion(), d);

        //get shadow sampler from 2 corners
        shadow_tex = getTexRegions(w, r2, w_exgeo_scaled, NShad, 0.0, 0.0, true);
    #if KWIN_EFFECT_API_VERSION < 234
        GLRenderTarget::popRenderTarget();
    #else
        GLFramebuffer::popFramebuffer();
    #endif
    }

    m_diff[w] = QList<GLTexture>();

    const int mvpMatrixLocation = m_diff_shader ->uniformLocation("modelViewProjectionMatrix");
    const int cornerNumberLocation = m_diff_shader->uniformLocation("corner_number");
    const int samplerSizeLocation = m_diff_shader->uniformLocation("sampler_size");
    ShaderManager *sm = ShaderManager::instance();
    sm->pushShader(m_diff_shader);
    int n;
    if(out_of_screen) n = NShad;
    else n = NTex;
    const QRect *r = out_of_screen ? r2 : r4;
    GLTexture white_tex = GLTexture(GL_TEXTURE_RECTANGLE);
    if(out_of_screen) {
        QImage white_img(r[0].width(), r[0].height(), QImage::Format_ARGB32_Premultiplied);
        white_img.fill(Qt::white);
        white_tex = GLTexture(white_img.copy(0, 0, r[0].width(), r[0].height()), GL_TEXTURE_RECTANGLE);
    }
    for (int i = 0; i < n; ++i)
    {
        GLTexture target = GLTexture(GL_RGBA8, w_exgeo_scaled.size());
        
    #if KWIN_EFFECT_API_VERSION < 234
        GLRenderTarget renderTarget(target);
        GLRenderTarget::pushRenderTarget(&renderTarget);
    #else
        GLFramebuffer renderTarget(&target);
        GLFramebuffer::pushFramebuffer(&renderTarget);
    #endif

        QMatrix4x4 mvp;
        mvp.ortho(QRect(0, 0, w_exgeo_scaled.width(), w_exgeo_scaled.height()));
        QVector2D samplerSize = QVector2D(r[i].width(), r[i].height());
        mvp.translate(r[i].x(), r[i].y());
        m_diff_shader->setUniform(mvpMatrixLocation, mvp);
        m_diff_shader->setUniform(samplerSizeLocation, samplerSize);
        m_diff_shader->setUniform(cornerNumberLocation, out_of_screen? i*3 : i);
        glActiveTexture(GL_TEXTURE1);
        if(!out_of_screen) 
            empty_corners_tex[i].bind();
        else
            white_tex.bind();
        glActiveTexture(GL_TEXTURE0);
        shadow_tex[i].bind();
        shadow_tex[i].render(r[i], r[i]);
        shadow_tex[i].unbind();
        if(!out_of_screen) {
            empty_corners_tex[i].unbind();
            m_diff[w].append(copyTexSubImage(w_exgeo_scaled, r[i]));
        } else {
            white_tex.unbind();
            GLTexture t = copyTexSubImage(w_exgeo_scaled, r[i]);
            m_diff[w].append(t);
            m_diff[w].append(t);
        }
    #if KWIN_EFFECT_API_VERSION < 234
        GLRenderTarget::popRenderTarget();
    #else
        GLFramebuffer::popFramebuffer();
    #endif
    }
    sm->popShader();
}

QList<GLTexture>
LightlyShadersEffect::getTexRegions(EffectWindow *w, const QRect* rect, const QRect &geo, int nTex, qreal xTranslation, qreal yTranslation, bool force)
{
    QList<GLTexture> sample_tex;

    for (int i = 0; i < nTex; ++i)
    {
        if(m_clip[w].contains(rect[i].adjusted(m_size_scaled, m_size_scaled, -m_size_scaled, -m_size_scaled)) && !force) {
            sample_tex.append(GLTexture(GL_TEXTURE_RECTANGLE));
            continue;
        }

        sample_tex.append(copyTexSubImage(geo, rect[i], xTranslation, yTranslation));
    }

    return sample_tex;
}

GLTexture
LightlyShadersEffect::copyTexSubImage(const QRect &geo, const QRect &rect, qreal xTranslation, qreal yTranslation)
{
    QImage img(rect.width(), rect.height(), QImage::Format_ARGB32_Premultiplied);
    GLTexture t = GLTexture(img, GL_TEXTURE_RECTANGLE);
    t.bind();
    glCopyTexSubImage2D(
        GL_TEXTURE_RECTANGLE, 
        0, 
        0, 
        0, 
        rect.x() - xTranslation,
        geo.height() - rect.y() - rect.height() - yTranslation,
        rect.width(),
        rect.height()
    );
    t.unbind();
    return t;
}

QRect
LightlyShadersEffect::scale(const QRect rect)
{
    return QRect(
        rect.x()*m_scale,
        rect.y()*m_scale,
        rect.width()*m_scale,
        rect.height()*m_scale
    );
}

bool
LightlyShadersEffect::enabledByDefault()
{
    return supported();
}

bool
LightlyShadersEffect::supported()
{
#if KWIN_EFFECT_API_VERSION < 234
    return effects->isOpenGLCompositing() && GLRenderTarget::supported();
#else
    return effects->isOpenGLCompositing() && GLFramebuffer::supported();
#endif
}

#include "lightlyshaders.moc"


} // namespace KWin
