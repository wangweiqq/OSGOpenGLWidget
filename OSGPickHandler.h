#pragma once
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/Viewer>
#include <osg/Point>
#include <osg/Multisample>
#include <osgUtil/SmoothingVisitor>
#include <osgText/Text>

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

#include "PointIntersector.h"
#include <vector>
#include <QString>
/**
	点信息板UI页面
*/
class PointBuildBoard:public osg::Referenced {
public :
	PointBuildBoard(std::string id, osg::Vec3 selPointPos, osg::ref_ptr<osgViewer::Viewer> viewer,osg::ref_ptr<osg::Camera> camera);
	~PointBuildBoard();
	/**
		创建Box面板
	*/
	void CreateBox( osg::Vec4 boxColor = osg::Vec4(0.75f, 0.81f, 0.84f, 0.8f),float width = 120,float height = 80);
	//更新选择点云点位置
	void ResetSelPos(osg::Vec3 selPointPos);
	/**
		更新Box的位置
	*/
	void UpdateBoxPos();
	/**
	创建Text标签
	*/
	osg::ref_ptr<osgText::Text> CreateText(std::string id, QString str, int fontSize = 10);
	//osg::ref_ptr<osg::Node> createHUD(osgViewer::Viewer* viewer);
	/**
	设置标题
	*/
	void SetTitle(QString str);
	void SetStrX(QString str);
	void SetStrY(QString str);
	void SetStrZ(QString str);
	osg::ref_ptr<osg::Geometry> CreateIcon(std::string id, osg::Vec4 color);
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
private:
	int _padding = 5;
	
	//x，y，z小方块绘制
	int _cubwidth = 15;
	std::vector<osg::Vec3> _cubrelpos;
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
	std::vector<osg::Vec3> _boxrelpos;
	//选中点云的位置（世界坐标）
	osg::Vec3 mSelPointPos;
	//Box的原点位置（创建由选中的点决定，之后用户拖动决定，屏幕坐标）
	osg::Vec3 mBoxPos;
	osg::ref_ptr<osgText::Text> _XLabel;
	osg::ref_ptr<osgText::Text> _YLabel;
	osg::ref_ptr<osgText::Text> _ZLabel;
	//移动面板是原点相对鼠标点击位置的偏移
	osg::Vec3 mMovePosOffset;
public:
	//编号
	std::string mId;
	//文字标签
	osg::ref_ptr<osgText::Text> mTitle;
	osg::ref_ptr<osgText::Text> mTxtX;
	osg::ref_ptr<osgText::Text> mTxtY;
	osg::ref_ptr<osgText::Text> mTxtZ;
	//X，Y，Z图标
	osg::ref_ptr<osg::Geometry> mXIcon;
	osg::ref_ptr<osg::Geometry> mYIcon;
	osg::ref_ptr<osg::Geometry> mZIcon;
	
	//是否允许移动该面板
	bool IsAllowMove = false;
};
class OSGPickHandler :
	public osgGA::GUIEventHandler
{
public:
	OSGPickHandler(osgViewer::Viewer* viewer);
	~OSGPickHandler();
	/**重置*/
	void Reset();
	/**画一个点*/
	void OnePoint();
	/**画二个点*/
	void TwoMeause();
	void DrawTips(unsigned int primitiveIndex,osg::Vec3 pos);
	/**
		更新PointBuildBoard界面
	*/
	void UpdateBoard();
	//osg::ref_ptr<osg::Node> createHUD(osgViewer::Viewer* viewer);
protected:
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
	virtual void pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea);
private:
	//创建一个选中点
	osg::ref_ptr<osg::Geode> createSelPoint(QString name, osg::Vec3& pos);
	
	//osg::Geode* DrawOnePoint(QString name,osg::Vec3& pos);
	osg::ref_ptr<osg::Group> mPickGroup;
	osg::ref_ptr<osgViewer::Viewer> mViewer;
	//允许画几个点
	int allowPointsNum = 1;
	osg::ref_ptr<osg::Geode> mOnePoint;
	osg::ref_ptr<osg::Geode> mTwoPoint;
	osg::ref_ptr<PointBuildBoard> mOneBoard;
	osg::ref_ptr<PointBuildBoard> mTwoBoard;
	//创建HUD相机
	osg::ref_ptr<osg::Camera> mHUDCamera;
	/*std::string mOnePointName;
	std::string mTwoPointName;
	osg::Vec3 mOnePoint;
	osg::Vec3 mTwoPoint;*/
};

