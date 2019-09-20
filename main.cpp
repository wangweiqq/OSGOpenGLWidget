#include "QtOpenGLWidgetOSG3.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QGuiApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
	QApplication a(argc, argv);
	QtOpenGLWidgetOSG3 w;
	w.show();
	return a.exec();
}
