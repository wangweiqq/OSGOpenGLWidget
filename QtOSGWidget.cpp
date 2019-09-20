#pragma execution_character_set("utf-8")
#ifdef _DEBUG
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"osgViewerd.lib")
#pragma comment(lib,"osgGAd.lib")
#else
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgViewer.lib")
#pragma comment(lib,"osgGA.lib")
#endif

#include "QtOSGWidget.h"
/**
1、创建图形上下文和图形窗口
2、将图形上下文附加到相机
3、将相机设置为主视图
*/
QtOSGWidget::QtOSGWidget(QWidget *parent)
	: QOpenGLWidget(parent),
	_mViewer(new osgViewer::Viewer),
	_mGraphicsWindow(new osgViewer::GraphicsWindowEmbedded(this->x(),this->y(),this->width(),this->height()))
{
	//创建一个主摄像头并附加图形上下文
	osg::Camera* camera = new osg::Camera;
	camera->setViewport(0, 0, this->width(), this->height());
	camera->setClearColor(osg::Vec4(0.9f, 0.9f, 1.f, 1.f));
	/*float aspectRatio = static_cast<float>(this->width()) / static_cast<float>(this->height());
	camera->setProjectionMatrixAsPerspective(30.f, aspectRatio, 0.1f, 1000.f);*/
	camera->setProjectionMatrixAsPerspective(30, (double)this->width() / this->height(), 1, 1000);
	camera->setGraphicsContext(_mGraphicsWindow);

	//将摄像机关联到观察者
	_mViewer->setCamera(camera);
	
	osgGA::TrackballManipulator* manipulator = new osgGA::TrackballManipulator;
	manipulator->setAllowThrow(false);
	_mViewer->setCameraManipulator(manipulator);
	_mViewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
	_mViewer->realize();

	//setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);

	this->setMinimumSize(100, 100);
}

