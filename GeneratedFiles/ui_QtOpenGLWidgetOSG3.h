/********************************************************************************
** Form generated from reading UI file 'QtOpenGLWidgetOSG3.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTOPENGLWIDGETOSG3_H
#define UI_QTOPENGLWIDGETOSG3_H

#include <OSGWidget.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtOpenGLWidgetOSG3Class
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnCloud;
    QPushButton *btnCylinder;
    QPushButton *btnGlider;
    QPushButton *btnQuad;
    QPushButton *btnShape;
    QPushButton *btnClear;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radXaxis;
    QRadioButton *radYaxis;
    QRadioButton *radZaxis;
    QPushButton *btnBeginColor;
    QPushButton *btnEndColor;
    QPushButton *btnHeightRamp;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *radSelPoint;
    QRadioButton *radMeasure;
    QPushButton *btnReset;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_2;
    OSGWidget *openGLWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtOpenGLWidgetOSG3Class)
    {
        if (QtOpenGLWidgetOSG3Class->objectName().isEmpty())
            QtOpenGLWidgetOSG3Class->setObjectName(QString::fromUtf8("QtOpenGLWidgetOSG3Class"));
        QtOpenGLWidgetOSG3Class->resize(930, 696);
        centralWidget = new QWidget(QtOpenGLWidgetOSG3Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnCloud = new QPushButton(groupBox);
        btnCloud->setObjectName(QString::fromUtf8("btnCloud"));
        btnCloud->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(btnCloud);

        btnCylinder = new QPushButton(groupBox);
        btnCylinder->setObjectName(QString::fromUtf8("btnCylinder"));
        btnCylinder->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(btnCylinder);

        btnGlider = new QPushButton(groupBox);
        btnGlider->setObjectName(QString::fromUtf8("btnGlider"));
        btnGlider->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(btnGlider);

        btnQuad = new QPushButton(groupBox);
        btnQuad->setObjectName(QString::fromUtf8("btnQuad"));
        btnQuad->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(btnQuad);

        btnShape = new QPushButton(groupBox);
        btnShape->setObjectName(QString::fromUtf8("btnShape"));
        btnShape->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(btnShape);

        btnClear = new QPushButton(groupBox);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));
        btnClear->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(btnClear);


        horizontalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        radXaxis = new QRadioButton(groupBox_2);
        radXaxis->setObjectName(QString::fromUtf8("radXaxis"));
        radXaxis->setMinimumSize(QSize(0, 40));
        radXaxis->setChecked(true);

        horizontalLayout_2->addWidget(radXaxis);

        radYaxis = new QRadioButton(groupBox_2);
        radYaxis->setObjectName(QString::fromUtf8("radYaxis"));
        radYaxis->setMinimumSize(QSize(0, 40));

        horizontalLayout_2->addWidget(radYaxis);

        radZaxis = new QRadioButton(groupBox_2);
        radZaxis->setObjectName(QString::fromUtf8("radZaxis"));
        radZaxis->setMinimumSize(QSize(0, 40));

        horizontalLayout_2->addWidget(radZaxis);

        btnBeginColor = new QPushButton(groupBox_2);
        btnBeginColor->setObjectName(QString::fromUtf8("btnBeginColor"));
        btnBeginColor->setMinimumSize(QSize(0, 40));
        btnBeginColor->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 0);"));

        horizontalLayout_2->addWidget(btnBeginColor);

        btnEndColor = new QPushButton(groupBox_2);
        btnEndColor->setObjectName(QString::fromUtf8("btnEndColor"));
        btnEndColor->setMinimumSize(QSize(0, 40));
        btnEndColor->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));

        horizontalLayout_2->addWidget(btnEndColor);

        btnHeightRamp = new QPushButton(groupBox_2);
        btnHeightRamp->setObjectName(QString::fromUtf8("btnHeightRamp"));
        btnHeightRamp->setMinimumSize(QSize(0, 40));

        horizontalLayout_2->addWidget(btnHeightRamp);


        horizontalLayout_3->addWidget(groupBox_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        horizontalLayout_5 = new QHBoxLayout(groupBox_3);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        radSelPoint = new QRadioButton(groupBox_3);
        radSelPoint->setObjectName(QString::fromUtf8("radSelPoint"));
        radSelPoint->setMinimumSize(QSize(0, 40));

        horizontalLayout_5->addWidget(radSelPoint);

        radMeasure = new QRadioButton(groupBox_3);
        radMeasure->setObjectName(QString::fromUtf8("radMeasure"));
        radMeasure->setMinimumSize(QSize(0, 40));

        horizontalLayout_5->addWidget(radMeasure);

        btnReset = new QPushButton(groupBox_3);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));
        btnReset->setMinimumSize(QSize(0, 40));

        horizontalLayout_5->addWidget(btnReset);

        btnCancel = new QPushButton(groupBox_3);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setMinimumSize(QSize(0, 40));

        horizontalLayout_5->addWidget(btnCancel);


        horizontalLayout_4->addWidget(groupBox_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_4);

        openGLWidget = new OSGWidget(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));

        verticalLayout->addWidget(openGLWidget);

        QtOpenGLWidgetOSG3Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtOpenGLWidgetOSG3Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 930, 23));
        QtOpenGLWidgetOSG3Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtOpenGLWidgetOSG3Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtOpenGLWidgetOSG3Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtOpenGLWidgetOSG3Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtOpenGLWidgetOSG3Class->setStatusBar(statusBar);

        retranslateUi(QtOpenGLWidgetOSG3Class);

        QMetaObject::connectSlotsByName(QtOpenGLWidgetOSG3Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtOpenGLWidgetOSG3Class)
    {
        QtOpenGLWidgetOSG3Class->setWindowTitle(QApplication::translate("QtOpenGLWidgetOSG3Class", "QtOpenGLWidgetOSG3", nullptr));
        groupBox->setTitle(QApplication::translate("QtOpenGLWidgetOSG3Class", "GroupBox", nullptr));
        btnCloud->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "\347\202\271\344\272\221", nullptr));
        btnCylinder->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "\345\234\206\346\237\261", nullptr));
        btnGlider->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "\346\273\221\347\277\224\346\234\272", nullptr));
        btnQuad->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "\345\233\233\350\276\271\345\275\242", nullptr));
        btnShape->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "\345\207\240\344\275\225\344\275\223", nullptr));
        btnClear->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "Clear", nullptr));
        groupBox_2->setTitle(QApplication::translate("QtOpenGLWidgetOSG3Class", "GroupBox", nullptr));
        radXaxis->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "X\350\275\264", nullptr));
        radYaxis->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "Y\350\275\264", nullptr));
        radZaxis->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "Z\350\275\264", nullptr));
        btnBeginColor->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "\345\274\200\345\247\213\351\242\234\350\211\262", nullptr));
        btnEndColor->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "\347\273\223\346\235\237\351\242\234\350\211\262", nullptr));
        btnHeightRamp->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "\347\241\256\345\256\232", nullptr));
        groupBox_3->setTitle(QApplication::translate("QtOpenGLWidgetOSG3Class", "GroupBox", nullptr));
        radSelPoint->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "\351\200\211\347\202\271", nullptr));
        radMeasure->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "\346\265\213\351\207\217", nullptr));
        btnReset->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "\351\207\215\347\275\256", nullptr));
        btnCancel->setText(QApplication::translate("QtOpenGLWidgetOSG3Class", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtOpenGLWidgetOSG3Class: public Ui_QtOpenGLWidgetOSG3Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTOPENGLWIDGETOSG3_H
