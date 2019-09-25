#include "QtCameraManipulator.h"



QtCameraManipulator::QtCameraManipulator():osgGA::TrackballManipulator()
{
	//_position = osg::Vec3(0, 0, 50);
	////一般让相机绕x轴旋转90度，否则相机会从上空看模型（一般，一般会这样，看你模型怎么方了)  
	//_rotate = osg::Vec3(osg::PI_2, 0, 0);
	//_speed = 2.0;
	//_angle = 2.5;
}


QtCameraManipulator::~QtCameraManipulator()
{
}
/**
参照StandardManipulator::performMovement()算法
*/
bool QtCameraManipulator::performMovement() {
	// return if less then two events have been added
	if (_ga_t0.get() == NULL || _ga_t1.get() == NULL)
		return false;

	// get delta time
	double eventTimeDelta = _ga_t0->getTime() - _ga_t1->getTime();
	if (eventTimeDelta < 0.)
	{
		OSG_WARN << "Manipulator warning: eventTimeDelta = " << eventTimeDelta << std::endl;
		eventTimeDelta = 0.;
	}

	// get deltaX and deltaY
	float dx = _ga_t0->getXnormalized() - _ga_t1->getXnormalized();
	float dy = _ga_t0->getYnormalized() - _ga_t1->getYnormalized();

	// return if there is no movement.
	if (dx == 0. && dy == 0.)
		return false;


	// call appropriate methods
	unsigned int buttonMask = _ga_t1->getButtonMask();
	unsigned int modKeyMask = _ga_t1->getModKeyMask();
	if (buttonMask == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
	{
		return performMovementLeftMouseButton(eventTimeDelta, dx, dy);
	}
	else if (buttonMask == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
	{
		return performMovementMiddleMouseButton(eventTimeDelta, dx, dy);
	}
	return false;
}
void QtCameraManipulator::computeHomePosition(const osg::Camera *camera, bool useBoundingBox) {
	if (getNode())
	{
		osg::BoundingSphere boundingSphere;

		OSG_INFO << " CameraManipulator::computeHomePosition(" << camera << ", " << useBoundingBox << ")" << std::endl;

		if (useBoundingBox)
		{
			// compute bounding box
			// (bounding box computes model center more precisely than bounding sphere)
			osg::ComputeBoundsVisitor cbVisitor;
			getNode()->accept(cbVisitor);
			osg::BoundingBox &bb = cbVisitor.getBoundingBox();

			if (bb.valid()) boundingSphere.expandBy(bb);
			else boundingSphere = getNode()->getBound();
		}
		else
		{
			// compute bounding sphere
			boundingSphere = getNode()->getBound();
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

		// set home position
		setHomePosition(boundingSphere.center() + osg::Vec3d(0.0, 0.0, dist),
			boundingSphere.center(),
			osg::Vec3d(0.0f, 0.0f, 1.0f),
			_autoComputeHomePosition);

			/*setHomePosition(boundingSphere.center() + osg::Vec3d(0.0, -dist, 0.0),
				boundingSphere.center(),
				osg::Vec3d(0.0f, 0.0f, 1.0f),
				_autoComputeHomePosition);*/
	}
}
//bool QtCameraManipulator::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us) {
//	/*switch (ea.getEventType())
//	{
//
//	case osgGA::GUIEventAdapter::FRAME:
//		return handleFrame(ea, us);
//
//	case osgGA::GUIEventAdapter::RESIZE:
//		return handleResize(ea, us);
//
//	default:
//		break;
//	}*/
//
//	/*if (ea.getHandled())
//		return false;*/
//	switch (ea.getEventType())
//	{
//	//case osgGA::GUIEventAdapter::SCROLL:
//	//{
//	//	if (_flags & PROCESS_MOUSE_WHEEL)
//	//		return handleMouseWheel(ea, us);
//	//	/*osgViewer::Viewer * viewer = dynamic_cast<osgViewer::Viewer *>(&us);
//	//	osg::Camera* camera = viewer->getCamera();
//	//	osg::Matrix MVPW = camera->getViewMatrix()* camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
//	//	osg::Matrix inverseMVPW = osg::Matrix::inverse(MVPW);
//	//	osg::Vec3 mouseWorld = osg::Vec3(ea.getX(), ea.getY(), 0)*inverseMVPW;
//	//	osg::Vec3 direction = mouseWorld - _position;
//	//	direction.normalize();
//	//	if (ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_UP) {
//	//		_position += direction * 20;
//	//	}
//	//	else if (ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_DOWN) {
//	//		_position -= direction * 20;
//	//	}*/
//	//}
//	//	break;
//	case osgGA::GUIEventAdapter::PUSH :
//	{
//		//return handleMousePush(ea, us);
//		/*switch (ea.getButton())
//		{
//		case osgGA::GUIEventAdapter::MouseButtonMask::LEFT_MOUSE_BUTTON:
//			std::cout << "LEFT_MOUSE_BUTTON" << std::endl;
//			break;
//		case osgGA::GUIEventAdapter::MouseButtonMask::MIDDLE_MOUSE_BUTTON:
//			std::cout << "MIDDLE_MOUSE_BUTTON" << std::endl;
//			break;
//		case osgGA::GUIEventAdapter::MouseButtonMask::RIGHT_MOUSE_BUTTON:
//			std::cout << "RIGHT_MOUSE_BUTTON" << std::endl;
//			break;
//		default:
//			break;
//		}*/
//		if (osgGA::GUIEventAdapter::MouseButtonMask::RIGHT_MOUSE_BUTTON == ea.getButton()) {
//			IsRightButton = true;
//			return true;
//		}
//	}
//		break;
//	case osgGA::GUIEventAdapter::RELEASE :
//	{
//		if (osgGA::GUIEventAdapter::MouseButtonMask::RIGHT_MOUSE_BUTTON == ea.getButton()) {
//			IsRightButton = false;
//			return true;
//		}
//	}
//		break;
//	case osgGA::GUIEventAdapter::MOVE:
//	{
//		if (osgGA::GUIEventAdapter::MouseButtonMask::RIGHT_MOUSE_BUTTON == ea.getButton()) {
//			return true;
//		}
//	}
//		break;
//	default:
//		break;
//	}
//	
//	return osgGA::TrackballManipulator::handle(ea,us);
//}