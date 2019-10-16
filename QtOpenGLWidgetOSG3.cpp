#include "QtOpenGLWidgetOSG3.h"
#include "OSGWidget.h"
#include <QColorDialog>
#include <QButtonGroup>
QtOpenGLWidgetOSG3::QtOpenGLWidgetOSG3(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	/*QtOSGWidget* widget = new QtOSGWidget();
	this->setCentralWidget(widget);*/
	connect(this->ui.btnCloud, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onCloud()));
	connect(this->ui.btnCylinder, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onCylinder()));
	connect(this->ui.btnGlider, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onGlider()));
	connect(this->ui.btnQuad, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onQuad()));
	connect(this->ui.btnShape, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onShape()));
	connect(this->ui.btnClear, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onClear()));

	//connect(this->ui.btnCloud, SIGNAL(clicked(bool)), this->ui.groupBox_2, SLOT(setVisible(bool)));
	//connect(this->ui.btnCylinder, SIGNAL(clicked(bool)), this->ui.groupBox_2, SLOT(setVisible(bool)));
	//connect(this->ui.btnGlider, SIGNAL(clicked(bool)), this->ui.groupBox_2, SLOT(setVisible(bool)));
	//connect(this->ui.btnQuad, SIGNAL(clicked(bool)), this->ui.groupBox_2, SLOT(setVisible(bool)));
	//connect(this->ui.btnShape, SIGNAL(clicked(bool)), this->ui.groupBox_2, SLOT(setVisible(bool)));
	//connect(this->ui.btnClear, SIGNAL(clicked(bool)), this->ui.groupBox_2, SLOT(setVisible(bool)));

	connect(this->ui.radXaxis, SIGNAL(clicked()), this, SLOT(onChangedHightRamp()));
	connect(this->ui.radYaxis, SIGNAL(clicked()), this, SLOT(onChangedHightRamp()));
	connect(this->ui.radZaxis, SIGNAL(clicked()), this, SLOT(onChangedHightRamp()));
	connect(this->ui.btnBeginColor, SIGNAL(clicked()), this, SLOT(onSelBeginColor()));
	connect(this->ui.btnEndColor, SIGNAL(clicked()), this, SLOT(onSelEndColor()));
	connect(this->ui.btnHeightRamp, SIGNAL(clicked()), this, SLOT(onSendHeightRamp()));
	connect(this, SIGNAL(sendHeightRamp(int, QColor, QColor)), this->ui.openGLWidget, SLOT(onRecHeightRamp(int, QColor, QColor)));
	connect(this, SIGNAL(sendHeightRamp(int, QColor, QColor)), this, SLOT(onRecHeightRamp(int, QColor, QColor)));
	//this->ui.groupBox_2->setVisible(false);

	radGroup = new QButtonGroup(this);
	radGroup->addButton(this->ui.radSelPoint);
	radGroup->addButton(this->ui.radMeasure);

	connect(radGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onSelPoint(QAbstractButton*, bool)));
	/*connect(this->ui.radSelPoint, SIGNAL(toggled(bool )), this, SLOT(onSelPoint(bool)));
	connect(this->ui.radMeasure, SIGNAL(toggled(bool )), this, SLOT(onSelPoint(bool)));*/
	connect(this->ui.btnReset, SIGNAL(clicked()), this, SLOT(onResetSelPoint()));
	connect(this->ui.btnCancel, SIGNAL(clicked()), this, SLOT(onCancelSelPoint()));

	connect(this, SIGNAL(selCloudPoint(OSGWidget::MeauseCloud)), this->ui.openGLWidget, SLOT(onSelCloudPoint(OSGWidget::MeauseCloud)));

	connect(this->ui.btnTest, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onTest()));
}
void QtOpenGLWidgetOSG3::onSelPoint(QAbstractButton *button, bool checked) {
	if (checked) {
		if (this->ui.radSelPoint == button) {
			emit selCloudPoint(OSGWidget::MeauseCloud::ONEPOINT);
		}
		else if (this->ui.radMeasure == button) {
			emit selCloudPoint(OSGWidget::MeauseCloud::TWOMEAUSE);
		}
	}
}
void QtOpenGLWidgetOSG3::onResetSelPoint() {
	radGroup->setExclusive(false);
	this->ui.radSelPoint->setChecked(false);
	this->ui.radMeasure->setChecked(false);
	radGroup->setExclusive(true);
	emit selCloudPoint(OSGWidget::MeauseCloud::RESET);
}
void QtOpenGLWidgetOSG3::onCancelSelPoint() {
	radGroup->setExclusive(false);
	this->ui.radSelPoint->setChecked(false);
	this->ui.radMeasure->setChecked(false);
	radGroup->setExclusive(true);
	emit selCloudPoint(OSGWidget::MeauseCloud::NONE);
}

void QtOpenGLWidgetOSG3::onShowHeightRamp() {

}
void QtOpenGLWidgetOSG3::onHideHeightRamp() {

}
void QtOpenGLWidgetOSG3::onChangedHightRamp() {

}
void QtOpenGLWidgetOSG3::onSelBeginColor() {
	 QColor color = QColorDialog::getColor(begColor,this,"ѡ����ʼ��ɫ");
	 //qreal r, g, b;
	 int r, g, b;
	 if (color.isValid()) {
		 color.getRgb(&r, &g, &b);
		 //color.getRgbF(&r, &g, &b);
		 begColor = color;
		 this->ui.btnBeginColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)").arg(r).arg(g).arg(b));
	 }
}
void QtOpenGLWidgetOSG3::onSelEndColor() {
	QColor color = QColorDialog::getColor(endColor, this, "ѡ�������ɫ");
	int r, g, b;
	if (color.isValid()) {
		color.getRgb(&r, &g, &b);
		endColor = color;
		this->ui.btnEndColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)").arg(r).arg(g).arg(b));
	}
}
void QtOpenGLWidgetOSG3::onSendHeightRamp() {
	int axis = 1;
	if (this->ui.radXaxis->isChecked()) {
		axis = 1;
	}
	else if (this->ui.radYaxis->isChecked()) {
		axis = 2;
	}
	else if (this->ui.radZaxis->isChecked()) {
		axis = 3;
	}
	emit sendHeightRamp(axis, begColor, endColor);
}
void QtOpenGLWidgetOSG3::onRecHeightRamp(int, QColor, QColor) {
	std::cout << "����" << std::endl;
}
void QtOpenGLWidgetOSG3::on_btnTest_clicked() {
	std::cout << "����2" << std::endl;
}