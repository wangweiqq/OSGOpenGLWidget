#pragma execution_character_set("utf-8")
#include "OSGPickHandler.h"
#include <QByteArray>
#include <QString>
#include <iostream>
#include <sstream>
#include <set>
extern bool IsVerfyModelName(QString str);

//PointBuildBoard::PointBuildBoard(QString _id, osg::Vec3 selPointPos, osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Camera> camera):osg::Referenced(), mSelPointPos(selPointPos), _viewer(viewer), _camera(camera){
//	QByteArray strArr = _id.toLocal8Bit();
//	mId = strArr.data();
//	_geode = new osg::Geode;
//	_geode->setName(mId);
//	//设置状态关闭灯光
//	osg::StateSet* stateset = _geode->getOrCreateStateSet();
//	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
//	stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
//	_camera->addChild(_geode);
//	//世界坐标转屏幕坐标(确定Box的位置)
//	osg::Camera* _tCamera = _viewer->getCamera();
//	osg::Matrix VPW = _tCamera->getViewMatrix() *
//		_tCamera->getProjectionMatrix() *
//		_tCamera->getViewport()->computeWindowMatrix();
//	//当前点偏移
//
//	mBoxPos = mSelPointPos * VPW + osg::X_AXIS * 10;
//	osg::Viewport* viewport = _tCamera->getViewport();
//	unsigned int width  = viewport->width();
//	unsigned int height = viewport->height();
//	float _x = mBoxPos.x();
//	float _y = mBoxPos.y();
//	float _z = mBoxPos.z();
//	if (mBoxPos.x() + _wbox > width) {
//		_x = width - _wbox;
//	}
//	if (mBoxPos.y() + _hbox > height) {
//		_y = height - _hbox;
//	}
//	mBoxPos = osg::Vec3(_x, _y, _z);
//
//	_cubrelpos.clear();
//	_cubrelpos.push_back(osg::Vec3(0.0, 0.0, 0.0));
//	_cubrelpos.push_back(osg::Vec3(_cubwidth, 0.0, 0.0));
//	_cubrelpos.push_back(osg::Vec3(_cubwidth, _cubwidth, 0.0));
//	_cubrelpos.push_back(osg::Vec3(0.0, _cubwidth, 0.0));
//	//std::cout << "1.(" << window.x() << "," << window.y() << "," << window.z() << ")" << std::endl;
//	CreateBox();
//	//_viewer->getSceneData()->asGroup()->addChild(createHUD(_viewer)); ;
//}
//PointBuildBoard::~PointBuildBoard() {
//	_camera->removeChild(_geode);
//}
////osg::ref_ptr<osg::Node> PointBuildBoard::createHUD(osgViewer::Viewer* viewer) {
////	int padding = 5;
////	int w_box = 120;
////	int h_box = 80;
////	osg::Vec3 w_pos(w_box, 0.0f, 0.0f);
////	osg::Vec3 h_pos(0.0f, h_box, 0.0f);
////	//Box位置偏移
////	osg::Vec3 z_boxoffset(0.0f, 0.0f, -0.1f);
////	//Box位置
////	osg::Vec3 p_box(100.0, 100.0, 0);
////	//Box绝对位置（左下角为0点）
////	osg::Vec3 box_relpos[] = { z_boxoffset ,z_boxoffset + w_pos ,z_boxoffset + w_pos + h_pos ,z_boxoffset + h_pos };
////
////	//x，y，z小方块绘制
////	int cub_width = 15;
////	osg::Vec3 cub_relpos[] = { osg::Vec3(0.0, 0.0, 0.0) ,osg::Vec3(cub_width, 0.0, 0.0) ,osg::Vec3(cub_width, cub_width, 0.0) ,osg::Vec3(0.0, cub_width, 0.0) };
////
////	//字体位置
////	osg::Vec3 f1_pos = p_box + h_pos - osg::Vec3(-1.0f, 1.0f, 0.0f)*padding;
////
////
////	//创建HUD相机
////	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
////	camera->setViewMatrix(osg::Matrix::identity());
////	camera->setRenderOrder(osg::Camera::POST_RENDER);
////	camera->setClearMask(GL_DEPTH_BUFFER_BIT);
////	camera->setAllowEventFocus(false);
////	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
////	//std::cout << "screen 1" << this->width() << "," << this->height() << std::endl;
////	/*camera->setProjectionMatrixAsOrtho2D(0, this->width(), 0, this->height());
////	camera->setViewport(0, 0, this->width(), this->height());*/
////	camera->setProjectionMatrixAsOrtho2D(0, 1024, 0, 768);
////	camera->setViewport(0, 0, 1024, 768);
////
////	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
////	//设置状态关闭灯光
////	osg::StateSet* stateset = geode->getOrCreateStateSet();
////	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
////	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
////
////	osg::ref_ptr<osg::Geometry> gm = new osg::Geometry;
////	geode->addDrawable(gm);
////
////	//压入顶点
////	osg::Vec3Array *vertex = new osg::Vec3Array;
////	for (int i = 0; i < sizeof(box_relpos) / sizeof(box_relpos[0]); ++i) {
////		vertex->push_back(box_relpos[i] + p_box);
////	}
////	gm->setVertexArray(vertex);
////
////	//创建颜色数组
////	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
////	vc->push_back(osg::Vec4(0.75f, 0.81f, 0.84f, 0.8f));
////	//设置颜色数组
////	gm->setColorArray(vc.get());
////	//设置颜色绑定方式为单个顶点
////	gm->setColorBinding(osg::Geometry::BIND_OVERALL);
////
////	//法线
////	osg::Vec3Array *norm = new osg::Vec3Array;
////	norm->push_back(osg::Vec3(0.0, 0.0, 1.0));
////	gm->setNormalArray(norm);
////	gm->setNormalBinding(osg::Geometry::BIND_OVERALL);
////	gm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertex->size()));
////
////	osg::ref_ptr<osg::Geometry> gm2 = new osg::Geometry;
////	geode->addDrawable(gm2);
////
////	//世界坐标转屏幕坐标
////	osg::Camera* _tCamera = viewer->getCamera();
////	osg::Matrix VPW = _tCamera->getViewMatrix() *
////		_tCamera->getProjectionMatrix() *
////		_tCamera->getViewport()->computeWindowMatrix();
////	osg::Vec3 window = osg::Vec3(-202.414f, 961.0f, 70.0564f) * VPW;
////	std::cout << "1.(" << window.x() << "," << window.y() << "," << window.z() << ")" << std::endl;
////
////	//压入顶点
////	osg::Vec3Array *vertex2 = new osg::Vec3Array;
////	vertex2->push_back(box_relpos[0] + p_box);
////	vertex2->push_back(box_relpos[0] + p_box + osg::X_AXIS * 10);
////	vertex2->push_back(osg::Vec3(379.869f, 385.842f, 1.00056f));//测试顶点
////	gm2->setVertexArray(vertex2);
////
////	//创建颜色数组
////	osg::ref_ptr<osg::Vec4Array> vc2 = new osg::Vec4Array();
////	vc2->push_back(osg::Vec4(0.75f, 0.81f, 0.84f, 0.8f));
////	//设置颜色数组
////	gm2->setColorArray(vc2.get());
////	//设置颜色绑定方式为单个顶点
////	gm2->setColorBinding(osg::Geometry::BIND_OVERALL);
////
////	gm2->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, vertex2->size()));
////
////	//设置字体
////	osg::ref_ptr<osgText::Text> text = new osgText::Text;
////	text->setFont("msyh.ttc");
////	text->setText(L"Point #253504");//动态传入ID号
////	text->setLineSpacing(0.25f);
////	text->setCharacterSize(10);
////	text->setColor(osg::Vec4(0.0, 0.0, 0.0, 1.0));
////	int chheight = text->getCharacterHeight();
////	//int chheight2 = text->getFontHeight();
////	//osg::BoundingBox f1_boundbox = text->getBoundingBox();
////	//int f1_height = f1_boundbox.yMax() - f1_boundbox.yMin();
////	osg::Vec3 f1_pos2 = osg::Vec3(f1_pos.x(), f1_pos.y() - chheight, f1_pos.z());
////	text->setPosition(f1_pos2);
////
////	//绘制方块1
////	//osg::Vec3 cub_pos1 = f1_pos2 - osg::Vec3(0.0f, 1.0f, 0.0f)*text->getFontHeight() - osg::Y_AXIS*padding;
////	osg::Vec3 cub_pos1 = f1_pos2 - osg::Y_AXIS* chheight * 2 - osg::Y_AXIS*padding;
////	osg::ref_ptr<osg::Geometry> gm3 = new osg::Geometry;
////	geode->addDrawable(gm3);
////
////	//压入顶点
////	osg::Vec3Array *vertex3 = new osg::Vec3Array;
////	for (int i = 0; i < sizeof(cub_relpos) / sizeof(cub_relpos[0]); ++i) {
////		vertex3->push_back(cub_relpos[i] + cub_pos1);
////	}
////	gm3->setVertexArray(vertex3);
////
////	//创建颜色数组
////	osg::ref_ptr<osg::Vec4Array> vc3 = new osg::Vec4Array();
////	vc3->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
////	//设置颜色数组
////	gm3->setColorArray(vc3.get());
////	//设置颜色绑定方式为单个顶点
////	gm3->setColorBinding(osg::Geometry::BIND_OVERALL);
////	gm3->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertex3->size()));
////
////	//绘制方块2
////	osg::Vec3 cub_pos2 = cub_pos1 - osg::Y_AXIS*cub_width;
////	osg::ref_ptr<osg::Geometry> gm4 = new osg::Geometry;
////	geode->addDrawable(gm4);
////
////	//压入顶点
////	osg::Vec3Array *vertex4 = new osg::Vec3Array;
////	for (int i = 0; i < sizeof(cub_relpos) / sizeof(cub_relpos[0]); ++i) {
////		vertex4->push_back(cub_relpos[i] + cub_pos2);
////	}
////	gm4->setVertexArray(vertex4);
////
////	//创建颜色数组
////	osg::ref_ptr<osg::Vec4Array> vc4 = new osg::Vec4Array();
////	vc4->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
////	//设置颜色数组
////	gm4->setColorArray(vc4.get());
////	//设置颜色绑定方式为单个顶点
////	gm4->setColorBinding(osg::Geometry::BIND_OVERALL);
////
////	gm4->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertex4->size()));
////	//绘制方块3
////	osg::Vec3 cub_pos3 = cub_pos2 - osg::Y_AXIS*cub_width;
////	osg::ref_ptr<osg::Geometry> gm5 = new osg::Geometry;
////	geode->addDrawable(gm5);
////
////	//压入顶点
////	osg::Vec3Array *vertex5 = new osg::Vec3Array;
////	for (int i = 0; i < sizeof(cub_relpos) / sizeof(cub_relpos[0]); ++i) {
////		vertex5->push_back(cub_relpos[i] + cub_pos3);
////	}
////	gm5->setVertexArray(vertex5);
////
////	//创建颜色数组
////	osg::ref_ptr<osg::Vec4Array> vc5 = new osg::Vec4Array();
////	vc5->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
////	//设置颜色数组
////	gm5->setColorArray(vc5.get());
////	//设置颜色绑定方式为单个顶点
////	gm5->setColorBinding(osg::Geometry::BIND_OVERALL);
////
////	gm5->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertex5->size()));
////
////	//字体位置
////	//osg::Vec3 f1_pos = p_box + h_pos - osg::Vec3(-1.0f, 1.0f, 0.0f)*padding;
////
////	geode->addDrawable(text);
////	camera->addChild(geode);
////
////	return camera;
////}
//void PointBuildBoard::CreateBox(osg::Vec4 boxColor, float width, float height) {
//	if (_boxGm.valid()) {
//		_geode->removeChild(_boxGm);
//		_boxGm.~ref_ptr();
//	}
//	_wbox = width;
//	_hbox = height;
//	_boxrelpos.clear();
//	//Box位置偏移
//	osg::Vec3 z_boxoffset(0.0f, 0.0f, 0.0f);
//	_boxrelpos.push_back(z_boxoffset);
//	_boxrelpos.push_back(z_boxoffset + osg::X_AXIS*_wbox);
//	_boxrelpos.push_back(z_boxoffset + osg::X_AXIS*_wbox + osg::Y_AXIS*_hbox);
//	_boxrelpos.push_back(z_boxoffset + osg::Y_AXIS*_hbox);
//
//	_boxGm = new osg::Geometry;
//	_boxGm->setName("BoxPanel");
//	_geode->addDrawable(_boxGm);
//	
//
//	if (mXIcon.valid()) {
//		_geode->removeChild(mXIcon);
//		mXIcon.~ref_ptr();
//	}
//	if (mYIcon.valid()) {
//		_geode->removeChild(mYIcon);
//		mYIcon.~ref_ptr();
//	}
//	if (mZIcon.valid()) {
//		_geode->removeChild(mZIcon);
//		mZIcon.~ref_ptr();
//	}
//	mXIcon = CreateIcon("XIcon", osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
//	mYIcon = CreateIcon("YIcon", osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
//	mZIcon = CreateIcon("ZIcon", osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
//	if (_XLabel.valid()) {
//		_geode->removeChild(_XLabel);
//		_XLabel.~ref_ptr();
//	}
//	_XLabel = CreateText("X", "X", _cubwidth - 2);
//	_XLabel->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
//	if (_YLabel.valid()) {
//		_geode->removeChild(_XLabel);
//		_YLabel.~ref_ptr();
//	}
//	_YLabel = CreateText("Y", "Y", _cubwidth - 2);
//	_YLabel->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
//	if (_ZLabel.valid()) {
//		_geode->removeChild(_XLabel);
//		_ZLabel.~ref_ptr();
//	}
//	_ZLabel = CreateText("Z", "Z", _cubwidth - 2);
//	_ZLabel->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
//
//	//标题绘制
//	if (mTitle.valid()) {
//		_geode->removeChild(mTitle);
//		mTitle.~ref_ptr();
//	}
//	mTitle = CreateText("Title", "Point #253504");
//	if (mTxtX.valid()) {
//		_geode->removeChild(mTxtX);
//		mTxtX.~ref_ptr();
//	}
//	mTxtX = CreateText("Title", "Point #253504");
//	if (mTxtY.valid()) {
//		_geode->removeChild(mTxtY);
//		mTxtX.~ref_ptr();
//	}
//	mTxtY = CreateText("Title", "Point #253504");
//	if (mTxtZ.valid()) {
//		_geode->removeChild(mTxtZ);
//		mTxtZ.~ref_ptr();
//	}
//	mTxtZ = CreateText("Title", "Point #253504");
//
//	UpdateBoxPos();
//
//	//创建颜色数组
//	osg::ref_ptr<osg::Vec4Array> vboxColor = new osg::Vec4Array();
//	vboxColor->push_back(boxColor);
//	_boxGm->setColorArray(vboxColor);
//	//设置颜色绑定方式为单个顶点
//	_boxGm->setColorBinding(osg::Geometry::BIND_OVERALL);
//
//	_boxGm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
//	mXIcon->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
//	mYIcon->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
//	mZIcon->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
//}
//void PointBuildBoard::ResetSelPos(osg::Vec3 selPointPos) {
//	mSelPointPos = selPointPos;
//}
//void  PointBuildBoard::UpdateBoxPos() {
//	if (!_boxGm.valid()) {
//		return;
//	}
//	//UI三角形，用于指示
//	osg::Camera* _tCamera = _viewer->getCamera();
//	osg::Matrix VPW = _tCamera->getViewMatrix() *
//		_tCamera->getProjectionMatrix() *
//		_tCamera->getViewport()->computeWindowMatrix();
//	//选择点在屏幕上的坐标
//	osg::Vec3 selPosScreen = mSelPointPos * VPW;
//
//	std::vector<osg::Vec3> vecBoxPos = { _boxrelpos[0] + osg::Vec3(mBoxPos.x(),mBoxPos.y(),0.0) ,
//		_boxrelpos[1] + osg::Vec3(mBoxPos.x(),mBoxPos.y(),0.0),
//		_boxrelpos[2] + osg::Vec3(mBoxPos.x(),mBoxPos.y(),0.0),
//		_boxrelpos[3] + osg::Vec3(mBoxPos.x(),mBoxPos.y(),0.0)
//	};
//
//	if (!_triangleGm.valid()) {
//		_triangleGm = new osg::Geometry;
//		//创建颜色数组
//		osg::ref_ptr<osg::Vec4Array> vTriangleColor = new osg::Vec4Array();
//		vTriangleColor->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
//		_triangleGm->setColorArray(vTriangleColor);
//		//设置颜色绑定方式为单个顶点
//		_triangleGm->setColorBinding(osg::Geometry::BIND_OVERALL);
//		_geode->addDrawable(_triangleGm);
//	}
//	//点在Box范围内则不画三角形	
//	if (vecBoxPos[0].x() <= selPosScreen.x() && vecBoxPos[0].y() <= selPosScreen.y() &&
//		selPosScreen.x() <= vecBoxPos[2].x() && selPosScreen.y() <= vecBoxPos[2].y()) {
//		//在box内部
//		_triangleGm->setNodeMask(0);
//	}
//	else {
//		_triangleGm->setNodeMask(1);
//		osg::ref_ptr<osg::Vec3Array> vertexTrangle = new osg::Vec3Array;
//		std::vector<float> vecLen = { (vecBoxPos[0] - selPosScreen).length(),
//			(vecBoxPos[1] - selPosScreen).length() ,
//			(vecBoxPos[2] - selPosScreen).length(),
//			(vecBoxPos[3] - selPosScreen).length()
//		};
//		//取距离最小值索引
//		int minindex = 0;
//		for (int i = 1; i < vecLen.size(); ++i) {
//			if (vecLen[i] < vecLen[minindex]) {
//				minindex = i;
//			}
//		}
//		float factor = 20.0f;
//		switch (minindex)
//		{
//		case 0:
//			//下面或左面
//			if (vecBoxPos[0].x() > selPosScreen.x()) {
//				//左边
//				vertexTrangle->push_back(vecBoxPos[0]);
//				vertexTrangle->push_back(vecBoxPos[0] + osg::Y_AXIS*factor);
//			}
//			else {
//				//下边
//				vertexTrangle->push_back(vecBoxPos[0] + osg::X_AXIS * factor);
//				vertexTrangle->push_back(vecBoxPos[0]);
//			}
//			break;
//		case 1:
//			if (vecBoxPos[1].x() < selPosScreen.x()) {
//				//右边
//				vertexTrangle->push_back(vecBoxPos[1] + osg::Y_AXIS * factor);
//				vertexTrangle->push_back(vecBoxPos[1]);
//			}
//			else {
//				//下边
//				vertexTrangle->push_back(vecBoxPos[1]);
//				vertexTrangle->push_back(vecBoxPos[1] - osg::X_AXIS * factor);
//			}
//			break;
//		case 2:
//			if (vecBoxPos[2].x() < selPosScreen.x()) {
//				//右边
//				vertexTrangle->push_back(vecBoxPos[2]);
//				vertexTrangle->push_back(vecBoxPos[2] - osg::Y_AXIS * factor);
//			}
//			else {
//				//上边				
//				vertexTrangle->push_back(vecBoxPos[2] - osg::X_AXIS * factor);
//				vertexTrangle->push_back(vecBoxPos[2]);
//			}
//			break;
//		case 3:
//			if (vecBoxPos[3].x() > selPosScreen.x()) {
//				//左边
//				vertexTrangle->push_back(vecBoxPos[3] - osg::Y_AXIS * factor);
//				vertexTrangle->push_back(vecBoxPos[3]);
//			}
//			else {
//				//上边	
//				vertexTrangle->push_back(vecBoxPos[3]);
//				vertexTrangle->push_back(vecBoxPos[3] + osg::X_AXIS * factor);
//			}
//			break;
//		}
//		vertexTrangle->push_back(selPosScreen);
//		_triangleGm->setVertexArray(vertexTrangle);
//	}	
//	_triangleGm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 3));
//	//////////////////////////////////////
//
//	osg::ref_ptr<osg::Vec3Array> vertex = new osg::Vec3Array;
//	for (int i = 0; i < vecBoxPos.size(); ++i) {
//		vertex->push_back(vecBoxPos[i]);
//	}
//	_boxGm->setVertexArray(vertex);
//
//	//标题位置
//	osg::Vec3 rowpos1 = vecBoxPos[3] - osg::Vec3(-1.0f, 1.0f, 0.0f)*_padding;
//	float chheight = 0;
//	if (mTitle.valid()) {
//		chheight = mTitle->getCharacterHeight();
//		rowpos1 -= osg::Y_AXIS*chheight;
//		mTitle->setPosition(rowpos1);
//	}
//	
//	//X轴图标位置
//	osg::Vec3 rowpos2 = rowpos1 - osg::Y_AXIS* chheight * 2 - osg::Y_AXIS* _padding;
//	//Y轴图标位置
//	osg::Vec3 rowpos3 = rowpos2 - osg::Y_AXIS*_cubwidth;
//	//Z轴图标位置
//	osg::Vec3 rowpos4 = rowpos3 - osg::Y_AXIS*_cubwidth;
//	//X文本位置
//	osg::Vec3 rowtxt2 = rowpos2 + osg::X_AXIS*(_cubwidth + _padding) + osg::Y_AXIS*(((float)_cubwidth - chheight));
//	//Y文本位置
//	osg::Vec3 rowtxt3 = rowpos3 + osg::X_AXIS*(_cubwidth + _padding) + osg::Y_AXIS*(((float)_cubwidth - chheight));
//	//Z文本位置
//	osg::Vec3 rowtxt4 = rowpos4 + osg::X_AXIS*(_cubwidth + _padding) + osg::Y_AXIS*(((float)_cubwidth - chheight));
//
//	if (mXIcon.valid()) {
//		osg::Vec3Array *vericon1 = new osg::Vec3Array;
//		for (int i = 0; i < _cubrelpos.size(); ++i) {
//			vericon1->push_back(_cubrelpos[i] + rowpos2);
//		}
//		mXIcon->setVertexArray(vericon1);
//	}
//	if (_XLabel.valid()) {
//		_XLabel->setPosition(rowpos2 + osg::X_AXIS * 3 + osg::Y_AXIS * 2);
//	}
//	if (mYIcon.valid()) {
//		osg::Vec3Array *vericon2 = new osg::Vec3Array;
//		for (int i = 0; i < _cubrelpos.size(); ++i) {
//			vericon2->push_back(_cubrelpos[i] + rowpos3);
//		}
//		mYIcon->setVertexArray(vericon2);
//	}
//	if (_YLabel.valid()) {
//		_YLabel->setPosition(rowpos3 + osg::X_AXIS * 3 + osg::Y_AXIS * 2);
//	}
//	if (mZIcon.valid()) {
//		osg::Vec3Array *vericon3 = new osg::Vec3Array;
//		for (int i = 0; i < _cubrelpos.size(); ++i) {
//			vericon3->push_back(_cubrelpos[i] + rowpos4);
//		}
//		mZIcon->setVertexArray(vericon3);
//	}
//	if (_ZLabel.valid()) {
//		_ZLabel->setPosition(rowpos4 + osg::X_AXIS * 3 + osg::Y_AXIS * 2);
//	}
//	if (mTxtX.valid()) {
//		mTxtX->setPosition(rowtxt2);
//		chheight = mTxtX->getCharacterHeight();
//	}
//	if (mTxtY.valid()) {
//		mTxtY->setPosition(rowtxt3);
//		chheight = mTxtY->getCharacterHeight();
//	}
//	if (mTxtZ.valid()) {
//		mTxtZ->setPosition(rowtxt4);
//		chheight = mTxtZ->getCharacterHeight();
//	}
//}
//osg::ref_ptr<osg::Geometry> PointBuildBoard::CreateIcon(std::string id, osg::Vec4 color) {
//	osg::ref_ptr<osg::Geometry> gm = new osg::Geometry;
//	gm->setName(id);
//	//创建颜色数组
//	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
//	vc->push_back(color);
//	//设置颜色数组
//	gm->setColorArray(vc.get());
//	//设置颜色绑定方式为单个顶点
//	gm->setColorBinding(osg::Geometry::BIND_OVERALL);
//	_geode->addDrawable(gm);
//	return gm;
//}
//osg::ref_ptr<osgText::Text> PointBuildBoard::CreateText(std::string id, QString str, int fontSize) {
//	//设置字体
//	osg::ref_ptr<osgText::Text> text = new osgText::Text;
//	text->setName(id);
//	text->setFont("msyh.ttc");
//	QByteArray barr = str.toLocal8Bit();
//	char* bdata = barr.data();
//	text->setText(bdata);//动态传入ID号
//	text->setLineSpacing(0.25f);
//	text->setCharacterSize(fontSize);
//	text->setColor(osg::Vec4(0.0, 0.0, 0.0, 1.0));
//	_geode->addChild(text);
//	//int chheight = text->getCharacterHeight();
//	////int chheight2 = text->getFontHeight();
//	////osg::BoundingBox f1_boundbox = text->getBoundingBox();
//	////int f1_height = f1_boundbox.yMax() - f1_boundbox.yMin();
//	//osg::Vec3 f1_pos2 = osg::Vec3(f1_pos.x(), f1_pos.y() - chheight, f1_pos.z());
//	//text->setPosition(f1_pos2);
//	return text;
//}
//void PointBuildBoard::SetTitle(QString str) {
//	if (!mTitle.valid()) {
//		return;
//	}
//	QByteArray barr = str.toLocal8Bit();
//	char* bdata = barr.data();
//	mTitle->setText(bdata);
//}
//void PointBuildBoard::SetStrX(QString str) {
//	if (!mTxtX.valid()) {
//		return;
//	}
//	QByteArray barr = str.toLocal8Bit();
//	char* bdata = barr.data();
//	mTxtX->setText(bdata);
//}
//void PointBuildBoard::SetStrY(QString str) {
//	if (!mTxtY.valid()) {
//		return;
//	}
//	QByteArray barr = str.toLocal8Bit();
//	char* bdata = barr.data();
//	mTxtY->setText(bdata);
//}
//void PointBuildBoard::SetStrZ(QString str) {
//	if (!mTxtZ.valid()) {
//		return;
//	}
//	QByteArray barr = str.toLocal8Bit();
//	char* bdata = barr.data();
//	mTxtZ->setText(bdata);
//}
///**
//判断是否被点击
//*/
//bool PointBuildBoard::IsCheckClick(osg::Vec3 pos) {
//	/*std::cout << "mBoxPos = (" << mBoxPos.x() << "," << mBoxPos.y() << "),pos = (" << pos.x() << "," << pos.y() << ")" << std::endl;
//	std::cout << "mBoxPos.x() < pos.x() " << (mBoxPos.x() < pos.x()) << "\n mBoxPos.x() + _wbox > pos.x() "<< (mBoxPos.x() + _wbox > pos.x())
//		<< "\nmBoxPos.y() < pos.y() " << (mBoxPos.y() < pos.y()) << "\nmBoxPos.y() + _hbox > pos.y()" << (mBoxPos.y() + _hbox > pos.y()) << std::endl;*/
//	if (mBoxPos.x() < pos.x() && mBoxPos.x() + _wbox > pos.x() && mBoxPos.y() < pos.y() && mBoxPos.y() + _hbox > pos.y()) {
//		return true;
//	}
//	return false;
//}
///**
//记录移动时鼠标相对box原点的偏移
//*/
//void PointBuildBoard::RecordMoveOffset(osg::Vec3 pos) {
//	mMovePosOffset = pos - mBoxPos;
//	IsAllowMove = true;
//}
///**
//移动面板位置
//*/
//void PointBuildBoard::MoveBuildBoard(osg::Vec3 pos) {
//	if (!IsAllowMove) {
//		return;
//	}
//	mBoxPos = pos - mMovePosOffset;
//}
////////////////////////////////////////////////////////////////
OSGPickHandler::OSGPickHandler(osgViewer::Viewer* viewer):osgGA::GUIEventHandler()
{
	std::cout << "OSGPickHandler" << std::endl;
	mViewer = viewer;
	/*mPickGroup = new osg::Group();
	mPickGroup->setName("PickGroup");
	mViewer->getSceneData()->asGroup()->addChild(mPickGroup);
	mOnePoint = nullptr;
	mTwoPoint = nullptr;*/
	mHUDCamera = new osg::Camera;
	mHUDCamera->setName("TMP_ULDCamera");
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
	std::cout << "getScreenResolution = " << width << "," << height << std::endl;
	//mViewer->getSceneData()->asGroup()->addChild(createHUD(mViewer));
}


