#pragma execution_character_set("utf-8")
#ifdef _DEBUG
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"osgViewerd.lib")
#pragma comment(lib,"osgGAd.lib")
#pragma comment(lib,"osgDBd.lib")
#pragma comment(lib,"osgUtild.lib")
#pragma comment(lib,"osgTextd.lib")
#pragma comment(lib,"osgWidgetd.lib")
#else
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgViewer.lib")
#pragma comment(lib,"osgGA.lib")
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib,"osgUtil.lib")
#pragma comment(lib,"osgText.lib")
#pragma comment(lib,"osgWidget.lib")
#endif

#include "OSGWidget.h"
/**
1、创建图形上下文和图形窗口
2、将图形上下文附加到相机
3、将相机设置为主视图
*/
OSGWidget::OSGWidget(QWidget *parent)
	: QOpenGLWidget(parent),
	_mViewer(new osgViewer::Viewer),
	_mGraphicsWindow(new osgViewer::GraphicsWindowEmbedded(this->x(),this->y(),this->width(),this->height()))
{
	//setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);
	this->setMinimumSize(100, 100);
}

OSGWidget::~OSGWidget()
{
}
/**
设置OpenGL资源和状态
*/
void OSGWidget::initializeGL() {
	//创建一个主摄像头并附加图形上下文
	//osg::ref_ptr<osg::Camera> camera = new osg::Camera();
	//camera->setViewport(0, 0, this->width(), this->height());
	//camera->setClearColor(osg::Vec4(0.9f, 0.8f, 0.0f, 1.0f));
	///*float aspectRatio = static_cast<float>(this->width()) / static_cast<float>(this->height());
	//camera->setProjectionMatrixAsPerspective(30.f, aspectRatio, 0.1f, 1000.f);*/
	//camera->setProjectionMatrixAsPerspective(30, (double)this->width() / this->height(), 1, 1000);
	//camera->setGraphicsContext(_mGraphicsWindow.get());
	////将摄像机关联到观察者
	//_mViewer->setCamera(camera.get());

	osg::Camera* camera = _mViewer->getCamera();
	camera->setClearColor(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));
	//camera->setClearColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	camera->setProjectionMatrixAsPerspective(30, (double)this->width() / this->height(), 1, 1000);
	camera->setViewport(0, 0, this->width(), this->height());
	camera->setGraphicsContext(_mGraphicsWindow.get());
	//这是因为默认把小物体裁剪掉了，因此需要添加下面代码：
	osg::CullStack::CullingMode cullingMode = camera->getCullingMode();
	cullingMode &= ~(osg::CullStack::SMALL_FEATURE_CULLING);
	camera->setCullingMode(cullingMode);

	/*osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator();
	osg::ref_ptr<osgGA::FlightManipulator> manipulator2 = new osgGA::FlightManipulator;*/
	osg::ref_ptr<OSGCameraManipulator> manipulator = new OSGCameraManipulator;
	manipulator->setAllowThrow(false);
	_mViewer->setCameraManipulator(manipulator.get());
	//该事件可控制状态如W键：显示模型网格，S键显示帧速
	_mViewer->addEventHandler(new osgViewer::StatsHandler);
	//_mViewer->addEventHandler(new osgViewer::ThreadingHandler());
	//_mViewer->addEventHandler(new osgViewer::HelpHandler);
	//该事件可触发L键控制灯光
	_mViewer->addEventHandler(new osgGA::StateSetManipulator(_mViewer->getCamera()->getOrCreateStateSet()));
	//_mViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
	_mViewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
	_mViewer->realize();

	
	//osg::ref_ptr<osg::Group> pGroup = _mViewer->getSceneData()->asGroup();
	osg::ref_ptr<osg::Group> root =  new osg::Group();
	
	QByteArray barr = QString("root").toLocal8Bit();
	char* bdata = barr.data();
	root->setName(bdata);

	

	//std::cout << root->getName() << std::endl;
	//osgUtil::Optimizer optimizer;
	//optimizer.optimize(root.get());
	//_mViewer->setSceneData(root);
	//_mViewer->realize();
	//root->addChild(createQuad().get());
	mCurObject = createCloud();
	root->addChild(mCurObject);
	//root->addChild(createHUD(_mViewer));
	//root->addChild(createCoordinate().get());
	//root->addChild(createShape().get());

	//从观察者获取节点的方式
	//geode = dynamic_cast<osg::Geode*>(_mViewer->getSceneData());
	//设置OpenGL深度测试
	//stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

	//优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());
	_mViewer->setSceneData(root);
	_mViewer->realize();
	//glEnable(GL_DEPTH_TEST);

	//OSGPickHandler* handler = new OSGPickHandler(_mViewer);
	//handler->DrawTips(osg::Vec3(-202.414, 961, 70.0564));
	//
	////世界坐标转屏幕坐标
	//osg::Camera* _tCamera = _mViewer->getCamera();
	//osg::Matrix VPW = _tCamera->getViewMatrix() *
	//	_tCamera->getProjectionMatrix() *
	//	_tCamera->getViewport()->computeWindowMatrix();
	//osg::Vec3 window = osg::Vec3(-202.414f, 961.0f, 70.0564f) * VPW;
	//std::cout << "2.(" << window.x() << "," << window.y() << "," << window.z() << ")" << std::endl;
	//std::cout << "screen 2" << this->width() << "," << this->height() << std::endl;
}
/**
在场景更新时渲染OpenGL
*/
void OSGWidget::paintGL() {
	/*if (_mPickHandler.valid()) {
		_mPickHandler->UpdateBoard();
	}*/
	_mViewer->frame();
	//osg::Group* group = _mViewer->getSceneData()->asGroup();
	//for (int i = 0; i < group->getNumChildren(); ++i) {
	//	osg::Node* n = group->getChild(i);
	//	if (n->getName() == "ULDCamera") {
	//		osg::Camera* cam = n->asCamera();
	//		osg::Matrix viewMatr = cam->getViewMatrix();
	//		osg::Matrix ProjectionM = cam->getProjectionMatrix();
	//		osg::Matrix WindowMatrix = cam->getViewport()->computeWindowMatrix();
	//		osg::Matrix VPW = cam->getViewMatrix() *
	//			cam->getProjectionMatrix() *
	//			cam->getViewport()->computeWindowMatrix();
	//		double left, right, top, bottom, dnear, dfar;
	//		cam->getProjectionMatrixAsOrtho(left, right, bottom, top, dnear, dfar);
	//		std::cout << i << cam->getName() << "ViewPort" << cam->getViewport()->x()
	//			<< "," << cam->getViewport()->y() << "," << cam->getViewport()->width() << ", ortho2d = " <<
	//			left << "," << right << "," << bottom << "," << top << "," << dnear << "," << dfar << ", Mask"
	//			<< cam->getNodeMask() << std::endl;

	//		
	//		for (int j = 0; j < cam->getNumChildren(); ++j) {
	//			osg::Geode* ge = cam->getChild(j)->asGeode();
	//			for (int z = 0; z < ge->getNumDrawables(); z++) {
	//				std::cout << ge->getName() << std::endl;
	//				osg::Geometry* geo = ge->getDrawable(z)->asGeometry();
	//				if (geo && geo->getName() == "BoxPanel") {
	//					osg::Vec3Array* vec = dynamic_cast<osg::Vec3Array*>(geo->getVertexArray());
	//					for (int zz = 0; zz < vec->size(); ++zz) {
	//						std::cout << "boxpoint :" << vec->at(zz).x()<<","<< vec->at(zz).y()<<","<< vec->at(zz).z() << std::endl;
	//					}
	//				}
	//			}
	//		}
	//	}
	//	/*std::cout << n->getName()<<","<<n->className() << std::endl;
	//	std::cout << std::endl;*/
	//}
	//std::cout << " OSGWidget::paintGL" << std::endl;
}
/**
设置OpenGL视口，投影等
*/
void OSGWidget::resizeGL(int w, int h) {
	this->getEventQueue()->windowResize(this->x(), this->y(), w, h);
	_mGraphicsWindow->resized(this->x(), this->y(), w, h);
	osg::Camera* camera = _mViewer->getCamera();
	//camera->setViewport(this->x(), this->y(), w, h);
	//以下两个方法顺序
	camera->setProjectionMatrixAsPerspective(30, (double)w / h, 1, 1000);
	camera->setViewport(0, 0, w, h);


	////世界坐标转屏幕坐标
	//osg::Camera* _tCamera = _mViewer->getCamera();
	//osg::Matrix VPW = _tCamera->getViewMatrix() *
	//	_tCamera->getProjectionMatrix() *
	//	_tCamera->getViewport()->computeWindowMatrix();
	//osg::Vec3 window = osg::Vec3(-202.414f, 961.0f, 70.0564f) * VPW;
	//std::cout << "3.(" << window.x() << "," << window.y() << "," << window.z() << ")" << std::endl;
}
/**
获取OSG事件队列
*/
osgGA::EventQueue* OSGWidget::getEventQueue()const {
	return _mGraphicsWindow->getEventQueue();
};
void OSGWidget::mouseDoubleClickEvent(QMouseEvent *event) {
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
void OSGWidget::mouseMoveEvent(QMouseEvent *event) {
	setKeyboardModifiers(event);
	getEventQueue()->mouseMotion(event->x(), event->y());
	QOpenGLWidget::mouseMoveEvent(event);
}
void OSGWidget::mousePressEvent(QMouseEvent *event) {
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
	std::cout << "qt mouse click = ("<<event->x()<<","<<event->y()<<")" << std::endl;
	getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
	QOpenGLWidget::mousePressEvent(event);
}
void OSGWidget::mouseReleaseEvent(QMouseEvent *event) {
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
void OSGWidget::wheelEvent(QWheelEvent *event) {
	setKeyboardModifiers(event);
	getEventQueue()->mouseScroll(event->orientation() == Qt::Vertical ?
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT));
	getEventQueue()->mouseButtonPress(event->x(), event->y(), 3);
	QOpenGLWidget::wheelEvent(event);
}
bool OSGWidget::event(QEvent *event) {
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
void OSGWidget::setKeyboardModifiers(QInputEvent* event) {
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
void OSGWidget::keyPressEvent(QKeyEvent *event) {
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
	case Qt::Key_S:
	{
		getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_S);
	}
	break;
	case Qt::Key_L:
	{
		getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_L);
	}
	break;
	case Qt::Key_W:
	{
		getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_W);
	}
	break;
	case Qt::Key_Space:
	{
		//返回Home键，
		getEventQueue()->keyPress(osgGA::GUIEventAdapter::KEY_Space);
	}
	break;
	default:
		break;
	}
	QOpenGLWidget::keyPressEvent(event);
}
void OSGWidget::keyReleaseEvent(QKeyEvent *event) {
	setKeyboardModifiers(event);

	QOpenGLWidget::keyReleaseEvent(event);
}
//点云测量
void OSGWidget::onSelCloudPoint(MeauseCloud meause) {
	switch (meause)
	{
	case MeauseCloud::RESET:
	{
		if (_mPickHandler.valid()) {
			_mPickHandler->Reset();
			this->update();
		}
	}
		break;
	case MeauseCloud::ONEPOINT://选点云上一点
	{
		if (!_mPickHandler.valid()) {
			_mPickHandler = new OSGPickHandler(_mViewer);
			_mViewer->addEventHandler(_mPickHandler);
		}
		_mPickHandler->OnePoint();
	}
		break;
	case MeauseCloud::TWOMEAUSE://测量两点距离
	{
		if (!_mPickHandler.valid()) {
			_mPickHandler = new OSGPickHandler(_mViewer);
			_mViewer->addEventHandler(_mPickHandler);
		}		
		_mPickHandler->TwoMeause();
	}
		break;
	case MeauseCloud::BOXSELPOINTS://框选，选择一系列点
		if (!_mPickHandler.valid()) {
			_mPickHandler = new OSGPickHandler(_mViewer);
			_mPickHandler->mFrameSelectCallBack = std::bind(&OSGWidget::FrameSelectResult,this,std::placeholders::_1,std::placeholders::_2);
			//_mPickHandler->mCallback = std::bind(&OSGWidget::TestCallBack, this);
			_mViewer->addEventHandler(_mPickHandler);
		}
		_mPickHandler->FrameSelPoints();
		break;
	case MeauseCloud::NONE:
	default:
		if (_mPickHandler.valid()) {
			_mViewer->removeEventHandler(_mPickHandler);
			_mPickHandler.~ref_ptr();
		}
		this->update();
		break;
	}
	this->update();
}
void OSGWidget::TestCallBack() {

}
void OSGWidget::FrameSelectResult(QString nodeName, std::map<unsigned int, osg::Vec3> list) {
	std::cout << "FrameSelectResult size = " << list.size() << std::endl;
	emit FrameSelectPoints(nodeName,list);
}
void OSGWidget::onCylinder() {
	osg::ref_ptr<osg::Group> pGroup = _mViewer->getSceneData()->asGroup();
	osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(_mViewer->getSceneData());
	bool isEmpty = false;
	if (!root.valid()) {
		isEmpty = true;
		root = new osg::Group;
	}
	osg::ref_ptr<osg::Node> node = createCylinder();
	root->addChild(node.get());
	_mViewer->setSceneData(NULL);
	//computeNodePosition(node.get(), _mViewer->getCamera(), false);
	//if (isEmpty) {
		//优化场景数据
		osgUtil::Optimizer optimizer;
		optimizer.optimize(root.get());
		_mViewer->setSceneData(root);
		_mViewer->realize();
	//}
	this->update();
}
void OSGWidget::onQuad() {
	osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(_mViewer->getSceneData());
	bool isEmpty = false;
	if (!root.valid()) {
		isEmpty = true;
		root = new osg::Group;
	}
	osg::ref_ptr<osg::Node> node = createQuad();
	root->addChild(node.get());
	_mViewer->setSceneData(NULL);
	//computeNodePosition(node.get(), _mViewer->getCamera(), false);
	//if (isEmpty) {
		//优化场景数据
		osgUtil::Optimizer optimizer;
		optimizer.optimize(root.get());
		_mViewer->setSceneData(root);
		_mViewer->realize();
	//}
	this->update();
}
void OSGWidget::onCloud() {
	osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(_mViewer->getSceneData());
	bool isEmpty = false;
	if (!root.valid()) {
		isEmpty = true;
		root = new osg::Group;
	}
	osg::ref_ptr<osg::Node> node = createCloud();
	root->addChild(node.get());
	//osg::BoundingSphere bound = node->getBound();
	//std::cout << "x = " << bound.center().x() << ",y = " << bound.center().y() << ",z = " << bound.center().z() << ", R  = " << bound.radius() << std::endl;
	_mViewer->setSceneData(NULL);
	_mViewer->setSceneData(root);
	//_mViewer->setCameraManipulator(NULL);
	////computeNodePosition(node.get(), _mViewer->getCamera(), false);
	//osg::ref_ptr<OSGCameraManipulator> manipulator = new OSGCameraManipulator;
	//manipulator->setAllowThrow(false);
	//_mViewer->setCameraManipulator(manipulator.get());
	//if (isEmpty) {
		//优化场景数据
		/*osgUtil::Optimizer optimizer;
		optimizer.optimize(root.get());
		_mViewer->setSceneData(root);
		_mViewer->realize();*/
	//}
	//computeNodePosition(node.get(), _mViewer->getCamera(), false);
	/*_mViewer->getCamera()->setViewMatrixAsLookAt(osg::Vec3(1000,1000,2000),
		osg::Vec3(1000, 1000, 1000),
		osg::Vec3d(0.0f, 0.0f, 1.0f)
		);*/
	this->update();
}
void OSGWidget::onShape() {
	osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(_mViewer->getSceneData());
	bool isEmpty = false;
	if (!root.valid()) {
		isEmpty = true;
		root = new osg::Group;
	}
	osg::ref_ptr<osg::Node> node = createShape();
	root->addChild(node.get());
	_mViewer->setSceneData(NULL);
	//computeNodePosition(node.get(), _mViewer->getCamera(), false);
	//if (isEmpty) {
		//优化场景数据
		osgUtil::Optimizer optimizer;
		optimizer.optimize(root.get());
		_mViewer->setSceneData(root);
		_mViewer->realize();
	//}
	this->update();
}
void OSGWidget::onGlider() {
	osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(_mViewer->getSceneData());
	bool isEmpty = false;
	if (!root.valid()) {
		isEmpty = true;
		root = new osg::Group;
	}
	osg::ref_ptr<osg::Node> node = createOSGGlider();
	root->addChild(node.get());
	_mViewer->setSceneData(NULL);
	//computeNodePosition(node.get(), _mViewer->getCamera(), false);
	//if (isEmpty) {
		//优化场景数据
		osgUtil::Optimizer optimizer;
		optimizer.optimize(root.get());
		_mViewer->setSceneData(root);
		_mViewer->realize();
	//}
	this->update();
}
//class DelAllNodeVistor :public osg::NodeVisitor {
//public:
//	DelAllNodeVistor(osg::Group* node) :osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {
//		root = node;
//	}
//	/*virtual void apply(osg::Group& node) {
//		std::string name = node.getName();
//		std::cout <<"Group : " <<name << std::endl;
//	}*/
//	virtual void apply(osg::Node& node) {
//		if (node.getName() == "root") {
//			traverse(node);
//		}
//		else {
//			std::string name = node.getName();
//			std::cout << "Node : " << name << std::endl;
//			root->removeChild(&node);
//		}
//	}
//	/*virtual void apply(osg::Geode& node) {
//		std::string name = node.getName();
//		std::cout << "Geode : " << name << std::endl;
//		traverse(node);
//	}
//	virtual void apply(osg::Geometry& geometry) {
//		std::string name = geometry.getName();
//		std::cout << "Geometry : " << name << std::endl;
//		traverse(geometry);
//	}*/
//private:
//	osg::ref_ptr<osg::Group> root;
//};
void OSGWidget::onClear() {
	osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(_mViewer->getSceneData());
	if (root.valid()) {
		/*DelAllNodeVistor vistor(root.get());
		root->accept(vistor);*/
		int childCount = root->getNumChildren();
		for (int i = childCount - 1; i >= 0; --i) {
			root->removeChild(i);
		}
	}
	//_mViewer->realize();
	//root->accept(DelAllNodeVistor());
	this->update();
}
void OSGWidget::onRecHeightRamp(int axis, QColor beginColor, QColor endColor) {
	osg::Geode* cloudGeode = dynamic_cast<osg::Geode*>(getChildNode("CloudPoints"));
	if (cloudGeode == nullptr) {
		return;
	}
	osg::Vec3 direct = osg::X_AXIS;
	switch (axis)
	{
	case 1:
		direct = osg::X_AXIS;
		break;
	case 2:
		direct = osg::Y_AXIS;
		break;
	case 3:
		direct = osg::Z_AXIS;
		break;
	}
	qreal r, g, b;
	beginColor.getRgbF(&r, &g, &b);
	//开始颜色
	osg::Vec4 bcolor(r, g, b, 1.0f);
	endColor.getRgbF(&r, &g, &b);
	//结束颜色
	osg::Vec4 ecolor(r, g, b, 1.0f);
	ChangedCloudColor(cloudGeode, direct, bcolor, ecolor);
}
void OSGWidget::computeNodePosition(osg::Node* node, const osg::Camera *camera, bool useBoundingBox) {
	/*_mViewer->getCameraManipulator()->computeHomePosition(camera);
	return;*/
		osg::BoundingSphere boundingSphere;

		//OSG_INFO << " CameraManipulator::computeHomePosition(" << camera << ", " << useBoundingBox << ")" << std::endl;

		if (useBoundingBox)
		{
			// compute bounding box
			// (bounding box computes model center more precisely than bounding sphere)
			osg::ComputeBoundsVisitor cbVisitor;
			node->accept(cbVisitor);
			osg::BoundingBox &bb = cbVisitor.getBoundingBox();

			if (bb.valid()) boundingSphere.expandBy(bb);
			else boundingSphere = node->getBound();
		}
		else
		{
			// compute bounding sphere
			boundingSphere = node->getBound();
		}

		/*OSG_INFO << "    boundingSphere.center() = (" << boundingSphere.center() << ")" << std::endl;
		OSG_INFO << "    boundingSphere.radius() = " << boundingSphere.radius() << std::endl;*/

		double radius = osg::maximum(double(boundingSphere.radius()), 1e-6);

		// set dist to default
		double dist = 3.5f * radius;

		if (camera)
		{

			// try to compute dist from frustum
			double left, right, bottom, top, zNear, zFar;
			if (camera->getProjectionMatrixAsFrustum(left, right, bottom, top, zNear, zFar))
			{
				double vertical2 = fabs(right - left) / zNear / 2.;
				double horizontal2 = fabs(top - bottom) / zNear / 2.;
				double dim = horizontal2 < vertical2 ? horizontal2 : vertical2;
				double viewAngle = atan2(dim, 1.);
				dist = radius / sin(viewAngle);
			}
			else
			{
				// try to compute dist from ortho
				if (camera->getProjectionMatrixAsOrtho(left, right, bottom, top, zNear, zFar))
				{
					dist = fabs(zFar - zNear) / 2.;
				}
			}
		}
		osg::ref_ptr<osg::Geode> geode = new osg::Geode();
		osg::ComputeBoundsVisitor boundVisitor;
		node->accept(boundVisitor);
		osg::BoundingBox boundingBox = boundVisitor.getBoundingBox();
		float length = boundingBox.xMax() - boundingBox.xMin();
		float width = boundingBox.yMax() - boundingBox.yMin();
		float height = boundingBox.zMax() - boundingBox.zMin();
		osg::Vec3 direct = osg::X_AXIS;
		if (length <= width && length <= height) {
			direct = osg::X_AXIS;
		}
		else if (width <= length && width <= height) {
			direct = osg::Y_AXIS;
		}
		else {
			direct = osg::Z_AXIS;
		}
		osg::Vec3f cesh = boundingSphere.center();
		_mViewer->getCamera()->setViewMatrixAsLookAt(boundingSphere.center() + direct* dist,
			boundingSphere.center(),
			osg::Vec3d(0.0f, 0.0f, 1.0f)
			);
		/*_mViewer->getCameraManipulator()->setHomePosition(boundingSphere.center() + direct* dist,
			boundingSphere.center(),
			osg::Vec3d(0.0f, 0.0f, 1.0f),
			true);*/
}

