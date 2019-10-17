#pragma once
#include "BuildBoard.h"
class MeasureBuildBoard :
	public BuildBoard
{
public:
	MeasureBuildBoard(QString id,unsigned int pos1Index ,osg::Vec3 pos1, unsigned int pos2Index, osg::Vec3 pos2, osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Camera> camera);
	virtual ~MeasureBuildBoard();

	/**
	创建Box面板
	*/
	virtual void CreateBox(osg::Vec4 boxColor = osg::Vec4(0.75f, 0.81f, 0.84f, 0.8f), float width = 240, float height = 80);
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
	void SetStrXY(QString str);
	void SetStrXZ(QString str);
	void SetStrZY(QString str);
protected:
	//更新选择点云点位置
	void ResetSelPos(unsigned int findex, osg::Vec3 fpos, unsigned int sindex, osg::Vec3 spos);
public:
	unsigned int mFirstPosIndex;
	osg::Vec3 mFirstVecPos;
	unsigned int mSecondPosIndex;
	osg::Vec3 mSecondVecPos;
	//第一个点
	osg::ref_ptr<osg::Geode> mFGPos;
	//第二个点
	osg::ref_ptr<osg::Geode> mSGPos;
	//两点间的线
	osg::ref_ptr<osg::Geode> mLine;

	//文字标签
	osg::ref_ptr<osgText::Text> mTitle;
	osg::ref_ptr<osgText::Text> mTxtX;
	osg::ref_ptr<osgText::Text> mTxtY;
	osg::ref_ptr<osgText::Text> mTxtZ;

	osg::ref_ptr<osgText::Text> mTxtXY;
	osg::ref_ptr<osgText::Text> mTxtXZ;
	osg::ref_ptr<osgText::Text> mTxtZY;

	//X，Y，Z图标
	osg::ref_ptr<osgText::Text> _DeltaXLabel;
	osg::ref_ptr<osgText::Text> _DeltaYLabel;
	osg::ref_ptr<osgText::Text> _DeltaZLabel;
	osg::ref_ptr<osg::Geometry> mDeltaXIcon;
	osg::ref_ptr<osg::Geometry> mDeltaYIcon;
	osg::ref_ptr<osg::Geometry> mDeltaZIcon;

	osg::ref_ptr<osgText::Text> _DeltaXYLabel;
	osg::ref_ptr<osgText::Text> _DeltaXZLabel;
	osg::ref_ptr<osgText::Text> _DeltaZYLabel;
	osg::ref_ptr<osg::Geometry> mDeltaXYIcon;
	osg::ref_ptr<osg::Geometry> mDeltaXZIcon;
	osg::ref_ptr<osg::Geometry> mDeltaZYIcon;
private:
	int _padding = 5;
	//x，y，z小方块绘制
	int _cubwidth = 30;
	int _cubHeight = 15;
	//小方块相对位置
	std::vector<osg::Vec3> _cubrelpos;
};

