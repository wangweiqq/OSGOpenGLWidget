#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtOpenGLWidgetOSG3.h"
#include <QColor>
#include <QStandardItemModel>
class QtOpenGLWidgetOSG3 : public QMainWindow
{
	Q_OBJECT

public:
	QtOpenGLWidgetOSG3(QWidget *parent = Q_NULLPTR);
signals:
	void sendHeightRamp(int axis, QColor beginColor, QColor endColor);
	//选1点
	void selCloudPoint(MeauseCloud meause = MeauseCloud::NONE);
public slots:
	/**
		更改高度图样式
	*/
	void onChangedHightRamp();
	void onSelBeginColor();
	void onSelEndColor();
	void onShowHeightRamp();
	void onHideHeightRamp();
	void onSendHeightRamp();
	void onRecHeightRamp(int, QColor, QColor);

	void onSelPoint(QAbstractButton *button, bool checked);
	void onResetSelPoint();
	void onCancelSelPoint();
	void on_btnTest_clicked();


	void onFrameSelectResult(QString nodeName,std::map<unsigned int, osg::Vec3> list);
private:
	Ui::QtOpenGLWidgetOSG3Class ui;
	int axisdirect = 0;
	QColor begColor = Qt::green;
	QColor endColor = Qt::red;

	QButtonGroup* radGroup;

	QStandardItemModel* pTreeModel;
};
