#pragma once
#include <osgGA/CameraManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <osgViewer/Viewer>
#include <osg/Camera>
#include <osg/ComputeBoundsVisitor>
#include <iostream>
/**
自定义OSG相机漫游类
*/
class OSGCameraManipulator :
	public osgGA::TrackballManipulator
{
public:
	OSGCameraManipulator();
	virtual ~OSGCameraManipulator();
//	///**
//	//这个函数在从一个摄像机切换到另一个摄像机时调用，用来把上一个摄像机的视图矩阵传过来，
//	//这样就可依此设定自己的初始位置了。
//	//*/
//	virtual void setByMatrix(const osg::Matrixd& matrix) {
//
//	}
//
//	/**
//	这个方法当在外部直接调用Viewer的setViewByMatrix方法时，把设置的矩阵传过来，让
//	摄像机记住新更改的位置
//	*/
//	virtual void setByInverseMatrix(const osg::Matrixd& matrix)
//	{
//	}
//
//	/** 
//		SetByMatrix方法需要的矩阵就是用这个方法得到的，用来向下一个摄像机传递矩阵。
//	*/
//	virtual osg::Matrixd getMatrix() const {
//		osg::Matrixd mat;
//		mat.makeRotate(_rotate.x(), osg::X_AXIS, _rotate.y(), osg::Y_AXIS, _rotate.z(), osg::Z_AXIS);
//		std::cout << "getMatrix" << std::endl;
//		return mat* osg::Matrixd::translate(_position);
//	}
//
//	/** 
//	视图矩阵（观察矩阵）是变换矩阵的逆矩阵)   这个是最重要的方法，这个方法每帧会被调用，它返回当前的视图矩阵。
//在这个方法里进行时间的处理，改变自己的状态，进而在 getInverseMatrix 被调用时，改变
//场景内摄像机的位置姿态。这个函数在 void Viewer::updateTraversal()中被调用
// _camera->setViewMatrix(_cameraManipulator->getInverseMatrix());
//	*/
//	virtual osg::Matrixd getInverseMatrix() const {
//		osg::Matrixd mat;
//		mat.makeRotate(_rotate.x(), osg::X_AXIS, _rotate.y(), osg::Y_AXIS, _rotate.z(), osg::Z_AXIS);
//		return osg::Matrixd::inverse(mat* osg::Matrixd::translate(_position));
//	}
	/**
	在这个方法里，有两个参数，第一个是GUI事件的供给者，第二个参数用来handle方法对GUI
进行反馈，它可以让GUIEventHandler根据输入事件让GUI进行一些动作。
如果要进行事件处理，可以从GUIEventHandler继承出自己的类，然后覆盖handle方法，在里
面进行事件处理。osgProducer::Viewer类维护一个GUIEventHandler队列，事件在这个队列里依次传
递，handle的返回值决定这个事件是否继续让后面的GUIEventHandler处理，如果返回true，则停止
处理，如果返回false，后面的GUIEventHandler还有机会继续对这个事件进行响应。
	*/
	//virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);
	virtual bool performMovement();
	virtual void computeHomePosition(const osg::Camera *camera = NULL, bool useBoundingBox = false);
private:
	//鼠标右键被按下
	//bool IsRightButton = false;
	////视点位置
	//osg::Vec3f _position;
	////视点方向
	//osg::Vec3f _rotate;
	//float _speed;
	//float _angle;
};

