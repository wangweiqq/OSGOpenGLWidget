#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtOpenGLWidgetOSG3.h"
#include <QColor>
class QtOpenGLWidgetOSG3 : public QMainWindow
{
	Q_OBJECT

public:
	QtOpenGLWidgetOSG3(QWidget *parent = Q_NULLPTR);
signals:
	void sendHeightRamp(int axis, QColor beginColor, QColor endColor);
	//选1点
	void selCloudPoint(QtOSGWidget::MeauseCloud meause = QtOSGWidget::NONE);
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

	void onSelPoint();
	void onResetSelPoint();
	void onCancelSelPoint();
private:
	Ui::QtOpenGLWidgetOSG3Class ui;
	int axisdirect = 0;
	QColor begColor = Qt::green;
	QColor endColor = Qt::red;
};
