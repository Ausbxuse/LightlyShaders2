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

#ifndef LIGHTLYSHADERS_H
#define LIGHTLYSHADERS_H

#include <kwineffects.h>

namespace KWin {

class GLTexture;

class Q_DECL_EXPORT LightlyShadersEffect : public KWin::Effect

{
    Q_OBJECT
public:
    LightlyShadersEffect();
    ~LightlyShadersEffect();

    static bool supported();
    static bool enabledByDefault();
    
    void setRoundness(const int r);
    void reconfigure(ReconfigureFlags flags) override;
    void prePaintWindow(EffectWindow* w, WindowPrePaintData& data, std::chrono::milliseconds time) override;
    void paintWindow(EffectWindow* w, int mask, QRegion region, WindowPaintData& data) override;
    virtual int requestedEffectChainPosition() const override { return 99; }

    enum { RoundedCorners = 0, SquircledCorners };

protected Q_SLOTS:
    void windowAdded(EffectWindow *window);
    void windowClosed(EffectWindow *window);
    void windowMaximizedStateChanged(EffectWindow *w, bool horizontal, bool vertical);

private:
    void genMasks();
    void genRect();

    void fillRegion(const QRegion &reg, const QColor &c);
    GLTexture copyTexSubImage(const QRect &geo, const QRect &rect);
    QList<GLTexture> getTexRegions(EffectWindow *w, const QRect* rect, const QRect &geo, int nTex, bool force=false);
    void drawSquircle(QPainter *p, float size, int translate);
    QImage genMaskImg(int size, bool mask, bool outer_rect);
    void getShadowDiffs(EffectWindow *w, const QRect* rect, QList<GLTexture> &empty_corners_tex, bool out_of_screen);

    enum { TopLeft = 0, TopRight, BottomRight, BottomLeft, NTex };
    enum { Top = 0, Bottom, NShad };
    GLTexture *m_tex[NTex];
    GLTexture *m_rect[NTex];
    GLTexture *m_dark_rect[NTex];
    int m_size, m_alpha, m_corners_type, m_squircle_ratio;
    bool m_outline, m_dark_theme, m_disabled_for_maximized;
    QSize m_corner;
    QMap<EffectWindow *, QRegion> m_clip;
    QMap<EffectWindow *, bool> m_diff_update;
    QMap<EffectWindow *, QList<GLTexture>> m_diff;
    GLShader *m_shader, *m_diff_shader;
    QList<EffectWindow *> m_managed, m_skipEffect;
};

} // namespace KWin

#endif //LIGHTLYSHADERS_H

