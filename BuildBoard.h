#pragma once
#include <QString>
#include <osgViewer/Viewer>
#include <osg/StateAttribute>
#include <osgText/Text>
#include <osg/ShapeDrawable>
#include <osg/Camera>
#include <osg/Point>
#include <osg/LineWidth>
#include <osgUtil/SmoothingVisitor>
class BuildBoard :
	public osg::Referenced
{
public:
	//BuildBoard(QString id, osg::Vec3 selPointPos, osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Camera> camera);
	BuildBoard(QString id, osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Camera> camera);
	virtual ~BuildBoard();
	/**
		创建Box面板
	*/
	virtual void CreateBox( osg::Vec4 boxColor = osg::Vec4(0.75f, 0.81f, 0.84f, 0.8f),float width = 120,float height = 80);
	/**
	更新Box的位置
	*/
	virtual void UpdateBoxPos();	
	/**
	创建Text标签
	*/
	osg::ref_ptr<osgText::Text> CreateText(std::string id, QString str, int fontSize = 10, std::string fontfamily = "msyh.ttc");
	osg::ref_ptr<osg::Geometry> CreateIcon(std::string id, osg::Vec4 color);
	osg::ref_ptr<osg::Geode> createSelPoint(QString name, osg::Vec3& pos);
	osg::ref_ptr<osg::Geode> CreateLine(QString name, osg::Vec4 color, std::vector<osg::Vec3> list);
	/**
		判断是否被点击
	*/
	bool IsCheckClick(osg::Vec3 pos);
	osg::Vec3 GetBoxOrigin() {
		return mBoxPos;
	}
	/**
		更改Box面板位置
	*/
	void SetBoxPosition(osg::Vec3 pos) {
		mSelPointPos = pos;
	}
	/**
		记录移动时鼠标相对box原点的偏移
	*/
	void RecordMoveOffset(osg::Vec3 pos);
	/**
		移动面板位置
	*/
	void MoveBuildBoard(osg::Vec3 pos);
protected:	
	//更新选择点云点位置
	virtual void ResetSelPos(osg::Vec3 selPointPos);
protected:
	osg::ref_ptr<osgViewer::Viewer> _viewer;
	//创建HUD相机
	osg::ref_ptr<osg::Camera> _camera;
	osg::ref_ptr<osg::Geode> _geode;
	//绘制Box
	osg::ref_ptr<osg::Geometry> _boxGm;
	//绘制三角形指示标记
	osg::ref_ptr<osg::Geometry> _triangleGm;
	//Box的宽和高
	int _wbox = 120;
	int _hbox = 80;
	//box相对位置
	std::vector<osg::Vec3> _boxrelpos;
	
	//Box的原点位置（创建由选中的点决定，之后用户拖动决定，屏幕坐标）
	osg::Vec3 mBoxPos;
	//移动面板是原点相对鼠标点击位置的偏移
	osg::Vec3 mMovePosOffset;	
public:
	//编号
	std::string mId;	
	//是否允许移动该面板
	bool IsAllowMove = false;
	//选中点云的位置（世界坐标）
	osg::Vec3 mSelPointPos;
};

