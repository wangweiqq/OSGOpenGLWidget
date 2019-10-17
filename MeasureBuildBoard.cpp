#include "MeasureBuildBoard.h"
MeasureBuildBoard::MeasureBuildBoard(QString id, unsigned int pos1Index, osg::Vec3 pos1, unsigned int pos2Index, osg::Vec3 pos2, osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Camera> camera) :
	BuildBoard(id, viewer, camera)
{
	ResetSelPos(pos1Index, pos1, pos2Index, pos2);
	_cubrelpos.clear();
	_cubrelpos.push_back(osg::Vec3(0.0, 0.0, 0.0));
	_cubrelpos.push_back(osg::Vec3((float)_cubwidth, 0.0, 0.0));
	_cubrelpos.push_back(osg::Vec3((float)_cubwidth, (float)_cubHeight, 0.0));
	_cubrelpos.push_back(osg::Vec3(0.0, (float)_cubHeight, 0.0));
	CreateBox();
	ResetSelPos(pos1Index, pos1, pos2Index, pos2);
}

MeasureBuildBoard::~MeasureBuildBoard()
{
	if (mFGPos.valid()) {
		_viewer->getSceneData()->asGroup()->removeChild(mFGPos);
		mFGPos.~ref_ptr();
	}
	if (mSGPos.valid()) {
		_viewer->getSceneData()->asGroup()->removeChild(mSGPos);
		mSGPos.~ref_ptr();
	}
	if (mLine.valid()) {
		_viewer->getSceneData()->asGroup()->removeChild(mLine);
		mLine.~ref_ptr();
	}
}
//更新选择点云点位置
void MeasureBuildBoard::ResetSelPos(unsigned int findex, osg::Vec3 fpos, unsigned int sindex, osg::Vec3 spos) {
	mFirstPosIndex = findex;
	mFirstVecPos = fpos;
	mSecondPosIndex = sindex;
	mSecondVecPos = spos;
	if (mFGPos.valid()) {
		_viewer->getSceneData()->asGroup()->removeChild(mFGPos);
		mFGPos.~ref_ptr();
	}
	mFGPos = createSelPoint(QString("%1").arg(mFirstPosIndex), mFirstVecPos);
	_viewer->getSceneData()->asGroup()->addChild(mFGPos);
	if (mSGPos.valid()) {
		_viewer->getSceneData()->asGroup()->removeChild(mSGPos);
		mSGPos.~ref_ptr();
	}
	mSGPos = createSelPoint(QString("%1").arg(mSecondPosIndex), mSecondVecPos);
	_viewer->getSceneData()->asGroup()->addChild(mSGPos);
	if (mLine.valid()) {
		_viewer->getSceneData()->asGroup()->removeChild(mLine);
		mLine.~ref_ptr();
	}
	mLine = CreateLine("Line", osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f), { mFirstVecPos, mSecondVecPos });
	_viewer->getSceneData()->asGroup()->addChild(mLine);
	//计算点1到点2中点位置
	BuildBoard::ResetSelPos((mFirstVecPos + mSecondVecPos) / 2);

	//QString::number(xdata[i], 10, 2)
	float dx = mFirstVecPos.x() - mSecondVecPos.x();
	float dy = mFirstVecPos.y() - mSecondVecPos.y();
	float dz = mFirstVecPos.z() - mSecondVecPos.z();

	float dxy = std::sqrtf(std::powf(dx, 2) + std::powf(dy, 2));
	float dxz = std::sqrtf(std::powf(dx, 2) + std::powf(dz, 2));
	float dzy = std::sqrtf(std::powf(dz, 2) + std::powf(dy, 2));

	float distence = (mFirstVecPos - mSecondVecPos).length();//std::sqrtf(std::powf(dx, 2) + std::powf(dy, 2) + std::powf(dz, 2));

	SetTitle(QString("Distance: %1").arg(QString::number(distence, 10, 4)));

	SetStrX(QString::number(dx, 10, 4));
	SetStrY(QString::number(dy, 10, 4));
	SetStrZ(QString::number(dz, 10, 4));

	SetStrXY(QString::number(dxy, 10, 4));
	SetStrXZ(QString::number(dxz, 10, 4));
	SetStrZY(QString::number(dzy, 10, 4));
}
/**
创建Box面板
*/
void MeasureBuildBoard::CreateBox(osg::Vec4 boxColor, float width, float height) {
	BuildBoard::CreateBox(boxColor, width, height);
	if (mDeltaXIcon.valid()) {
		_geode->removeChild(mDeltaXIcon);
		mDeltaXIcon.~ref_ptr();
	}
	if (mDeltaYIcon.valid()) {
		_geode->removeChild(mDeltaYIcon);
		mDeltaYIcon.~ref_ptr();
	}
	if (mDeltaZIcon.valid()) {
		_geode->removeChild(mDeltaZIcon);
		mDeltaZIcon.~ref_ptr();
	}
	mDeltaXIcon = CreateIcon("XIcon", osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	mDeltaYIcon = CreateIcon("YIcon", osg::Vec4(0.105f, 0.553f, 0.239f, 1.0f));
	mDeltaZIcon = CreateIcon("ZIcon", osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	if (_DeltaXLabel.valid()) {
		_geode->removeChild(_DeltaXLabel);
		_DeltaXLabel.~ref_ptr();
	}
	_DeltaXLabel = CreateText("DX", "DX", _cubHeight - 2,"msyhbd.ttc");
	_DeltaXLabel->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	if (_DeltaYLabel.valid()) {
		_geode->removeChild(_DeltaYLabel);
		_DeltaYLabel.~ref_ptr();
	}
	_DeltaYLabel = CreateText("DY", "DY", _cubHeight - 2, "msyhbd.ttc");
	_DeltaYLabel->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	if (_DeltaZLabel.valid()) {
		_geode->removeChild(_DeltaZLabel);
		_DeltaZLabel.~ref_ptr();
	}
	_DeltaZLabel = CreateText("DZ", "DZ", _cubHeight - 2, "msyhbd.ttc");
	_DeltaZLabel->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));

	//标题绘制
	if (mTitle.valid()) {
		_geode->removeChild(mTitle);
		mTitle.~ref_ptr();
	}
	mTitle = CreateText("Title", "Point #253504");
	if (mTxtX.valid()) {
		_geode->removeChild(mTxtX);
		mTxtX.~ref_ptr();
	}
	mTxtX = CreateText("Title", "Point #253504");
	if (mTxtY.valid()) {
		_geode->removeChild(mTxtY);
		mTxtX.~ref_ptr();
	}
	mTxtY = CreateText("Title", "Point #253504");
	if (mTxtZ.valid()) {
		_geode->removeChild(mTxtZ);
		mTxtZ.~ref_ptr();
	}
	mTxtZ = CreateText("Title", "Point #253504");



	if (mDeltaXYIcon.valid()) {
		_geode->removeChild(mDeltaXYIcon);
		mDeltaXYIcon.~ref_ptr();
	}
	if (mDeltaXZIcon.valid()) {
		_geode->removeChild(mDeltaXZIcon);
		mDeltaXZIcon.~ref_ptr();
	}
	if (mDeltaZYIcon.valid()) {
		_geode->removeChild(mDeltaZYIcon);
		mDeltaZYIcon.~ref_ptr();
	}
	mDeltaXYIcon = CreateIcon("XYIcon", osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	mDeltaXZIcon = CreateIcon("XZIcon", osg::Vec4(0.105f, 0.553f, 0.239f, 1.0f));
	mDeltaZYIcon = CreateIcon("ZYIcon", osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));

	if (_DeltaXYLabel.valid()) {
		_geode->removeChild(_DeltaXYLabel);
		_DeltaXYLabel.~ref_ptr();
	}
	_DeltaXYLabel = CreateText("DXY", "DXY", _cubHeight - 2, "msyhbd.ttc");
	_DeltaXYLabel->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	if (_DeltaXZLabel.valid()) {
		_geode->removeChild(_DeltaXZLabel);
		_DeltaXZLabel.~ref_ptr();
	}
	_DeltaXZLabel = CreateText("DXZ", "DXZ", _cubHeight - 2, "msyhbd.ttc");
	_DeltaXZLabel->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	if (_DeltaZYLabel.valid()) {
		_geode->removeChild(_DeltaZYLabel);
		_DeltaZYLabel.~ref_ptr();
	}
	_DeltaZYLabel = CreateText("DZY", "DZY", _cubHeight - 2, "msyhbd.ttc");
	_DeltaZYLabel->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));



	if (mTxtXY.valid()) {
		_geode->removeChild(mTxtXY);
		mTxtXY.~ref_ptr();
	}
	mTxtXY = CreateText("Title", "Point #253504");
	if (mTxtXZ.valid()) {
		_geode->removeChild(mTxtXZ);
		mTxtXZ.~ref_ptr();
	}
	mTxtXZ = CreateText("Title", "Point #253504");
	if (mTxtZY.valid()) {
		_geode->removeChild(mTxtZY);
		mTxtZY.~ref_ptr();
	}
	mTxtZY = CreateText("Title", "Point #253504");

	UpdateBoxPos();

	mDeltaXIcon->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	mDeltaYIcon->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	mDeltaZIcon->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	mDeltaXYIcon->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	mDeltaXZIcon->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	mDeltaZYIcon->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
}
/**
更新Box的位置
*/
void MeasureBuildBoard::UpdateBoxPos() {
	BuildBoard::UpdateBoxPos();

	std::vector<osg::Vec3> vecBoxPos = { _boxrelpos[0] + osg::Vec3(mBoxPos.x(),mBoxPos.y(),0.0) ,
		_boxrelpos[1] + osg::Vec3(mBoxPos.x(),mBoxPos.y(),0.0),
		_boxrelpos[2] + osg::Vec3(mBoxPos.x(),mBoxPos.y(),0.0),
		_boxrelpos[3] + osg::Vec3(mBoxPos.x(),mBoxPos.y(),0.0)
	};

	//标题位置
	osg::Vec3 rowpos1 = vecBoxPos[3] - osg::Vec3(-1.0f, 1.0f, 0.0f)*_padding;
	float chheight = 0;
	if (mTitle.valid()) {
		chheight = mTitle->getCharacterHeight();
		rowpos1 -= osg::Y_AXIS*chheight;
		mTitle->setPosition(rowpos1);
	}

	//X轴图标位置
	osg::Vec3 rowpos2 = rowpos1 - osg::Y_AXIS* _cubHeight - osg::Y_AXIS* _padding;
	//Y轴图标位置
	osg::Vec3 rowpos3 = rowpos2 - osg::Y_AXIS*_cubHeight;
	//Z轴图标位置
	osg::Vec3 rowpos4 = rowpos3 - osg::Y_AXIS*_cubHeight;
	//X文本位置
	osg::Vec3 rowtxt2 = rowpos2 + osg::X_AXIS*(_cubwidth + _padding) + osg::Y_AXIS*(((float)_cubHeight - chheight));
	//Y文本位置
	osg::Vec3 rowtxt3 = rowpos3 + osg::X_AXIS*(_cubwidth + _padding) + osg::Y_AXIS*(((float)_cubHeight - chheight));
	//Z文本位置
	osg::Vec3 rowtxt4 = rowpos4 + osg::X_AXIS*(_cubwidth + _padding) + osg::Y_AXIS*(((float)_cubHeight - chheight));

	//X轴图标位置
	osg::Vec3 rowpos5 = rowpos1 + osg::X_AXIS*_wbox/2 - osg::Y_AXIS* _cubHeight - osg::Y_AXIS* _padding;
	//Y轴图标位置
	osg::Vec3 rowpos6 = rowpos2 + osg::X_AXIS*_wbox / 2 - osg::Y_AXIS*_cubHeight;
	//Z轴图标位置
	osg::Vec3 rowpos7 = rowpos3 + osg::X_AXIS*_wbox / 2 - osg::Y_AXIS*_cubHeight;
	//X文本位置
	osg::Vec3 rowtxt5 = rowpos2 + osg::X_AXIS*(_wbox / 2 + _cubwidth + _padding) + osg::Y_AXIS*(((float)_cubHeight - chheight));
	//Y文本位置
	osg::Vec3 rowtxt6 = rowpos3 + osg::X_AXIS*(_wbox / 2 + _cubwidth + _padding) + osg::Y_AXIS*(((float)_cubHeight - chheight));
	//Z文本位置
	osg::Vec3 rowtxt7 = rowpos4 + osg::X_AXIS*(_wbox / 2 + _cubwidth + _padding) + osg::Y_AXIS*(((float)_cubHeight - chheight));

	if (mDeltaXIcon.valid()) {
		osg::Vec3Array *vericon1 = new osg::Vec3Array;
		for (int i = 0; i < _cubrelpos.size(); ++i) {
			vericon1->push_back(_cubrelpos[i] + rowpos2);
		}
		mDeltaXIcon->setVertexArray(vericon1);
	}
	if (_DeltaXLabel.valid()) {
		_DeltaXLabel->setPosition(rowpos2 + osg::X_AXIS * 5 + osg::Y_AXIS * 2);
	}
	if (mDeltaYIcon.valid()) {
		osg::Vec3Array *vericon2 = new osg::Vec3Array;
		for (int i = 0; i < _cubrelpos.size(); ++i) {
			vericon2->push_back(_cubrelpos[i] + rowpos3);
		}
		mDeltaYIcon->setVertexArray(vericon2);
	}
	if (_DeltaYLabel.valid()) {
		_DeltaYLabel->setPosition(rowpos3 + osg::X_AXIS * 5 + osg::Y_AXIS * 2);
	}
	if (mDeltaZIcon.valid()) {
		osg::Vec3Array *vericon3 = new osg::Vec3Array;
		for (int i = 0; i < _cubrelpos.size(); ++i) {
			vericon3->push_back(_cubrelpos[i] + rowpos4);
		}
		mDeltaZIcon->setVertexArray(vericon3);
	}
	if (_DeltaZLabel.valid()) {
		_DeltaZLabel->setPosition(rowpos4 + osg::X_AXIS * 5 + osg::Y_AXIS * 2);
	}
	if (mTxtX.valid()) {
		mTxtX->setPosition(rowtxt2);
		chheight = mTxtX->getCharacterHeight();
	}
	if (mTxtY.valid()) {
		mTxtY->setPosition(rowtxt3);
		chheight = mTxtY->getCharacterHeight();
	}
	if (mTxtZ.valid()) {
		mTxtZ->setPosition(rowtxt4);
		chheight = mTxtZ->getCharacterHeight();
	}


	if (mDeltaXYIcon.valid()) {
		osg::Vec3Array *vericon1 = new osg::Vec3Array;
		for (int i = 0; i < _cubrelpos.size(); ++i) {
			vericon1->push_back(_cubrelpos[i] + rowpos5);
		}
		mDeltaXYIcon->setVertexArray(vericon1);
	}
	if (_DeltaXYLabel.valid()) {
		_DeltaXYLabel->setPosition(rowpos5 + osg::X_AXIS * 2 + osg::Y_AXIS * 2);
	}
	if (mDeltaXZIcon.valid()) {
		osg::Vec3Array *vericon2 = new osg::Vec3Array;
		for (int i = 0; i < _cubrelpos.size(); ++i) {
			vericon2->push_back(_cubrelpos[i] + rowpos6);
		}
		mDeltaXZIcon->setVertexArray(vericon2);
	}
	if (_DeltaXZLabel.valid()) {
		_DeltaXZLabel->setPosition(rowpos6 + osg::X_AXIS * 2 + osg::Y_AXIS * 2);
	}
	if (mDeltaZYIcon.valid()) {
		osg::Vec3Array *vericon3 = new osg::Vec3Array;
		for (int i = 0; i < _cubrelpos.size(); ++i) {
			vericon3->push_back(_cubrelpos[i] + rowpos7);
		}
		mDeltaZYIcon->setVertexArray(vericon3);
	}
	if (_DeltaZYLabel.valid()) {
		_DeltaZYLabel->setPosition(rowpos7 + osg::X_AXIS * 2 + osg::Y_AXIS * 2);
	}
	if (mTxtXY.valid()) {
		mTxtXY->setPosition(rowtxt5);
	}
	if (mTxtXZ.valid()) {
		mTxtXZ->setPosition(rowtxt6);
	}
	if (mTxtZY.valid()) {
		mTxtZY->setPosition(rowtxt7);
	}
}
void MeasureBuildBoard::SetTitle(QString str) {
	if (!mTitle.valid()) {
		return;
	}
	QByteArray barr = str.toLocal8Bit();
	char* bdata = barr.data();
	mTitle->setText(bdata);
}
void MeasureBuildBoard::SetStrX(QString str) {
	if (!mTxtX.valid()) {
		return;
	}
	QByteArray barr = str.toLocal8Bit();
	char* bdata = barr.data();
	mTxtX->setText(bdata);
}
void MeasureBuildBoard::SetStrY(QString str) {
	if (!mTxtY.valid()) {
		return;
	}
	QByteArray barr = str.toLocal8Bit();
	char* bdata = barr.data();
	mTxtY->setText(bdata);
}
void MeasureBuildBoard::SetStrZ(QString str) {
	if (!mTxtZ.valid()) {
		return;
	}
	QByteArray barr = str.toLocal8Bit();
	char* bdata = barr.data();
	mTxtZ->setText(bdata);
}
void MeasureBuildBoard::SetStrXY(QString str) {
	if (!mTxtXY.valid()) {
		return;
	}
	QByteArray barr = str.toLocal8Bit();
	char* bdata = barr.data();
	mTxtXY->setText(bdata);
}
void MeasureBuildBoard::SetStrXZ(QString str) {
	if (!mTxtXZ.valid()) {
		return;
	}
	QByteArray barr = str.toLocal8Bit();
	char* bdata = barr.data();
	mTxtXZ->setText(bdata);
}
void MeasureBuildBoard::SetStrZY(QString str) {
	if (!mTxtZY.valid()) {
		return;
	}
	QByteArray barr = str.toLocal8Bit();
	char* bdata = barr.data();
	mTxtZY->setText(bdata);
}