QtOSGWidget::~QtOSGWidget()
{
}
/**
设置OpenGL资源和状态
*/
void QtOSGWidget::initializeGL() {
	//构造测试圆柱
	osg::Cylinder* cylinder = new osg::Cylinder(osg::Vec3(0.f, 0.f, 0.f), 0.25f, 0.5f);
	osg::ShapeDrawable*sd = new osg::ShapeDrawable(cylinder);
	sd->setName("zidingyi1");
	sd->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0));
	//叶子节点
	osg::Geode* geode = new osg::Geode;
	geode->addDrawable(sd);

	_mViewer->setSceneData(geode);
	
	//从观察者获取节点的方式
	geode = dynamic_cast<osg::Geode*>(_mViewer->getSceneData());
	osg::StateSet* stateSet = geode->getOrCreateStateSet();
	osg::Material* material = new osg::Material;
	material->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
	stateSet->setAttributeAndModes(material, osg::StateAttribute::ON);

	//设置OpenGL深度测试
	//stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
	glEnable(GL_DEPTH_TEST);
}
/**
在场景更新时渲染OpenGL
*/
void QtOSGWidget::paintGL() {
	_mViewer->frame();
}
/**
设置OpenGL视口，投影等
*/
void QtOSGWidget::resizeGL(int w, int h) {
	this->getEventQueue()->windowResize(this->x(), this->y(), w, h);
	_mGraphicsWindow->resized(this->x(), this->y(), w, h);
	osg::Camera* camera = _mViewer->getCamera();
	camera->setViewport(this->x(), this->y(), w, h);
}
/**
获取OSG事件队列
*/
osgGA::EventQueue* QtOSGWidget::getEventQueue()const {
	return _mGraphicsWindow->getEventQueue();
};
void QtOSGWidget::mouseDoubleClickEvent(QMouseEvent *event) {
	setKeyboardModifiers(event);
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton:
		button = 1;
		break;
	case Qt::MidButton:
		button = 2;
		break;
	case Qt::RightButton:
		button = 3;
		break;
	}
	getEventQueue()->mouseDoubleButtonPress(event->x(), event->y(), button);
	QOpenGLWidget::mouseDoubleClickEvent(event);
}
void QtOSGWidget::mouseMoveEvent(QMouseEvent *event) {
	setKeyboardModifiers(event);
	getEventQueue()->mouseMotion(event->x(), event->y());
	QOpenGLWidget::mouseMoveEvent(event);
}
void QtOSGWidget::mousePressEvent(QMouseEvent *event) {
	setKeyboardModifiers(event);
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton:
		button = 1;
		break;
	case Qt::MidButton:
		button = 2;
		break;
	case Qt::RightButton:
		button = 3;
		break;
	}
	getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
	QOpenGLWidget::mousePressEvent(event);
}
void QtOSGWidget::mouseReleaseEvent(QMouseEvent *event) {
	setKeyboardModifiers(event);
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton:
		button = 1;
		break;
	case Qt::MidButton:
		button = 2;
		break;
	case Qt::RightButton:
		button = 3;
		break;
	}
	getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);
	QOpenGLWidget::mouseReleaseEvent(event);
}
void QtOSGWidget::wheelEvent(QWheelEvent *event) {
	setKeyboardModifiers(event);
	getEventQueue()->mouseScroll(event->orientation() == Qt::Vertical ?
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT));
	QOpenGLWidget::wheelEvent(event);
}
bool QtOSGWidget::event(QEvent *event) {
	bool handled = QOpenGLWidget::event(event);
	switch (event->type())
	{
	case QEvent::MouseButtonPress:
	case QEvent::MouseButtonRelease:
	case QEvent::MouseMove:
	case QEvent::Wheel:
	case QEvent::MouseButtonDblClick:
	case QEvent::KeyPress:
	case QEvent::KeyRelease:
		this->update();
		break;
	default:
		break;
	}
	return handled;
}
void QtOSGWidget::setKeyboardModifiers(QInputEvent* event) {
	int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier);
	unsigned mask = 0;
	if (modkey & Qt::ShiftModifier) {
		mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
	}
	if (modkey & Qt::AltModifier) {
		mask |= osgGA::GUIEventAdapter::MODKEY_ALT;
	}
	if (modkey & Qt::ControlModifier) {
		mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;
	}
	getEventQueue()->getCurrentEventState()->setModKeyMask(mask);
}
void QtOSGWidget::keyPressEvent(QKeyEvent *event) {
	setKeyboardModifiers(event);
	//QByteArray KeyData = event->text().toLocal8Bit();
	/*const char* cKey = KeyData.data();
	osgGA::GUIEventAdapter::KeySymbol symbol = osgGA::GUIEventAdapter::KeySymbol(event->key());*/
	//getEventQueue()->keyPress();
	switch (event->key())
	{
	case Qt::Key_F:
	{
		//从观察者获取节点的方式
		osg::Geode* geode = dynamic_cast<osg::Geode*>(_mViewer->getSceneData());
		int count = geode->getNumDrawables();
		for (int i = 0; i < count; ++i) {
			osg::ShapeDrawable* draw = dynamic_cast<osg::ShapeDrawable*> (geode->getDrawable(i));
			std::string name = draw->getName();
			if (name == "zidingyi1") {
				draw->setColor(osg::Vec4(0.0, 1.0, 0.0, 1.0));
			}
		}
	}
		break;
	case Qt::Key_D:
	{
		//从观察者获取节点的方式
		osg::Geode* geode = dynamic_cast<osg::Geode*>(_mViewer->getSceneData());
		int count = geode->getNumDrawables();
		for (int i = 0; i < count; ++i) {
			osg::Drawable* draw = geode->getDrawable(i);
			std::string name = draw->getName();
			if (name == "zidingyi1") {
				geode->removeDrawable(draw);
			}
		}
	}
		break;
	default:
		break;
	}
	QOpenGLWidget::keyPressEvent(event);
}
void QtOSGWidget::keyReleaseEvent(QKeyEvent *event) {
	setKeyboardModifiers(event);

	QOpenGLWidget::keyReleaseEvent(event);
}