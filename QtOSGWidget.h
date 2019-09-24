#pragma once
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QEvent>

#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/StateSetManipulator>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/ViewerEventHandlers>
#include <osgUtil/Optimizer>

#include <iostream>

#include "QtCameraManipulator.h"

class QtOSGWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	QtOSGWidget(QWidget *parent = nullptr);
	~QtOSGWidget();
protected:
	void initializeGL()override;
	void paintGL()override;
	void resizeGL(int w, int h)override;
	//将osgGA::EventQueue事件与Qt鼠标事件相关联
	void mouseDoubleClickEvent(QMouseEvent *event)override;
	void mouseMoveEvent(QMouseEvent *event)override;
	void mousePressEvent(QMouseEvent *event)override;
	void mouseReleaseEvent(QMouseEvent *event)override;
	void wheelEvent(QWheelEvent *event)override;
	void keyPressEvent(QKeyEvent *event)override;
	void keyReleaseEvent(QKeyEvent *event)override;

	bool event(QEvent *event) override;
private:
	osgGA::EventQueue* getEventQueue()const;
	void setKeyboardModifiers(QInputEvent* event);
	/**
		 读取3D点云
	*/
	osg::ref_ptr<osg::Vec3Array> ReadModelFile(std::string filename);
	//测试：
	//创建四边形
	osg::ref_ptr<osg::Node> createQuad();
	//创建测试点云
	osg::ref_ptr<osg::Node> createCloud();
	//创建预定义几何体
	osg::ref_ptr<osg::Node> createShape();
private:
	osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _mGraphicsWindow;
	osg::ref_ptr<osgViewer::Viewer> _mViewer;
};
