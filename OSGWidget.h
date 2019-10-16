#pragma once
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QEvent>

#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/DrawPixels>
#include <osg/Point>
#include <osg/StateAttribute>
#include <osg/PointSprite>
#include <osg/Camera>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/StateSetManipulator>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/ViewerEventHandlers>
#include <osgUtil/Optimizer>
#include <osgUtil/SmoothingVisitor>
#include <osgText/Text>
#include <osgWidget/Box>

#include <iostream>

#include "OSGCameraManipulator.h"
#include "OSGPickHandler.h"

class OSGWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	/**
		点云测量
	*/
	enum MeauseCloud
	{
		NONE,//无
		RESET,//重置
		ONEPOINT,//测量一点
		TWOMEAUSE//测量两点
	};
	OSGWidget(QWidget *parent = nullptr);
	~OSGWidget();
	/**
		查找场景子节点yan
	*/
	osg::Node* getChildNode(std::string name);
	/**
		//更改点叶子节点颜色，geode：叶子节点，axis：延那个轴方向更改颜色，begColor:开始颜色，endColor：结束颜色
	*/
	void ChangedCloudColor(osg::Geode* geode,osg::Vec3 axis,osg::Vec4 begColor, osg::Vec4 endColor);
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
		计算节点Node位置
	*/
	void computeNodePosition(osg::Node* node, const osg::Camera *camera, bool useBoundingBox);
	/**
		 读取3D点云
	*/
	//osg::ref_ptr<osg::Vec3dArray> ReadModelFile(std::string filename);
	osg::ref_ptr<osg::Vec3Array> ReadModelFile(std::string filename);
	//测试：
	/**
		创建圆柱
	*/
	osg::ref_ptr<osg::Node> createCylinder();
	/**
	创建OSG滑翔机模型
	*/
	osg::ref_ptr<osg::Node> createOSGGlider();
	//创建四边形
	osg::ref_ptr<osg::Node> createQuad();
	//创建测试点云
	osg::ref_ptr<osg::Node> createCloud();
	//创建预定义几何体
	osg::ref_ptr<osg::Node> createShape();
	//绘制坐标轴
	osg::ref_ptr<osg::Node> createCoordinate();
	//创建HUD
	osg::ref_ptr<osg::Node> createHUD(osgViewer::Viewer*);
public slots:
	void onCylinder();
	void onQuad();
	void onCloud();
	void onShape();
	void onGlider();
	void onClear();
	void onRecHeightRamp(int axis, QColor beginColor, QColor endColor);

	void onSelCloudPoint(OSGWidget::MeauseCloud meause);

	void onTest();
private:
	osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _mGraphicsWindow;
	osg::ref_ptr<osgViewer::Viewer> _mViewer;

	osg::ref_ptr<OSGPickHandler> _mPickHandler = nullptr;
};
