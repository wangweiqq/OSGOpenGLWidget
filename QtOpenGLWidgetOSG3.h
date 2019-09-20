#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtOpenGLWidgetOSG3.h"

class QtOpenGLWidgetOSG3 : public QMainWindow
{
	Q_OBJECT

public:
	QtOpenGLWidgetOSG3(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtOpenGLWidgetOSG3Class ui;
};
