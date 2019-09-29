#include "OSGPickHandler.h"
#include <QByteArray>
#include <QString>
#include <iostream>
#include <sstream>


OSGPickHandler::OSGPickHandler():osgGA::GUIEventHandler()
{
}


OSGPickHandler::~OSGPickHandler()
{
}
bool OSGPickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa){
	osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if (!viewer)return false;
	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::PUSH:
	{
		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) {
			pick(viewer, ea);
		}
		else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) {

		}
		//QByteArray barr = QString(" Û±ÍPUSH£∫").toLocal8Bit();
		//std::cout << barr.data() << std::endl;
	}
	break;
	}
	return false;
}
void OSGPickHandler::pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea){
	//osg::ref_ptr<PointIntersector> intersector = new PointIntersector(osgUtil::Intersector::WINDOW, osg::Vec3(ea.getX() - 0.1, ea.getY() - 0.1, 0), osg::Vec3(ea.getX() + 0.1, ea.getY() + 0.1, 0));
	osg::ref_ptr<PointIntersector> intersector = new PointIntersector(osgUtil::Intersector::WINDOW, ea.getX(), ea.getY());
	     osgUtil::IntersectionVisitor iv(intersector.get());
		 view->getCamera()->accept(iv);
	
		 if (intersector->containsIntersections())
		 {
			 std::vector<osg::Vec3d> points;
			 for (auto iter = intersector->getIntersections().begin(); iter != intersector->getIntersections().end(); iter++)
			 {
				 points.push_back(iter->getWorldIntersectPoint());
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