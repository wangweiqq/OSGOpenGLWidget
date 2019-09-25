#include "QtOpenGLWidgetOSG3.h"
#include "QtOSGWidget.h"
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
}
