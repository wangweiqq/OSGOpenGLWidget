#pragma once
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/Viewer>
#include "PointIntersector.h"
class OSGPickHandler :
	public osgGA::GUIEventHandler
{
public:
	OSGPickHandler();
	virtual ~OSGPickHandler();
	void Reset() {
	
	}
	void OnePoint() {
	
	}
	void TwoMeause() {
	
	}
protected:
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
	virtual void pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea);
};