//顶视图
void OSGWidget::onTopViewChanged() {
	if (!mCurObject.valid()) {
		return;
	}
	const osg::BoundingSphere& bs = mCurObject->getBound();
	osg::Matrixd md;
	md.makeLookAt(bs.center() + osg::Z_AXIS*3.5f*bs.radius(), bs.center(),osg::Y_AXIS);
	_mViewer->getCameraManipulator()->setByInverseMatrix(md);
	this->update();
	std::cout << "onTopViewChanged" << std::endl;
}
//前视图
void OSGWidget::onFrontViewChanged() {
	if (!mCurObject.valid()) {
		return;
	}
	const osg::BoundingSphere& bs = mCurObject->getBound();
	osg::Matrixd md;
	md.makeLookAt(bs.center() - osg::Y_AXIS*3.5f*bs.radius(), bs.center(), osg::Z_AXIS);
	_mViewer->getCameraManipulator()->setByInverseMatrix(md);
	this->update();
	std::cout << "onFrontViewChanged" << std::endl;
}
//左视图
void OSGWidget::onLeftViewChanged() {
	if (!mCurObject.valid()) {
		return;
	}
	const osg::BoundingSphere& bs = mCurObject->getBound();
	osg::Matrixd md;
	md.makeLookAt(bs.center() - osg::X_AXIS*3.5f*bs.radius(), bs.center(), osg::Z_AXIS);
	_mViewer->getCameraManipulator()->setByInverseMatrix(md);
	this->update();
	std::cout << "onRearViewChanged" << std::endl;
}
//后视图
void OSGWidget::onRearViewChanged() {
	if (!mCurObject.valid()) {
		return;
	}
	const osg::BoundingSphere& bs = mCurObject->getBound();
	osg::Matrixd md;
	md.makeLookAt(bs.center() + osg::Y_AXIS*3.5f*bs.radius(), bs.center(), osg::Z_AXIS);
	_mViewer->getCameraManipulator()->setByInverseMatrix(md);
	this->update();
	std::cout << "onRearViewChanged" << std::endl;
}
//右视图
void OSGWidget::onRightViewChanged() {
	if (!mCurObject.valid()) {
		return;
	}
	const osg::BoundingSphere& bs = mCurObject->getBound();
	osg::Matrixd md;
	md.makeLookAt(bs.center() + osg::X_AXIS*3.5f*bs.radius(), bs.center(), osg::Z_AXIS);
	_mViewer->getCameraManipulator()->setByInverseMatrix(md);
	this->update();
	std::cout << "onRearViewChanged" << std::endl;
}
//底视图
void OSGWidget::onBottomViewChanged() {
	if (!mCurObject.valid()) {
		return;
	}
	const osg::BoundingSphere& bs = mCurObject->getBound();
	osg::Matrixd md;
	md.makeLookAt(bs.center() - osg::Z_AXIS*3.5f*bs.radius(), bs.center(), osg::Y_AXIS);
	_mViewer->getCameraManipulator()->setByInverseMatrix(md);
	this->update();
	std::cout << "onBottomViewChanged" << std::endl;
}
//前视图2
void OSGWidget::onFront2ViewChanged() {
	if (!mCurObject.valid()) {
		return;
	}
	const osg::BoundingSphere& bs = mCurObject->getBound();
	osg::Matrixd md;
	osg::Vec3 v = osg::Vec3(-1.0f, -1.0f, 1.0f);
	v.normalize();
	md.makeLookAt(bs.center() + v*3.5f*bs.radius(), bs.center(), osg::Vec3(1.0f, 1.0f, 1.0f));
	_mViewer->getCameraManipulator()->setByInverseMatrix(md);
	this->update();
	std::cout << "onFront2ViewChanged" << std::endl;
}
//后视图2
void OSGWidget::onBack2ViewChanged() {
	if (!mCurObject.valid()) {
		return;
	}
	const osg::BoundingSphere& bs = mCurObject->getBound();
	osg::Matrixd md;
	osg::Vec3 v = osg::Vec3(1.0f, 1.0f, 1.0f);
	v.normalize();
	md.makeLookAt(bs.center() + v*3.5f*bs.radius(), bs.center(), osg::Vec3(-1.0f, -1.0f, 1.0f));
	_mViewer->getCameraManipulator()->setByInverseMatrix(md);
	this->update();
	std::cout << "onBack2ViewChanged" << std::endl;
}


