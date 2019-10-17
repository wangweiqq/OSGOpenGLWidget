#pragma once
#include "BuildBoard.h"
class PointBuildBoard :
	public BuildBoard
{
public:
	PointBuildBoard(QString id,unsigned int posIndex, osg::Vec3 selPointPos, osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Camera> camera);
	virtual ~PointBuildBoard();	
	/**
	创建Box面板
	*/
	virtual void CreateBox(osg::Vec4 boxColor = osg::Vec4(0.75f, 0.81f, 0.84f, 0.8f), float width = 120, float height = 80);
	/**
	更新Box的位置
	*/
	virtual void UpdateBoxPos();
	/**
	设置标题
	*/
	void SetTitle(QString str);
	void SetStrX(QString str);
	void SetStrY(QString str);
	void SetStrZ(QString str);
protected:
	//更新选择点云点位置
	void ResetSelPos(unsigned int index,osg::Vec3 selPointPos);
public:
	//选中点的索引号
	unsigned int selPosIndex;
	//被选中的点
	osg::ref_ptr<osg::Geode> mSelPoint;
	//文字标签
	osg::ref_ptr<osgText::Text> mTitle;
	osg::ref_ptr<osgText::Text> mTxtX;
	osg::ref_ptr<osgText::Text> mTxtY;
	osg::ref_ptr<osgText::Text> mTxtZ;
	//X，Y，Z图标
	osg::ref_ptr<osgText::Text> _XLabel;
	osg::ref_ptr<osgText::Text> _YLabel;
	osg::ref_ptr<osgText::Text> _ZLabel;
	osg::ref_ptr<osg::Geometry> mXIcon;
	osg::ref_ptr<osg::Geometry> mYIcon;
	osg::ref_ptr<osg::Geometry> mZIcon;
private:
	int _padding = 5;
	//x，y，z小方块绘制
	int _cubwidth = 15;
	//小方块相对位置
	std::vector<osg::Vec3> _cubrelpos;
};

