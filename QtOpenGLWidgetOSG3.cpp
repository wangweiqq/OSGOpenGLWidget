#include "QtOpenGLWidgetOSG3.h"
#include "QtOSGWidget.h"
QtOpenGLWidgetOSG3::QtOpenGLWidgetOSG3(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QtOSGWidget* widget = new QtOSGWidget();
	this->setCentralWidget(widget);
}
