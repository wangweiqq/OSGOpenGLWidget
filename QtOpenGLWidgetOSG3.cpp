#pragma execution_character_set("utf-8")
#include "QtOpenGLWidgetOSG3.h"
#include "OSGWidget.h"
#include <QColorDialog>
#include <QButtonGroup>
#include <QStandardItem>
#include "CloudOperator.h"
#include <osg/Vec3>
#include <QVector3D>
QtOpenGLWidgetOSG3::QtOpenGLWidgetOSG3(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	pTreeModel = new QStandardItemModel(ui.treeView);
	ui.treeView->setModel(pTreeModel);
	ui.treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	pTreeModel->setHorizontalHeaderLabels(QStringList() << "模型节点");
	/*QtOSGWidget* widget = new QtOSGWidget();
	this->setCentralWidget(widget);*/
	this->ui.btnCloud->hide();
	this->ui.btnCylinder->hide();
	this->ui.btnGlider->hide();
	this->ui.btnQuad->hide();
	this->ui.btnShape->hide();
	this->ui.btnClear->hide();
	this->ui.btnTest->hide();

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
	radGroup->addButton(this->ui.radSelPoints);

	connect(radGroup, SIGNAL(buttonToggled(QAbstractButton*,bool)), this, SLOT(onSelPoint(QAbstractButton*, bool)));
	/*connect(this->ui.radSelPoint, SIGNAL(toggled(bool )), this, SLOT(onSelPoint(bool)));
	connect(this->ui.radMeasure, SIGNAL(toggled(bool )), this, SLOT(onSelPoint(bool)));*/
	connect(this->ui.btnReset, SIGNAL(clicked()), this, SLOT(onResetSelPoint()));
	connect(this->ui.btnCancel, SIGNAL(clicked()), this, SLOT(onCancelSelPoint()));

	connect(this, SIGNAL(selCloudPoint(MeauseCloud)), this->ui.openGLWidget, SLOT(onSelCloudPoint(MeauseCloud)));

	connect(this->ui.btnTest, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onTest()));


	connect(this->ui.openGLWidget, SIGNAL(FrameSelectPoints(QString,std::map<unsigned int, osg::Vec3>)), this, SLOT(onFrameSelectResult(QString, std::map<unsigned int, osg::Vec3>)));


	//视图模式
	connect(this->ui.btnTopView, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onTopViewChanged()));
	connect(this->ui.btnFrontView, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onFrontViewChanged()));
	connect(this->ui.btnLeftView, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onLeftViewChanged()));
	connect(this->ui.btnRearView, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onRearViewChanged()));
	connect(this->ui.btnRightView, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onRightViewChanged()));
	connect(this->ui.btnBottomView, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onBottomViewChanged()));
	connect(this->ui.btnFrontView2, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onFront2ViewChanged()));
	connect(this->ui.btnBackView2, SIGNAL(clicked()), this->ui.openGLWidget, SLOT(onBack2ViewChanged()));
}
void QtOpenGLWidgetOSG3::onSelPoint(QAbstractButton *button, bool checked) {
	if (checked) {
		if (this->ui.radSelPoint == button) {
			emit selCloudPoint(MeauseCloud::ONEPOINT);
		}
		else if (this->ui.radMeasure == button) {
			emit selCloudPoint(MeauseCloud::TWOMEAUSE);
		}
		else if (this->ui.radSelPoints == button) {
			emit selCloudPoint(MeauseCloud::BOXSELPOINTS);
		}
	}
}
void QtOpenGLWidgetOSG3::onResetSelPoint() {
	radGroup->setExclusive(false);
	this->ui.radSelPoint->setChecked(false);
	this->ui.radMeasure->setChecked(false);
	this->ui.radSelPoints->setChecked(false);
	radGroup->setExclusive(true);
	emit selCloudPoint(MeauseCloud::RESET);
}
void QtOpenGLWidgetOSG3::onCancelSelPoint() {
	radGroup->setExclusive(false);
	this->ui.radSelPoint->setChecked(false);
	this->ui.radMeasure->setChecked(false);
	this->ui.radSelPoints->setChecked(false);
	radGroup->setExclusive(true);
	emit selCloudPoint(MeauseCloud::NONE);
}

void QtOpenGLWidgetOSG3::onShowHeightRamp() {

}
void QtOpenGLWidgetOSG3::onHideHeightRamp() {

}
void QtOpenGLWidgetOSG3::onChangedHightRamp() {

}
void QtOpenGLWidgetOSG3::onSelBeginColor() {
	 QColor color = QColorDialog::getColor(begColor,this,"选择起始颜色");
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
	QColor color = QColorDialog::getColor(endColor, this, "选择结束颜色");
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
	std::cout << "测试" << std::endl;
}
void QtOpenGLWidgetOSG3::on_btnTest_clicked() {
	std::cout << "测试2" << std::endl;
}

void  QtOpenGLWidgetOSG3::onFrameSelectResult(QString nodeName, std::map<unsigned int, osg::Vec3> list) {
	//std::cout << "onFrameSelectResult = " << nodeName.toLocal8Bit().data()<<",size = " <<list.size() << std::endl;
	pTreeModel->clear();
	pTreeModel->setHorizontalHeaderLabels(QStringList() << "模型节点");
	QStandardItem* root = new QStandardItem(nodeName);
	pTreeModel->appendRow(root);
	for (auto it = list.begin(); it != list.end(); ++it) {
		QStandardItem* item = new QStandardItem(QString("#%1").arg((*it).first));
		osg::Vec3 v = (*it).second;
		QVector3D v3(v.x(), v.y(), v.z());
		item->setData(v3,Qt::UserRole);
		root->appendRow(item);
	}
	ui.treeView->expandAll();
}