OSGPickHandler::~OSGPickHandler()
{
	std::cout << "~OSGPickHandler" << std::endl;
	//mViewer->getSceneData()->asGroup()->removeChild(mPickGroup);
	mViewer->getSceneData()->asGroup()->removeChild(mHUDCamera);
}
bool OSGPickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa){
	//osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	//if (!viewer)return false;
	if (!mViewer.valid()) {
		return false;
	}
	/*if (allowPointsNum == BOXSELPOINTS) {
		return mFrameSelect->FramePick(ea);
	}*/
	else {
		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::PUSH:
		{
			if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) {
				switch (allowPointsNum)
				{
				case MeauseCloud::ONEPOINT:
				case MeauseCloud::TWOMEAUSE:
				{
					if (mOneBoard.valid()) {
						if (mOneBoard->IsCheckClick(osg::Vec3(ea.getX(), ea.getY(), 0)))
						{
							//std::cout << "allow move" << std::endl;
							mOneBoard->RecordMoveOffset(osg::Vec3(ea.getX(), ea.getY(), 0));
							return true;
						}
					}
					if (mMeasure.valid()) {
						if (mMeasure->IsCheckClick(osg::Vec3(ea.getX(), ea.getY(), 0)))
						{
							mMeasure->RecordMoveOffset(osg::Vec3(ea.getX(), ea.getY(), 0));
							return true;
						}
					}
					pick(mViewer, ea);
				}
				break;
				case BOXSELPOINTS:
					mFrameSelect.~ref_ptr();
					mFrameSelect = new FrameSelectCloud(mViewer);
					mFrameSelect->SetFirstPos(osg::Vec2(ea.getX(), ea.getY()));
					return true;
					break;
				}
			}
		}
		break;
		case osgGA::GUIEventAdapter::RELEASE:
		{
			if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) {
				if (mOneBoard.valid()) {
					mOneBoard->IsAllowMove = false;
				}
				else if (mMeasure.valid()) {
					mMeasure->IsAllowMove = false;
				}
			}
			if (mFrameSelect.valid() && mFrameSelect->IsAllowDrag) {
				mFrameSelect->DragFrame(osg::Vec2(ea.getX(), ea.getY()));
				int c1 = mFrameSelect->list.size();
				if (mFrameSelectCallBack != nullptr && mFrameSelect->list.size() > 0) {
					mFrameSelectCallBack(mFrameSelect->mSelNodeName,mFrameSelect->list);
				}
				mFrameSelect->IsAllowDrag = false;
				return true;
			}
		}
		break;
		case osgGA::GUIEventAdapter::DRAG:
		{
			if (mFrameSelect.valid() && mFrameSelect->IsAllowDrag) {
				/*if (mFrameSelect->DragFrame(osg::Vec2(ea.getX(), ea.getY()))) {
					return true;
				}*/
				mFrameSelect->DrawSelRect(osg::Vec2(ea.getX(), ea.getY()));
				return true;
			}
			else {
				if (mOneBoard.valid() && mOneBoard->IsAllowMove) {
					//std::cout << "move" << std::endl;
					mOneBoard->MoveBuildBoard(osg::Vec3(ea.getX(), ea.getY(), 0));
					return true;
				}
				else if (mMeasure.valid() && mMeasure->IsAllowMove) {
					mMeasure->MoveBuildBoard(osg::Vec3(ea.getX(), ea.getY(), 0));
					return true;
				}
			}
		}
		break;
		case osgGA::GUIEventAdapter::FRAME:
			UpdateBoard();
			//std::cout << "osgGA::GUIEventAdapter::FRAME" << std::endl;
		break;
		}
	}
	return false;
}
void OSGPickHandler::pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea){
	float x1 = ea.getX();
	float y1 = ea.getY();
	float offset = 3;
	osg::ref_ptr<osgUtil::PolytopeIntersector> intersector2 = new osgUtil::PolytopeIntersector(osgUtil::Intersector::WINDOW, x1 - offset, y1 - offset, x1 + offset, y1 + offset);
	osgUtil::IntersectionVisitor iv2(intersector2);
	view->getCamera()->accept(iv2);
	std::cout << "mouse points = ("<<ea.getX()<<","<<ea.getY()<<")" << std::endl;
	if (intersector2->containsIntersections()) {
		//std::cout << " =============PolytopeIntersector================ " << std::endl;
		auto iter = intersector2->getIntersections().begin();
		//std::vector<std::pair<unsigned int, osg::Vec3>> points;
		//int size = intersector2->getIntersections().size();
		for (; iter != intersector2->getIntersections().end(); ++iter) {
			//if ((iter->nodePath).back()->getName() == "CloudPoints")
			if(IsVerfyModelName((iter->nodePath).back()->getName().c_str()))
			{
				DrawTips(iter->primitiveIndex, iter->localIntersectionPoint);
				break;
			}
			double                          distance  = iter->distance;     ///< distance from reference plane
			double                          maxDistance = iter->maxDistance;  ///< maximum distance of intersection points from reference plane
			osg::NodePath                   nodePath = iter->nodePath;
			osg::ref_ptr<osg::Drawable>     drawable = iter->drawable;
			//osg::ref_ptr<osg::RefMatrix>    matrix;
			osg::Vec3                       localIntersectionPoint = iter->localIntersectionPoint;  ///< center of all intersection points
			unsigned int                    numIntersectionPoints = iter->numIntersectionPoints;
			//osg::Plane::Vec3_type                       intersectionPoints[MaxNumIntesectionPoints];
			unsigned int                    primitiveIndex = iter->primitiveIndex; ///< primitive index
			int a = 0;
			/*for (auto it = nodePath.begin(); it != nodePath.end(); ++it) {
				std::string name = (*it)->getName();
				std::string cname = (*it)->className();
				std::cout << name << " , " << cname << std::endl;
			}*/
			std::cout << (iter->nodePath).back()->getName() << " , " << (iter->nodePath).back()->className() << std::endl;
			std::cout << "primitiveIndex = " << primitiveIndex<<",localIntersectionPoint("<< localIntersectionPoint.x()<<","<< localIntersectionPoint.y()<<","<< localIntersectionPoint.z()<<")" << ",distance = " << distance << ",maxDistance = " << maxDistance << ",numIntersectionPoints = " << numIntersectionPoints << std::endl;
		}
		//std::cout << " ============================= " << std::endl;		
	}	
	//osg::ref_ptr<PointIntersector> intersector = new PointIntersector(osgUtil::Intersector::WINDOW, ea.getX(), ea.getY());
	////intersector->setOffset(0.5f);
	//osgUtil::IntersectionVisitor iv(intersector.get());
	//view->getCamera()->accept(iv);
	//
	//if (intersector->containsIntersections())
	//{
	//	std::cout << " ===============PointIntersector============== " << std::endl;
	//	std::vector<std::pair<unsigned int,osg::Vec3>> points;
	//	for (auto iter = intersector->getIntersections().begin(); iter != intersector->getIntersections().end(); iter++)
	//	{
	//		osg::Vec3 pos = iter->getWorldIntersectNormal();//iter->getWorldIntersectPoint();
	//		std::cout << (iter->nodePath).back()->getName() << " , " << (iter->nodePath).back()->className() << std::endl;
	//		std::cout << "primitiveIndex = " << iter->primitiveIndex << " point (" << iter->localIntersectionPoint.x() << "," << iter->localIntersectionPoint.y() << "," << iter->localIntersectionPoint.z()<<"),getWorldIntersectNormal("<< pos.x()<<","<<pos.y()<<","<<pos.z()<<")" <<std::endl;
	//		/*std::cout << "vertex indices = (" << pos.x() << "," << pos.y() << "," << pos.z() << ")" << std::endl;
	//		std::cout << "  ratio " << iter->ratio << std::endl;
	//		std::cout << "  point " << iter->localIntersectionPoint.x()<<","<< iter->localIntersectionPoint.y() << ","<< iter->localIntersectionPoint.z() << std::endl;
	//		std::cout << "  normal " << iter->localIntersectionNormal.x()<<","<<iter->localIntersectionNormal.y() << ","<<iter->localIntersectionNormal.z()  << std::endl;
	//		std::cout << "  indices " << iter->indexList.size() << std::endl;
	//		std::cout << "  primitiveIndex " << iter->primitiveIndex << std::endl;
	//		const osgUtil::LineSegmentIntersector::Intersection::IndexList& indices = iter->indexList;
	//		for (unsigned int i = 0; i < indices.size(); ++i)
	//		{
	//			std::cout << "        vertex indices [" << i << "] = " << indices[i] << std::endl;
	//		}*/
	//		//std::cout << iter->nodePath->back()->className() << std::endl;
	//		//points.push_back(std::make_pair(iter->primitiveIndex,iter->getWorldIntersectPoint()));
	//	}
	//	std::cout << " ===============PointIntersector============== " << std::endl;
	//	if (points.size() > 0) {
	//		//DrawTips(points[0].first,points[0].second);
	//		/*osg::Group* root = mViewer->getSceneData()->asGroup();
	//		int count = root->getNumChildren();
	//		for (int i = 0; i < count; ++i) {
	//			osg::Group* g = root->getChild(i)->asGroup();
	//			if (g) {
	//				std::cout << g->getName() << std::endl;
	//				if (g->getName() == "PickGroup") {
	//					for (int j = 0; j < g->getNumChildren(); ++j) {
	//						osg::Geode* geode = g->getChild(j)->asGeode();
	//						osg::Geometry* geometry = geode->getDrawable(0)->asGeometry();
	//						osg::Vec3Array* arr = dynamic_cast<osg::Vec3Array*> (geometry->getVertexArray());
	//						for (int z = 0; z < arr->size(); ++z) {
	//							std::cout << "Get Point = (" << arr->at(z).x() << "," << arr->at(z).y() << "," << arr->at(z).z() << ")" << std::endl;
	//						}
	//					}
	//				}
	//			}
	//		}*/
	//	}
	//	////osg::Vec3d worldpoint = CRealInteractionUtil::getNeartestPoint(intersector, osg::Vec2f(ea.getX(), ea.getY()), transformMatrix*vpw);
	//	//PointIntersector::Intersection result = *intersector->getIntersections().begin();
	//	///*for (auto iter = result.nodePath.begin(); iter != result.nodePath.end(); ++iter) {
	//	// std::cout << (*iter)->getName() << " , " << (*iter)->className() << std::endl;
	//	//}*/
	//	//std::cout << result.nodePath.back()->getName() << " , " << result.nodePath.back()->className() << std::endl;
	//	///*for (auto iter = result.nodePath.begin(); iter != result.nodePath.end(); ++iter) {
	//	// std::cout << (*iter)->getName() << " , " << (*iter)->className() << std::endl;
	//	//}*/
	//	///*PointIntersector::Intersection::IndexList& vil = result.indexList;
	//	//for (unsigned int i = 0; i < vil.size(); ++i)
	//	//{
	//	// std::cout << "        vertex indices [" << i << "] = " << vil[i] << std::endl;
	//	//}*/
	//}
	////osgUtil::LineSegmentIntersector::Intersections intersections;
	////std::string gdlist = "";
	////if (view->computeIntersections(ea, intersections))
	////{
	////	for (osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
	////	hitr != intersections.end();
	////		++hitr)
	////	{
	////		std::ostringstream os;
	////		if (!hitr->nodePath.empty() && !(hitr->nodePath.back()->getName().empty()))
	////		{
	////			// the geodes are identified by name.
	////			os << "Object \"" << hitr->nodePath.back()->getName() << "\"" << std::endl;
	////		}
	////		else if (hitr->drawable.valid())
	////		{
	////			os << "Object \"" << hitr->drawable->className() << "\"" << std::endl;
	////		}
	////		//os << "        local coords vertex(" << hitr->getLocalIntersectPoint() << ")" << "  normal(" << hitr->getLocalIntersectNormal() << ")" << std::endl;
	////		//os << "        world coords vertex(" << hitr->getWorldIntersectPoint() << ")" << "  normal(" << hitr->getWorldIntersectNormal() << ")" << std::endl;
	////		const osgUtil::LineSegmentIntersector::Intersection::IndexList& vil = hitr->indexList;
	////		for (unsigned int i = 0; i < vil.size(); ++i)
	////		{
	////			os << "        vertex indices [" << i << "] = " << vil[i] << std::endl;
	////		}
	////		gdlist += os.str();
	////		std::cout << gdlist << std::endl;
	////		std::cout << "===============" << std::endl;
	////	}
	////}
}
/**重置*/
void OSGPickHandler::Reset() {
	/*mViewer->getSceneData()->asGroup()->removeChild(mPickGroup);
	mPickGroup.~ref_ptr();*/
	/*mPickGroup = new osg::Group;
	mPickGroup->setName("PickGroup");
	mViewer->getSceneData()->asGroup()->addChild(mPickGroup);
	int count = 0;
	if (mOnePoint.valid()) {
		mPickGroup->removeChild(mOnePoint);
		mOnePoint.~ref_ptr();
	}
	if (mTwoPoint.valid()) {
		mPickGroup->removeChild(mTwoPoint);
		mTwoPoint.~ref_ptr();
	}*/
	if (mOneBoard.valid()) {
		mOneBoard.~ref_ptr();
	}
	if (mMeasure.valid()) {
		mMeasure.~ref_ptr();
	}
	if (mFrameSelect.valid()) {
		mFrameSelect.~ref_ptr();
	}
	//allowPointsNum = MeauseCloud::RESET;
}
/**画一个点*/
void OSGPickHandler::OnePoint() {
	Reset();
	allowPointsNum = MeauseCloud::ONEPOINT;
}
/**画二个点*/
void OSGPickHandler::TwoMeause() {
	Reset();
	allowPointsNum = MeauseCloud::TWOMEAUSE;
}
//框选点
void OSGPickHandler::FrameSelPoints() {
	Reset();
	allowPointsNum = MeauseCloud::BOXSELPOINTS;
}
///**
//创建面板
//*/
//void OSGPickHandler::CreateBoard(QString name,unsigned int primitiveIndex,osg::Vec3 pos,osg::ref_ptr<PointBuildBoard>& board) {
//	/*if (geode.valid()) {
//		mPickGroup->removeChild(geode);
//		geode.~ref_ptr();
//	}
//	geode = createSelPoint(QString("SelPoint_%1").arg(name), pos);
//	mPickGroup->addChild(geode);*/
//	if (board.valid()) {
//		board.~ref_ptr();
//	}
//	board = new PointBuildBoard(QString("BuildBoard_%1").arg(name), primitiveIndex, pos, mViewer, mHUDCamera);
//	board->SetTitle(QString("Point #%1").arg(primitiveIndex));
//	board->SetStrX(QString("%1").arg(pos.x()));
//	board->SetStrY(QString("%1").arg(pos.y()));
//	board->SetStrZ(QString("%1").arg(pos.z()));
//}
void OSGPickHandler::DrawTips(unsigned int primitiveIndex,osg::Vec3 pos) {
	switch (allowPointsNum)
	{
	case MeauseCloud::ONEPOINT:
	{
		mOneBoard.~ref_ptr();
		mOneBoard = new PointBuildBoard("BuildBoard_1", primitiveIndex, pos, mViewer, mHUDCamera);
		//CreateBoard("1", primitiveIndex, pos, mOneBoard);
		/*if (mOnePoint.valid()) {
			mPickGroup->removeChild(mOnePoint);
			mOnePoint.~ref_ptr();
		}
		QString str("选择点1");
		mOnePoint = createSelPoint(str,pos);
		mPickGroup->addChild(mOnePoint);
		if (!mOneBoard.valid()) {
			mOneBoard = new PointBuildBoard("OneBoard", pos, mViewer, mHUDCamera);
		}
		mOneBoard->ResetSelPos(pos);
		mOneBoard->SetTitle(QString("Point #%1").arg(primitiveIndex));
		mOneBoard->SetStrX(QString("%1").arg(pos.x()));
		mOneBoard->SetStrY(QString("%1").arg(pos.y()));
		mOneBoard->SetStrZ(QString("%1").arg(pos.z()));*/
	}
		break;
	case MeauseCloud::TWOMEAUSE:
	{
		if (!mOneBoard.valid()) {
			mMeasure.~ref_ptr();
			mOneBoard.~ref_ptr();
			mOneBoard = new PointBuildBoard("BuildBoard_1", primitiveIndex, pos, mViewer, mHUDCamera);
			/*QString str("选择点2");
			mOnePoint = createSelPoint(str, pos);*/
			//CreateBoard("1", primitiveIndex, pos, mOneBoard);
		}
		else {
			unsigned int oldIndex = mOneBoard->selPosIndex;
			osg::Vec3 oldPos = mOneBoard->mSelPointPos;
			mOneBoard.~ref_ptr();
			mMeasure.~ref_ptr();
			mMeasure = new MeasureBuildBoard(QString("BuildBoard_LineMeasure"), oldIndex, oldPos, primitiveIndex, pos, mViewer, mHUDCamera);
			//CreateBoard("2", primitiveIndex, pos, mTwoBoard);
			/*if (mTwoPoint.valid()) {
				mPickGroup->removeChild(mTwoPoint);
				mTwoPoint.~ref_ptr();
			}
			QString str("选择点2");
			mTwoPoint = createSelPoint(str, pos);
			if (!mTwoBoard.valid()) {
				mTwoBoard = new PointBuildBoard("TwoBoard", pos, mViewer, mHUDCamera);
			}
			mOneBoard->SetTitle(QString("Point #%1").arg(primitiveIndex));
			mTwoBoard->SetStrX(QString("%1").arg(pos.x()));
			mTwoBoard->SetStrY(QString("%1").arg(pos.y()));
			mTwoBoard->SetStrZ(QString("%1").arg(pos.z()));*/
		}
	}
		break;
	default:
		break;
	}
}
void OSGPickHandler::UpdateBoard() {
	if (mOneBoard.valid()) {
		mOneBoard->UpdateBoxPos();
	}
	if (mMeasure.valid()) {
		mMeasure->UpdateBoxPos();
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
//osg::ref_ptr<osg::Geode> OSGPickHandler::createSelPoint(QString name, osg::Vec3& pos) {
//	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
//	QByteArray barr = name.toLocal8Bit();
//	char* bdata = barr.data();
//	geode->setName(bdata);
//	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
//
//	osg::ref_ptr<osg::StateSet> stateSet = geom->getOrCreateStateSet();
//	osg::ref_ptr<osg::Point> pointSize = new osg::Point;
//	pointSize->setSize(10.0);
//	stateSet->setAttribute(pointSize, osg::StateAttribute::ON);
//	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
//	//traits->samples = 16;
//	/*osg::Multisample* pms = new osg::Multisample;
//	pms->setSampleCoverage(1, true);*/
//	stateSet->setMode(GL_POINT_SMOOTH, osg::StateAttribute::ON);
//	stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
//	//osg::PointSprite *sprite = new osg::PointSprite();
//	//stateSet->setTextureAttributeAndModes(0, sprite, osg::StateAttribute::ON);
//
//	//创建顶点数组，注意顺序逆时针
//	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
//	v->push_back(pos);
//	//设置顶点数据
//	geom->setVertexArray(v.get());
//	//创建颜色数组
//	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
//	vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
//	//设置颜色数组
//	geom->setColorArray(vc.get());
//	//设置颜色绑定方式为单个顶点
//	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
//
//	//添加图元，
//	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, v->size()));
//
//	//将图元添加至叶子节点
//	geode->addDrawable(geom.get());
//
//	//geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
//
//	//自动生成顶点法线(必须在addDrawable后)
//	osgUtil::SmoothingVisitor::smooth(*(geom.get()));
//	return geode;
//}