/**
度点云文件
*/
//float minX, maxX, minY, maxY, minZ, maxZ;
double minX, maxX, minY, maxY, minZ, maxZ;
osg::ref_ptr<osg::Vec3Array> OSGWidget::ReadModelFile(std::string filePath) {
//osg::ref_ptr<osg::Vec3dArray> OSGWidget::ReadModelFile(std::string filePath) {
	osg::ref_ptr<osg::Vec3Array> list = new osg::Vec3Array;
	//osg::ref_ptr<osg::Vec3dArray> list = new osg::Vec3dArray;
	FILE* pfData = fopen(filePath.c_str(), "r");
	if (pfData == NULL) {
		return list;
	}
	bool first = true;
	while (!feof(pfData)) {
		/*float fx, fy, fz;
		std::fscanf(pfData, "%f", &fx);
		std::fscanf(pfData, "%f", &fy);
		std::fscanf(pfData, "%f", &fz);*/
		double fx, fy, fz;
		std::fscanf(pfData, "%lf", &fx);
		std::fscanf(pfData, "%lf", &fy);
		std::fscanf(pfData, "%lf", &fz);
		if (first) {
			minX = maxX = fx;
			minY = maxY = fy;
			minZ = maxZ = fz;
			first = false;
		}
		else {
			minX = std::min(minX, fx);
			maxX = std::max(maxX, fx);
			minY = std::min(minY, fy);
			maxY = std::max(maxY, fy);
			minZ = std::min(minZ, fz);
			maxZ = std::max(maxZ, fz);
		}
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
//创建四边形
osg::ref_ptr<osg::Node> OSGWidget::createQuad() {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	QByteArray barr = QString("TMP_四边形").toLocal8Bit();
	char* bdata = barr.data();
	geode->setName(bdata);
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();


	osg::ref_ptr<osg::StateSet> stateSet = geom->getOrCreateStateSet();
	osg::ref_ptr<osg::Point> pointSize = new osg::Point;
	pointSize->setSize(10.0);
	stateSet->setAttribute(pointSize, osg::StateAttribute::OFF);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	stateSet->setMode(GL_POINT_SPRITE_ARB, osg::StateAttribute::ON);
	geom->setStateSet(stateSet);
	//osg::PointSprite *sprite = new osg::PointSprite();
	//stateSet->setTextureAttributeAndModes(0, sprite, osg::StateAttribute::ON);

	//创建顶点数组，注意顺序逆时针
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(-202.414, 961, 70.0564));
	//v->push_back(osg::Vec3(0.0, 0.0, 0.0));
	//v->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	////stateSet->setAttribute(pointSize, osg::StateAttribute::OFF);
	//v->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	//v->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	//设置顶点数据
	geom->setVertexArray(v.get());
	int test = v->size();

	//创建纹理坐标
	//osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();
	//vt->push_back(osg::Vec2(0.0f, 0.0f));
	//vt->push_back(osg::Vec2(1.0f, 0.0f));
	//vt->push_back(osg::Vec2(1.0f, 1.0f));
	//vt->push_back(osg::Vec2(0.0f, 1.0f));
	////设置纹理坐标
	//geom->setTexCoordArray(0, vt.get());

	//创建颜色数组
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	/*vc->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	vc->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));*/
	//设置颜色数组
	geom->setColorArray(vc.get());
	//设置颜色绑定方式为单个顶点
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//创建法线数组
	//osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	//nc->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	////设置法线数组
	//geom->setNormalArray(nc.get());
	////设置法线绑定方式为全部顶点
	//geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	//添加图元，绘图基元为四边形
	//geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, 4));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, v->size()));

	//将图元添加至叶子节点
	geode->addDrawable(geom.get());

	//geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	//自动生成顶点法线(必须在addDrawable后)
	osgUtil::SmoothingVisitor::smooth(*(geom.get()));

	return geode.get();
}
osg::ref_ptr<osg::Node> OSGWidget::createCylinder() {
	//构造测试圆柱
	osg::ref_ptr<osg::Cylinder> cylinder = new osg::Cylinder(osg::Vec3(0.f, 0.f, 0.f), 0.25f, 0.5f);
	osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(cylinder);
	QByteArray barr = QString("TMP_zidingyi1").toLocal8Bit();
	char* bdata = barr.data();
	sd->setName(barr);
	sd->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0));
	//叶子节点
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(sd);
	barr = QString("TMP_圆柱").toLocal8Bit();
	bdata = barr.data();
	geode->setName(bdata);
	//osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();
	//osg::ref_ptr<osg::Material> material = new osg::Material;
	//material->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
	//stateSet->setAttributeAndModes(material, osg::StateAttribute::ON);
	return geode;
}
osg::ref_ptr<osg::Node> OSGWidget::createOSGGlider() {
	osg::ref_ptr<osg::Node> node = osgDB::readRefNodeFile("glider.osg");
	QByteArray barr = QString("TMP_飞机").toLocal8Bit();
	char* bdata = barr.data();
	node->setName(bdata);
	return node.get();
}
osg::ref_ptr<osg::Node> OSGWidget::createCloud() {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	//std::string name = geode->getName();
	QByteArray barr = QString("CloudPoints").toLocal8Bit();
	char* bdata = barr.data();
	geode->setName(barr);

	osg::StateSet* set = geode->getOrCreateStateSet();
	osg::PointSprite *sprite = new osg::PointSprite();
	set->setTextureAttributeAndModes(0, sprite, osg::StateAttribute::ON);

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	geom->setName("TMP_cloudpointsgeometry");
	//osg::ref_ptr<osg::DrawPixels> geom = new osg::DrawPixels;
	//创建顶点数组，注意顺序逆时针
	osg::ref_ptr<osg::Vec3Array> v = ReadModelFile("model.txt");
	//osg::ref_ptr<osg::Vec3dArray> v = ReadModelFile("model.txt");
	//设置顶点数据
	geom->setVertexArray(v.get());
	int test = v->size();

	//创建颜色数组
	//osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	////开始颜色
	//osg::Vec4 bcolor(1.0f, 0.0f, 0.0f, 1.0f);
	////结束颜色
	//osg::Vec4 ecolor(0.0f, 1.0f, 0.0f, 1.0f);
	//osg::Vec4 diffcolor = (ecolor - bcolor)*((double)1 / (maxY - minY));

	//for (auto p = v->begin(); p != v->end(); ++p) {
	//	float x = p->x();
	//	float y = p->y();
	//	float z = p->z();
	//	osg::Vec4 c = bcolor + diffcolor * y;
	//	vc->push_back(c);
	//}
	////设置颜色数组
	//geom->setColorArray(vc.get());
	////设置颜色绑定方式为单个顶点
	//geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//创建法线数组
	//osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	//nc->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	////设置法线数组
	//geom->setNormalArray(nc.get());
	////设置法线绑定方式为全部顶点
	//geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, v->size()));

	//将图元添加至叶子节点
	geode->addDrawable(geom.get());

	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	//自动生成顶点法线(必须在addDrawable后)
	osgUtil::SmoothingVisitor::smooth(*(geom.get()));

	return geode.get();
}
//osg::ref_ptr<osg::Node>  QtOSGWidget::createCloud() {
//	//画点云
//	osg::ref_ptr<osg::Vec3Array> coords = ReadModelFile("model.txt");
//	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
//
//	geometry->setVertexArray(coords);
//	int size1 = coords->size();
//	int size2 = coords->referenceCount();
//
//	//颜色
//	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
//
//	//开始颜色
//	osg::Vec4 bcolor(1.0f, 0.0f, 0.0f, 1.0f);
//	//结束颜色
//	osg::Vec4 ecolor(0.0f, 1.0f, 0.0f, 1.0f);
//	osg::Vec4 diffcolor = (ecolor - bcolor)*((double)1 / (maxY - minY));
//
//	for (auto p = coords->begin(); p != coords->end(); ++p) {
//		float x = p->x();
//		float y = p->y();
//		float z = p->z();
//		osg::Vec4 c = bcolor + diffcolor * ((y - minY) / (maxY - minY));
//		vc->push_back(c);
//	}
//	/*vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
//	vc->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
//	vc->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
//	vc->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));*/
//	//设置颜色数组
//	geometry->setColorArray(vc.get());
//	//设置颜色绑定方式为单个顶点
//	geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
//
//	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
//	normals->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
//	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, coords->size()));
//
//	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//	geode->addDrawable(geometry);
//	//root->addChild(geode.get());
//	//geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
//	return geode.get();
//}
osg::ref_ptr<osg::Node> OSGWidget::createShape() {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	QByteArray barr = QString("TMP_预定义几何体").toLocal8Bit();
	char* bdata = barr.data();
	geode->setName(bdata);
	float radius = 0.8f;
	float height = 1.0f;
	//精细程度
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints;
	hints->setDetailRatio(0.5f);
	//球体
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0, 0, 0), radius), hints));
	//正方形
	geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(2.0f, 0.0, 0.0), 2 * radius), hints));
	//圆锥
	geode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(4.0f, 0.0f, 0.0), radius, height), hints));
	//圆柱
	geode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(6.0f, 0.0f, 0.0f), radius, height), hints));
	//太空舱
	geode->addDrawable(new osg::ShapeDrawable(new osg::Capsule(osg::Vec3(8.0f, 0.0f, 0.0f), radius, height), hints));
	return geode.get();
}
osg::Node* OSGWidget::getChildNode(std::string name) {
	osg::ref_ptr<osg::Node> rNode = _mViewer->getSceneData();
	if (rNode == nullptr) {
		return nullptr;
	}
	if (rNode->getName() == name) {
		return rNode;
	}
	osg::ref_ptr<osg::Group> root = dynamic_cast<osg::Group*>(rNode.get());
	if (!root.valid()) {
		return nullptr;
	}
	int childcount = root->getNumChildren();
	for (int i = 0; i < childcount; ++i) {
		osg::ref_ptr<osg::Node> node = root->getChild(i);
		if (node->getName() == name) {
			return node;
		}
	}
	return nullptr;
}
void OSGWidget::ChangedCloudColor(osg::Geode* geode, osg::Vec3 axis, osg::Vec4 begColor, osg::Vec4 endColor) {
	//double diffFactor = 0.0;
	/*if (axis == osg::X_AXIS) {
	diffFactor = ;
	}
	else if (axis == osg::Y_AXIS) {
	diffFactor = ;
	}
	else if (axis == osg::Z_AXIS) {
	diffFactor = ;
	}*/
	axis.normalize();
	osg::Vec3 diffFactor = osg::componentMultiply(osg::Vec3(1 / (maxX - minX), 1 / (maxY - minY), 1 / (maxZ - minZ)), axis);

	////int geomNum = cloudGeode->getNumDrawables();
	osg::ref_ptr<osg::Geometry> cloudGeom = dynamic_cast<osg::Geometry*>(geode->getDrawable(0));
	osg::ref_ptr<osg::Vec3Array> v = dynamic_cast<osg::Vec3Array*>(cloudGeom->getVertexArray());
	//创建颜色数组
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	////开始颜色
	//osg::Vec4 bcolor(1.0f, 0.0f, 0.0f, 1.0f);
	////结束颜色
	//osg::Vec4 ecolor(0.0f, 1.0f, 0.0f, 1.0f);
	osg::Vec4 diffcolor = (endColor - begColor);
	for (auto p = v->begin(); p != v->end(); ++p) {
		/*float x = p->x();
		float y = p->y();
		float z = p->z();*/
		osg::Vec4 c = begColor + diffcolor * (((*p) - osg::Vec3(minX, minY, minZ)) * diffFactor);
		float cx, cy, cz;
		if (c.x() < 0) {
			cx = 0.0;
		}
		else if (c.x() > 1) {
			cx = 1.0;
		}
		else {
			cx = c.x();
		}
		if (c.y() < 0) {
			cy = 0.0;
		}
		else if (c.y() > 1) {
			cy = 1.0;
		}
		else {
			cy = c.y();
		}
		if (c.z() < 0) {
			cz = 0.0;
		}
		else if (c.z() > 1) {
			cz = 1.0;
		}
		else {
			cz = c.z();
		}
		vc->push_back(osg::Vec4(cx, cy, cz, 1.0f));
	}
	//设置颜色数组
	cloudGeom->setColorArray(vc.get());
	//设置颜色绑定方式为单个顶点
	cloudGeom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	this->update();
}
//绘制坐标轴
osg::ref_ptr<osg::Node> OSGWidget::createCoordinate() {
	//创建保存几何信息的对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();	
	//创建四个顶点
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1000.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(0.0f, 1000.0f, 0.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 1000.0f));
	geom->setVertexArray(v.get());

	//为每个顶点指定一种颜色
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();
	c->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); //坐标原点为白色
	c->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)); //x red
	c->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); //坐标原点为白色
	c->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f)); //y green
	c->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); //坐标原点为白色
	c->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f)); //z blue
													 //如果没指定颜色则会变为黑色
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//三个轴
	//geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4)); //XZ
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2)); //X
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 2, 2)); //Y
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 4, 2)); //Z

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING,
		osg::StateAttribute::OFF);
	geode->addDrawable(geom.get());
	QByteArray barr = QString("TMP_CustomCoordinate").toLocal8Bit();
	char* bdata = barr.data();
	geode->setName(bdata);

	/*osg::ref_ptr<osg::Group> newroot = new osg::Group();
	newroot->addChild(geode.get());*/

	return geode;
}

