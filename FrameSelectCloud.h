#pragma once
/**
点云框选
*/
#include <osg/Referenced>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osg/Point>
#include <osgUtil/SmoothingVisitor>
#include <map>
#include <QString>

class FrameSelectCloud :
	public osg::Referenced
{
public:
	FrameSelectCloud(osg::ref_ptr<osgViewer::Viewer> viewer);
	virtual ~FrameSelectCloud();
	void SetFirstPos(osg::Vec2 pos);
	/**绘制选择框*/
	void DrawSelRect(osg::Vec2 pos);
	//bool FramePick(const osgGA::GUIEventAdapter& ea);
	bool DragFrame(osg::Vec2 curPos);
	//清除所有选择的点
	void clear();
	void Redraw();
private:
	
	//被选中的页节点
	osg::ref_ptr<osg::Geode> mGeode;
	osg::ref_ptr<osgViewer::Viewer> mViewer;
	//记录鼠标点击第一点
	osg::Vec2 mSPos1;
public:
	//是否允许拖动
	bool IsAllowDrag = false;
	////选中的顶点编号
	std::map<unsigned int, osg::Vec3> list;
	QString mSelNodeName;
	//创建HUD相机
	osg::ref_ptr<osg::Camera> mHUDCamera;
};

