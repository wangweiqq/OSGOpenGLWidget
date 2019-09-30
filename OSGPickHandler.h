#pragma once
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/Viewer>
#include <osg/Point>
#include <osg/Multisample>
#include <osgUtil/SmoothingVisitor>
#include "PointIntersector.h"

#include <QString>
class OSGPickHandler :
	public osgGA::GUIEventHandler
{
public:
	OSGPickHandler(osgViewer::Viewer* viewer);
	virtual ~OSGPickHandler();
	/**重置*/
	void Reset();
	/**画一个点*/
	void OnePoint();
	/**画二个点*/
	void TwoMeause();
	void DrawTips(osg::Vec3 pos);
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
	/*std::string mOnePointName;
	std::string mTwoPointName;
	osg::Vec3 mOnePoint;
	osg::Vec3 mTwoPoint;*/
};