//创建HUD
osg::ref_ptr<osg::Node> OSGWidget::createHUD(osgViewer::Viewer* viewer) {
	int padding = 5;
	int w_box = 120;
	int h_box = 80;
	osg::Vec3 w_pos(w_box,0.0f,0.0f);
	osg::Vec3 h_pos(0.0f, h_box, 0.0f);
	//Box位置偏移
	osg::Vec3 z_boxoffset(0.0f, 0.0f, -0.1f);
	//Box位置
	osg::Vec3 p_box(100.0, 100.0, 0);
	//Box绝对位置（左下角为0点）
	osg::Vec3 box_relpos[] = { z_boxoffset ,z_boxoffset + w_pos ,z_boxoffset + w_pos + h_pos ,z_boxoffset + h_pos };

	//x，y，z小方块绘制
	int cub_width = 15;
	osg::Vec3 cub_relpos[] = { osg::Vec3(0.0, 0.0, 0.0) ,osg::Vec3(cub_width, 0.0, 0.0) ,osg::Vec3(cub_width, cub_width, 0.0) ,osg::Vec3(0.0, cub_width, 0.0) };
	
	//字体位置
	osg::Vec3 f1_pos = p_box + h_pos - osg::Vec3(-1.0f, 1.0f, 0.0f)*padding;


	//创建HUD相机
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setViewMatrix(osg::Matrix::identity());
	camera->setRenderOrder(osg::Camera::POST_RENDER);
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);
	camera->setAllowEventFocus(false);
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	std::cout << "screen 1" << this->width() << "," << this->height() << std::endl;
	/*camera->setProjectionMatrixAsOrtho2D(0, this->width(), 0, this->height());
	camera->setViewport(0, 0, this->width(), this->height());*/
	camera->setProjectionMatrixAsOrtho2D(0, 1024, 0, 768);
	camera->setViewport(0, 0, 1024, 768);
	camera->setNodeMask(1);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->setNodeMask(1);
	//设置状态关闭灯光
	osg::StateSet* stateset = geode->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);

	osg::ref_ptr<osg::Geometry> gm = new osg::Geometry;
	gm->setName("TMP_MyBox");
	gm->setNodeMask(1);
	geode->addDrawable(gm);

	//压入顶点
	osg::Vec3Array *vertex = new osg::Vec3Array;
	for (int i = 0; i < sizeof(box_relpos) / sizeof(box_relpos[0]); ++i) {
		vertex->push_back(box_relpos[i]+ p_box);
	}
	gm->setVertexArray(vertex);

	//创建颜色数组
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	vc->push_back(osg::Vec4(0.75f, 0.81f, 0.84f, 0.8f));
	//设置颜色数组
	gm->setColorArray(vc.get());
	//设置颜色绑定方式为单个顶点
	gm->setColorBinding(osg::Geometry::BIND_OVERALL);

	//法线
	osg::Vec3Array *norm = new osg::Vec3Array;
	norm->push_back(osg::Vec3(0.0, 0.0, 1.0));
	gm->setNormalArray(norm);
	gm->setNormalBinding(osg::Geometry::BIND_OVERALL);
	gm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertex->size()));

	osg::ref_ptr<osg::Geometry> gm2 = new osg::Geometry;
	geode->addDrawable(gm2);

	//世界坐标转屏幕坐标
	osg::Camera* _tCamera = viewer->getCamera();
	osg::Matrix VPW = _tCamera->getViewMatrix() *
		_tCamera->getProjectionMatrix() *
		_tCamera->getViewport()->computeWindowMatrix();
	osg::Vec3 window = osg::Vec3(-202.414f, 961.0f, 70.0564f) * VPW;
	std::cout <<"1.("<< window.x()<<"," << window.y() << "," << window.z() << ")" << std::endl;

	//压入顶点
	osg::Vec3Array *vertex2 = new osg::Vec3Array;
	vertex2->push_back(box_relpos[0]+ p_box);
	vertex2->push_back(box_relpos[0]+ p_box+ osg::X_AXIS*10);
	vertex2->push_back(osg::Vec3(379.869f, 385.842f, 1.00056f));//测试顶点
	gm2->setVertexArray(vertex2);

	//创建颜色数组
	osg::ref_ptr<osg::Vec4Array> vc2 = new osg::Vec4Array();
	vc2->push_back(osg::Vec4(0.75f, 0.81f, 0.84f, 0.8f));
	//设置颜色数组
	gm2->setColorArray(vc2.get());
	//设置颜色绑定方式为单个顶点
	gm2->setColorBinding(osg::Geometry::BIND_OVERALL);

	gm2->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, vertex2->size()));
	
	//设置字体
	osg::ref_ptr<osgText::Text> text = new osgText::Text;
	text->setFont("msyh.ttc");	
	text->setText(L"Point #253504");//动态传入ID号
	text->setLineSpacing(0.25f);
	text->setCharacterSize(10);
	text->setColor(osg::Vec4(0.0,0.0,0.0,1.0));
	int chheight = text->getCharacterHeight();
	//int chheight2 = text->getFontHeight();
	//osg::BoundingBox f1_boundbox = text->getBoundingBox();
	//int f1_height = f1_boundbox.yMax() - f1_boundbox.yMin();
	osg::Vec3 f1_pos2 = osg::Vec3(f1_pos.x(), f1_pos.y() - chheight, f1_pos.z());
	text->setPosition(f1_pos2);

	//绘制方块1
	//osg::Vec3 cub_pos1 = f1_pos2 - osg::Vec3(0.0f, 1.0f, 0.0f)*text->getFontHeight() - osg::Y_AXIS*padding;
	osg::Vec3 cub_pos1 = f1_pos2- osg::Y_AXIS* chheight*2 - osg::Y_AXIS*padding;
	osg::ref_ptr<osg::Geometry> gm3 = new osg::Geometry;
	geode->addDrawable(gm3);

	//压入顶点
	osg::Vec3Array *vertex3 = new osg::Vec3Array;
	for (int i = 0; i < sizeof(cub_relpos) / sizeof(cub_relpos[0]); ++i) {
		vertex3->push_back(cub_relpos[i] + cub_pos1);
	}
	gm3->setVertexArray(vertex3);

	//创建颜色数组
	osg::ref_ptr<osg::Vec4Array> vc3 = new osg::Vec4Array();
	vc3->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//设置颜色数组
	gm3->setColorArray(vc3.get());
	//设置颜色绑定方式为单个顶点
	gm3->setColorBinding(osg::Geometry::BIND_OVERALL);
	gm3->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertex3->size()));

	//绘制方块2
	osg::Vec3 cub_pos2 = cub_pos1 - osg::Y_AXIS*cub_width;
	osg::ref_ptr<osg::Geometry> gm4 = new osg::Geometry;
	geode->addDrawable(gm4);

	//压入顶点
	osg::Vec3Array *vertex4 = new osg::Vec3Array;
	for (int i = 0; i < sizeof(cub_relpos) / sizeof(cub_relpos[0]); ++i) {
		vertex4->push_back(cub_relpos[i] + cub_pos2);
	}
	gm4->setVertexArray(vertex4);

	//创建颜色数组
	osg::ref_ptr<osg::Vec4Array> vc4 = new osg::Vec4Array();
	vc4->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	//设置颜色数组
	gm4->setColorArray(vc4.get());
	//设置颜色绑定方式为单个顶点
	gm4->setColorBinding(osg::Geometry::BIND_OVERALL);

	gm4->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertex4->size()));
	//绘制方块3
	osg::Vec3 cub_pos3 = cub_pos2 - osg::Y_AXIS*cub_width;
	osg::ref_ptr<osg::Geometry> gm5 = new osg::Geometry;
	geode->addDrawable(gm5);

	//压入顶点
	osg::Vec3Array *vertex5 = new osg::Vec3Array;
	for (int i = 0; i < sizeof(cub_relpos) / sizeof(cub_relpos[0]); ++i) {
		vertex5->push_back(cub_relpos[i] + cub_pos3);
	}
	gm5->setVertexArray(vertex5);

	//创建颜色数组
	osg::ref_ptr<osg::Vec4Array> vc5 = new osg::Vec4Array();
	vc5->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	//设置颜色数组
	gm5->setColorArray(vc5.get());
	//设置颜色绑定方式为单个顶点
	gm5->setColorBinding(osg::Geometry::BIND_OVERALL);

	gm5->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertex5->size()));

	//字体位置
	//osg::Vec3 f1_pos = p_box + h_pos - osg::Vec3(-1.0f, 1.0f, 0.0f)*padding;

	geode->addDrawable(text);
	camera->addChild(geode);
	_mViewer->getSceneData()->asGroup()->addChild(camera);
	camera->setName("TMP_ULDCamera");
	//this->update();
	return camera;
}
void OSGWidget::onTest() {
	createHUD(_mViewer);
}