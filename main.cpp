#include "QtOpenGLWidgetOSG3.h"
#include <QtWidgets/QApplication>

bool IsVerfyModelName(QString str) {
	if (str.isEmpty() || str.contains("TMP_")) {
		return false;
	}
	else {
		return true;
	}
}

int main(int argc, char *argv[])
{
	//qRegisterMetaType<std::map<unsigned int, osg::Vec3>>("std::map<unsigned int, osg::Vec3>");

	QGuiApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
	QApplication a(argc, argv);
	QtOpenGLWidgetOSG3 w;
	w.show();
	return a.exec();
}
