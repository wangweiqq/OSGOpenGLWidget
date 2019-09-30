#pragma execution_character_set("utf-8")
#include "OSGPickHandler.h"
#include <QByteArray>
#include <QString>
#include <iostream>
#include <sstream>


OSGPickHandler::OSGPickHandler(osgViewer::Viewer* viewer):osgGA::GUIEventHandler()
{
	mViewer = viewer;
	mPickGroup = new osg::Group();
	mPickGroup->setName("PickGroup");
	mViewer->getSceneData()->asGroup()->addChild(mPickGroup);
	mOnePoint = nullptr;
	mTwoPoint = nullptr;
}


OSGPickHandler::~OSGPickHandler()
{
	mViewer->getSceneData()->asGroup()->removeChild(mPickGroup);
}
bool OSGPickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa){
	//osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	//if (!viewer)return false;
	if (!mViewer.valid()) {
		return false;
	}
	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::PUSH:
	{
		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) {
			pick(mViewer, ea);
		}
		else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) {

		}
		//QByteArray barr = QString("鼠标PUSH：").toLocal8Bit();
		//std::cout << barr.data() << std::endl;
	}
	break;
	}
	return false;
}
void OSGPickHandler::pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea){
	//osg::ref_ptr<PointIntersector> intersector = new PointIntersector(osgUtil::Intersector::WINDOW, osg::Vec3(ea.getX() - 0.1, ea.getY() - 0.1, 0), osg::Vec3(ea.getX() + 0.1, ea.getY() + 0.1, 0));
	std::cout << "mouse click = (" << ea.getX() << "," << ea.getY() << std::endl;
	osg::ref_ptr<PointIntersector> intersector = new PointIntersector(osgUtil::Intersector::WINDOW, ea.getX(), ea.getY());
	//intersector->setOffset(0.5f);
	osgUtil::IntersectionVisitor iv(intersector.get());
	view->getCamera()->accept(iv);
	
	if (intersector->containsIntersections())
	{
		std::vector<osg::Vec3> points;
		for (auto iter = intersector->getIntersections().begin(); iter != intersector->getIntersections().end(); iter++)
		{
			osg::Vec3 pos = iter->getWorldIntersectPoint();
			std::cout << (iter->nodePath).back()->getName() << " , " << (iter->nodePath).back()->className() << std::endl;
			std::cout << "vertex indices = (" << pos.x() << "," << pos.y() << "," << pos.z() << ")" << std::endl;
			//std::cout << iter->nodePath->back()->className() << std::endl;
			points.push_back(iter->getWorldIntersectPoint());
		}
		if (points.size() > 0) {
			DrawTips(points[0]);
			osg::Group* root = mViewer->getSceneData()->asGroup();
			int count = root->getNumChildren();
			for (int i = 0; i < count; ++i) {
				osg::Group* g = root->getChild(i)->asGroup();
				if (g) {
					std::cout << g->getName() << std::endl;
					if (g->getName() == "PickGroup") {
						for (int j = 0; j < g->getNumChildren(); ++j) {
							osg::Geode* geode = g->getChild(j)->asGeode();
							osg::Geometry* geometry = geode->getDrawable(0)->asGeometry();
							osg::Vec3Array* arr = dynamic_cast<osg::Vec3Array*> (geometry->getVertexArray());
							for (int z = 0; z < arr->size(); ++z) {
								std::cout << "Get Point = (" << arr->at(z).x() << "," << arr->at(z).y() << "," << arr->at(z).z() << ")" << std::endl;
							}
						}
					}
				}
			}
		}
		////osg::Vec3d worldpoint = CRealInteractionUtil::getNeartestPoint(intersector, osg::Vec2f(ea.getX(), ea.getY()), transformMatrix*vpw);
		//PointIntersector::Intersection result = *intersector->getIntersections().begin();
		///*for (auto iter = result.nodePath.begin(); iter != result.nodePath.end(); ++iter) {
		// std::cout << (*iter)->getName() << " , " << (*iter)->className() << std::endl;
		//}*/
		//std::cout << result.nodePath.back()->getName() << " , " << result.nodePath.back()->className() << std::endl;
		///*for (auto iter = result.nodePath.begin(); iter != result.nodePath.end(); ++iter) {
		// std::cout << (*iter)->getName() << " , " << (*iter)->className() << std::endl;
		//}*/
		///*PointIntersector::Intersection::IndexList& vil = result.indexList;
		//for (unsigned int i = 0; i < vil.size(); ++i)
		//{
		// std::cout << "        vertex indices [" << i << "] = " << vil[i] << std::endl;
		//}*/

	}
	//osgUtil::LineSegmentIntersector::Intersections intersections;

	//std::string gdlist = "";

	//if (view->computeIntersections(ea, intersections))
	//{
	//	for (osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
	//	hitr != intersections.end();
	//		++hitr)
	//	{
	//		std::ostringstream os;
	//		if (!hitr->nodePath.empty() && !(hitr->nodePath.back()->getName().empty()))
	//		{
	//			// the geodes are identified by name.
	//			os << "Object \"" << hitr->nodePath.back()->getName() << "\"" << std::endl;
	//		}
	//		else if (hitr->drawable.valid())
	//		{
	//			os << "Object \"" << hitr->drawable->className() << "\"" << std::endl;
	//		}
	//		//os << "        local coords vertex(" << hitr->getLocalIntersectPoint() << ")" << "  normal(" << hitr->getLocalIntersectNormal() << ")" << std::endl;
	//		//os << "        world coords vertex(" << hitr->getWorldIntersectPoint() << ")" << "  normal(" << hitr->getWorldIntersectNormal() << ")" << std::endl;
	//		const osgUtil::LineSegmentIntersector::Intersection::IndexList& vil = hitr->indexList;
	//		for (unsigned int i = 0; i < vil.size(); ++i)
	//		{
	//			os << "        vertex indices [" << i << "] = " << vil[i] << std::endl;
	//		}

	//		gdlist += os.str();
	//		std::cout << gdlist << std::endl;
	//		std::cout << "===============" << std::endl;
	//	}
	//}
}
/**重置*/
void OSGPickHandler::Reset() {
	mViewer->getSceneData()->asGroup()->removeChild(mPickGroup);
	mPickGroup.release();
	mPickGroup = new osg::Group;
	mPickGroup->setName("PickGroup");
	mViewer->getSceneData()->asGroup()->addChild(mPickGroup);
	allowPointsNum = 0;
}
/**画一个点*/
void OSGPickHandler::OnePoint() {
	Reset();
	allowPointsNum = 1;
}
/**画二个点*/
void OSGPickHandler::TwoMeause() {
	Reset();
	allowPointsNum = 2;
}
void OSGPickHandler::DrawTips(osg::Vec3 pos) {
	switch (allowPointsNum)
	{
	case 1:
	{
		if (mOnePoint.valid()) {
			mPickGroup->removeChild(mOnePoint);
			mOnePoint.release();
		}
		QString str("选择点1");
		mOnePoint = createSelPoint(str,pos);
		if (mOnePoint.valid()) {
			std::cout << "OK" << std::endl;
		}
		std::string ttt = mOnePoint->getName();
		mPickGroup->addChild(mOnePoint);

	}
		break;
	case 2:
	{
		if (!mOnePoint.valid()) {
			QString str("选择点1");
			mOnePoint = createSelPoint(str, pos);
		}
		else {
			if (mTwoPoint.valid()) {
				mPickGroup->removeChild(mTwoPoint);
				mTwoPoint.release();
			}
			QString str("选择点2");
			mTwoPoint = createSelPoint(str, pos);
		}
	}
		break;
	default:
		break;
	}
}
//osg::Geode* OSGPickHandler::DrawOnePoint(QString name, osg::Vec3& pos) {
//	osg::ref_ptr<osg::Geode> geode = createSelPoint(pos);
//	QByteArray barr = name.toLocal8Bit();
//	char* bdata = barr.data();
//	//geode->setName(bdata);
//	mPickGroup->addChild(geode);
//	return geode.get();
//}
osg::ref_ptr<osg::Geode> OSGPickHandler::createSelPoint(QString name, osg::Vec3& pos) {
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	QByteArray barr = name.toLocal8Bit();
	char* bdata = barr.data();
	geode->setName(bdata);
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	osg::ref_ptr<osg::StateSet> stateSet = geom->getOrCreateStateSet();
	osg::ref_ptr<osg::Point> pointSize = new osg::Point;
	pointSize->setSize(10.0);
	stateSet->setAttribute(pointSize, osg::StateAttribute::ON);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	//traits->samples = 16;
	/*osg::Multisample* pms = new osg::Multisample;
	pms->setSampleCoverage(1, true);*/
	stateSet->setMode(GL_POINT_SMOOTH, osg::StateAttribute::ON);
	stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	//osg::PointSprite *sprite = new osg::PointSprite();
	//stateSet->setTextureAttributeAndModes(0, sprite, osg::StateAttribute::ON);

	//创建顶点数组，注意顺序逆时针
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(pos);
	//设置顶点数据
	geom->setVertexArray(v.get());
	//创建颜色数组
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//设置颜色数组
	geom->setColorArray(vc.get());
	//设置颜色绑定方式为单个顶点
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//添加图元，
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, v->size()));

	//将图元添加至叶子节点
	geode->addDrawable(geom.get());

	//geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	//自动生成顶点法线(必须在addDrawable后)
	osgUtil::SmoothingVisitor::smooth(*(geom.get()));
	return geode;
}