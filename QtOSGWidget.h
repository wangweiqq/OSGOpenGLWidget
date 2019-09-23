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
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/GraphicsWindow>
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
private:
	osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _mGraphicsWindow;
	osg::ref_ptr<osgViewer::Viewer> _mViewer;
};
