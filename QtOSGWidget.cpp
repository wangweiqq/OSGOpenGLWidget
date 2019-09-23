#pragma execution_character_set("utf-8")
#ifdef _DEBUG
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"osgViewerd.lib")
#pragma comment(lib,"osgGAd.lib")
#pragma comment(lib,"osgDBd.lib")
#pragma comment(lib,"osgUtild.lib")
#else
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgViewer.lib")
#pragma comment(lib,"osgGA.lib")
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib,"osgUtil.lib")
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
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setViewport(0, 0, this->width(), this->height());
	camera->setClearColor(osg::Vec4(0.f, 0.f, 0.f, 0.f));
	/*float aspectRatio = static_cast<float>(this->width()) / static_cast<float>(this->height());
	camera->setProjectionMatrixAsPerspective(30.f, aspectRatio, 0.1f, 1000.f);*/
	camera->setProjectionMatrixAsPerspective(30, (double)this->width() / this->height(), 1, 1000);
	camera->setGraphicsContext(_mGraphicsWindow);

	//将摄像机关联到观察者
	_mViewer->setCamera(camera);
	
	osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;
	osg::ref_ptr<osgGA::FlightManipulator> manipulator2 = new osgGA::FlightManipulator;
	osg::ref_ptr<QtCameraManipulator> manipulator3 = new QtCameraManipulator;
	manipulator->setAllowThrow(false);
	_mViewer->setCameraManipulator(manipulator3);
	_mViewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
	_mViewer->realize();

	//setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);

	this->setMinimumSize(100, 100);
}

QtOSGWidget::~QtOSGWidget()
{
}
osg::ref_ptr<osg::Vec3Array> QtOSGWidget::ReadModelFile(std::string filePath) {
	osg::ref_ptr<osg::Vec3Array> list = new osg::Vec3Array;
	FILE* pfData = fopen(filePath.c_str(), "r");
	if (pfData == NULL) {
		return list;
	}
	while (!feof(pfData)) {
		float fx, fy, fz;
		std::fscanf(pfData, "%f", &fx);
		std::fscanf(pfData, "%f", &fy);
		std::fscanf(pfData, "%f", &fz);
		list->push_back(osg::Vec3f(fx, fy, fz));
	}
	fclose(pfData);
	//std::ifstream fileIn(filePath, std::ios::in);//读取文件
	//std::string line;//读取了每一行的字符

	//std::getline(fileIn, line);//获取第一行
	//std::stringstream sstr(line);//给他转一下
	//std::string token;
	/*bool rgbIsInt;
	int lineInNum = 0;
	while (getline(sstr, token, ' '))
	{
		lineInNum++;
		if (lineInNum >= 3)
		{
			if (stof(token) > 1)
			{
				rgbIsInt = true;
			}

		}

	}*/
	return list;
}
/**
设置OpenGL资源和状态
*/
void QtOSGWidget::initializeGL() {
	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Vec3Array> coords = ReadModelFile("model.txt");
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;

	geometry->setVertexArray(coords);
	int size1 = coords->size();
	int size2 = coords->referenceCount();
	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
	normals->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, coords->size()));

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geometry);
	root->addChild(geode.get());
	root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	


	//构造测试圆柱
	//osg::ref_ptr<osg::Cylinder> cylinder = new osg::Cylinder(osg::Vec3(0.f, 0.f, 0.f), 0.25f, 0.5f);
	//osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(cylinder);
	//sd->setName("zidingyi1");
	//sd->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0));
	////叶子节点
	//osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	//geode->addDrawable(sd);
	//root->addChild(geode);
	//osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();
	//osg::ref_ptr<osg::Material> material = new osg::Material;
	//material->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
	//stateSet->setAttributeAndModes(material, osg::StateAttribute::ON);

	//_mViewer->setSceneData(geode);
	//osg::ref_ptr<osg::Node> node = osgDB::readRefNodeFile("ceshi2.STL");
	//root->addChild(node);
	//_mViewer->setSceneData(node);

	
	//从观察者获取节点的方式
	//geode = dynamic_cast<osg::Geode*>(_mViewer->getSceneData());
	//设置OpenGL深度测试
	//stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

	//优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root);
	_mViewer->setSceneData(root);
	_mViewer->realize();
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