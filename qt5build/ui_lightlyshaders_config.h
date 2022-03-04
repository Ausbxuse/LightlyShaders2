#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'lightlyshaders_config.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIGHTLYSHADERS_CONFIG_H
#define UI_LIGHTLYSHADERS_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *roundness;
    QCheckBox *outline;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *alpha;
    QSpacerItem *horizontalSpacer;
    QCheckBox *darkTheme;
    QCheckBox *disabledForMaximized;
    QComboBox *cornersType;
    QLabel *squircleRatioLabel;
    QSlider *squircleRatio;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 300);
        gridLayout = new QGridLayout(Form);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        roundness = new QSpinBox(Form);
        roundness->setObjectName(QString::fromUtf8("roundness"));
        roundness->setMinimum(1);
        roundness->setMaximum(64);

        horizontalLayout->addWidget(roundness);


        verticalLayout->addLayout(horizontalLayout);

        outline = new QCheckBox(Form);
        outline->setObjectName(QString::fromUtf8("outline"));

        verticalLayout->addWidget(outline);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 7, -1, -1);
        label_2 = new QLabel(Form);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        alpha = new QSpinBox(Form);
        alpha->setObjectName(QString::fromUtf8("alpha"));
        alpha->setMinimum(1);
        alpha->setMaximum(100);

        horizontalLayout_2->addWidget(alpha);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        darkTheme = new QCheckBox(Form);
        darkTheme->setObjectName(QString::fromUtf8("darkTheme"));

        verticalLayout->addWidget(darkTheme);

        disabledForMaximized = new QCheckBox(Form);
        disabledForMaximized->setObjectName(QString::fromUtf8("disabledForMaximized"));

        verticalLayout->addWidget(disabledForMaximized);

        cornersType = new QComboBox(Form);
        cornersType->setObjectName(QString::fromUtf8("cornersType"));

        verticalLayout->addWidget(cornersType);

        squircleRatioLabel = new QLabel(Form);
        squircleRatioLabel->setObjectName(QString::fromUtf8("squircleRatioLabel"));

        verticalLayout->addWidget(squircleRatioLabel);

        squircleRatio = new QSlider(Form);
        squircleRatio->setObjectName(QString::fromUtf8("squircleRatio"));
        squircleRatio->setMinimum(0);
        squircleRatio->setMaximum(24);
        squircleRatio->setPageStep(12);
        squircleRatio->setOrientation(Qt::Horizontal);
        squircleRatio->setTickPosition(QSlider::TicksBelow);
        squircleRatio->setTickInterval(12);

        verticalLayout->addWidget(squircleRatio);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(tr2i18n("Form", nullptr));
        label->setText(tr2i18n("Radius:", nullptr));
        roundness->setSuffix(tr2i18n("px", nullptr));
        outline->setText(tr2i18n("Outline around window", nullptr));
        label_2->setText(tr2i18n("Outline strength:", nullptr));
        alpha->setSuffix(tr2i18n("%", nullptr));
        darkTheme->setText(tr2i18n("Use black border (dark theme mode)", nullptr));
        disabledForMaximized->setText(tr2i18n("Disable for maximized windows", nullptr));
        squircleRatioLabel->setText(tr2i18n("Squircle ratio", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LIGHTLYSHADERS_CONFIG_H

