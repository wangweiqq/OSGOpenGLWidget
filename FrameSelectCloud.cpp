#include "FrameSelectCloud.h"
#include <iostream>
#include <osg/PointSprite>
#include <QString>
extern bool IsVerfyModelName(QString str);


FrameSelectCloud::FrameSelectCloud(osg::ref_ptr<osgViewer::Viewer> viewer) :
	osg::Referenced(), mViewer(viewer)//, mGeode(new osg::Geode)
{
	//mGeode->setName("TempPoint");	
	/*osg::StateSet* set = mGeode->getOrCreateStateSet();
	osg::PointSprite *sprite = new osg::PointSprite();
	set->setTextureAttributeAndModes(0, sprite, osg::StateAttribute::ON);
	set->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);*/

	//mViewer->getSceneData()->asGroup()->addChild(mGeode);
	list.clear();
}

FrameSelectCloud::~FrameSelectCloud()
{
	mViewer->getSceneData()->asGroup()->removeChild(mGeode);
}
void FrameSelectCloud::SetFirstPos(osg::Vec2 pos) {
	clear();
	IsAllowDrag = true;
	mSPos1 = pos;

	mHUDCamera = new osg::Camera;
	mHUDCamera->setName("TMP_RectSelCamera");
	mHUDCamera->setViewMatrix(osg::Matrix::identity());
	mHUDCamera->setRenderOrder(osg::Camera::POST_RENDER);
	mHUDCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
	mHUDCamera->setAllowEventFocus(false);
	mHUDCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	osg::GraphicsContext::WindowingSystemInterface *wsi = osg::GraphicsContext::getWindowingSystemInterface();
	if (!wsi)
	{
		//ERROR
		return;
	}
	unsigned int width, height;
	wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), width, height);
	mHUDCamera->setProjectionMatrixAsOrtho2D(0, width, 0, height);
	mHUDCamera->setViewport(0, 0, width, height);
	mViewer->getSceneData()->asGroup()->addChild(mHUDCamera);

}
void FrameSelectCloud::DrawSelRect(osg::Vec2 curPos) {
	if (!IsAllowDrag && !mHUDCamera.valid()) {
		return;
	}
	float minX = std::min(mSPos1.x(), curPos.x());
	float maxX = std::max(mSPos1.x(), curPos.x());
	float minY = std::min(mSPos1.y(), curPos.y());
	float maxY = std::max(mSPos1.y(), curPos.y());
	osg::Vec3 pos1 = osg::Vec3(minX, minY, 0.0f);
	osg::Vec3 pos2 = osg::Vec3(maxX, minY, 0.0f);
	osg::Vec3 pos3 = osg::Vec3(maxX, maxY, 0.0f);
	osg::Vec3 pos4 = osg::Vec3(minX, maxY, 0.0f);

	mHUDCamera->removeChildren(0, mHUDCamera->getNumChildren());
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	osg::StateSet* stateset = geode->getOrCreateStateSet();
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);

	osg::ref_ptr<osg::Geometry> _boxGm = new osg::Geometry;
	geode->addDrawable(_boxGm);
	mHUDCamera->addChild(geode);

	osg::ref_ptr<osg::Vec3Array> vertex = new osg::Vec3Array;
	vertex->push_back(pos1); 
	vertex->push_back(pos2);
	vertex->push_back(pos3);
	vertex->push_back(pos4);
	_boxGm->setVertexArray(vertex);

	//创建颜色数组
	osg::ref_ptr<osg::Vec4Array> vboxColor = new osg::Vec4Array();
	vboxColor->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
	_boxGm->setColorArray(vboxColor);
	_boxGm->setColorBinding(osg::Geometry::BIND_OVERALL);
	_boxGm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, 4));
	//将图元添加至叶子节点
	geode->addDrawable(_boxGm.get());
	//自动生成顶点法线(必须在addDrawable后)
	osgUtil::SmoothingVisitor::smooth(*(_boxGm.get()));
}
//清除所有选择的点
void FrameSelectCloud::clear()
{
	list.clear();
	//mGeode->removeDrawables(0, mGeode->getNumDrawables());
	if (mGeode.valid()) {
		mViewer->getSceneData()->asGroup()->removeChild(mGeode);
		mGeode.~ref_ptr();
	}
}
//bool FrameSelectCloud::FramePick(const osgGA::GUIEventAdapter& ea) 
//{
//	if (!IsAllowDrag) 
//	{
//		return false;
//	}
//	switch (ea.getEventType())
//	{
//	case osgGA::GUIEventAdapter::PUSH:
//	{
//		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) {
//			mSPos1 = osg::Vec2(ea.getX(), ea.getY());
//			clear();
//			IsAllowDrag = true;
//			return true;
//		}
//	}
//	break;
//	case osgGA::GUIEventAdapter::DRAG:
//	{
//		if (IsAllowDrag) {
//			float minX = std::min(mSPos1.x(), ea.getX());
//			float maxX = std::max(mSPos1.x(), ea.getX());
//			float minY = std::min(mSPos1.y(), ea.getY());
//			float maxY = std::max(mSPos1.y(), ea.getY());
//			osg::ref_ptr<osgUtil::PolytopeIntersector> intersector2 = new osgUtil::PolytopeIntersector(osgUtil::Intersector::WINDOW, minX, minY, maxX, maxY);
//			osgUtil::IntersectionVisitor iv2(intersector2);
//			mViewer->getCamera()->accept(iv2);
//			list.clear();
//			if (intersector2->containsIntersections()) {
//				//osg::Drawable* geometry = nullptr;
//				auto iter = intersector2->getIntersections().begin();
//				for (; iter != intersector2->getIntersections().end(); ++iter) {
//					if ((iter->nodePath).back()->getName() == "CloudPoints")
//					{
//						list.insert(std::make_pair(iter->primitiveIndex, (osg::Vec3)iter->localIntersectionPoint));
//					}
//				}
//				Redraw();
//			}
//		}
//	}
//	break;
//	case  osgGA::GUIEventAdapter::RELEASE:
//		if (IsAllowDrag) {
//			if (mCallBack != nullptr) {
//				mCallBack(list);
//			}
//			IsAllowDrag = false;
//		}
//		break;
//	}
//	return IsAllowDrag;
//}
bool FrameSelectCloud::DragFrame(osg::Vec2 curPos) {
	if (IsAllowDrag) {
		float minX = std::min(mSPos1.x(), curPos.x());
		float maxX = std::max(mSPos1.x(), curPos.x());
		float minY = std::min(mSPos1.y(), curPos.y());
		float maxY = std::max(mSPos1.y(), curPos.y());
		osg::ref_ptr<osgUtil::PolytopeIntersector> intersector2 = new osgUtil::PolytopeIntersector(osgUtil::Intersector::WINDOW, minX, minY, maxX, maxY);
		osgUtil::IntersectionVisitor iv2(intersector2);
		mViewer->getCamera()->accept(iv2);
		list.clear();
		mSelNodeName = "";
		if (intersector2->containsIntersections()) {
			//osg::Drawable* geometry = nullptr;
			auto iter = intersector2->getIntersections().begin();
			for (; iter != intersector2->getIntersections().end(); ++iter) {
				//if ((iter->nodePath).back()->getName() == "CloudPoints")
				if(IsVerfyModelName((iter->nodePath).back()->getName().c_str()))
				{
					mSelNodeName = (iter->nodePath).back()->getName().c_str();
					list.insert(std::make_pair(iter->primitiveIndex, (osg::Vec3)iter->localIntersectionPoint));
				}
			}
			//std::cout << "点数:" << intersector2->getIntersections().size() << std::endl;
			Redraw();
		}
	}
	return IsAllowDrag;
}
void FrameSelectCloud::Redraw() {
	if (mHUDCamera.valid()) {
		mViewer->getSceneData()->asGroup()->removeChild(mHUDCamera);
		mHUDCamera.~ref_ptr();
	}
	if (mGeode.valid()) {
		mViewer->getSceneData()->asGroup()->removeChild(mGeode);
		mGeode.~ref_ptr();
	}
	mGeode = new osg::Geode();

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	osg::ref_ptr<osg::StateSet> stateSet = geom->getOrCreateStateSet();
	osg::ref_ptr<osg::Point> pointSize = new osg::Point;
	pointSize->setSize(1.0);
	stateSet->setAttribute(pointSize, osg::StateAttribute::ON);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	stateSet->setMode(GL_POINT_SMOOTH, osg::StateAttribute::ON);
	stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);


	//geom->setName("cloudpointsgeometry");
	//osg::ref_ptr<osg::DrawPixels> geom = new osg::DrawPixels;
	//创建顶点数组，注意顺序逆时针
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	for (auto it = list.begin(); it != list.end(); ++it) {
		v->push_back((*it).second);
	}
	//osg::ref_ptr<osg::Vec3dArray> v = ReadModelFile("model.txt");
	//设置顶点数据
	geom->setVertexArray(v.get());

	//创建颜色数组
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//设置颜色数组
	geom->setColorArray(vc.get());
	//设置颜色绑定方式为单个顶点
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, v->size()));

	//将图元添加至叶子节点
	mGeode->addDrawable(geom.get());
	
	//自动生成顶点法线(必须在addDrawable后)
	//osgUtil::SmoothingVisitor::smooth(*(geom.get()));
	//mViewer->getSceneData()->asGroup()->addChild(geode);
	osg::Group* root = mViewer->getSceneData()->asGroup();
	root->addChild(mGeode);
}