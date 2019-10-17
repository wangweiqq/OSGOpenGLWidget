#include "MeasureBuildBoard.h"
MeasureBuildBoard::MeasureBuildBoard(QString id, unsigned int pos1Index, osg::Vec3 pos1, unsigned int pos2Index, osg::Vec3 pos2, osg::ref_ptr<osgViewer::Viewer> viewer, osg::ref_ptr<osg::Camera> camera) :
	BuildBoard(id, viewer, camera)
{

	_cubrelpos.clear();
	_cubrelpos.push_back(osg::Vec3(0.0, 0.0, 0.0));
	_cubrelpos.push_back(osg::Vec3(_cubwidth, 0.0, 0.0));
	_cubrelpos.push_back(osg::Vec3(_cubwidth, _cubwidth, 0.0));
	_cubrelpos.push_back(osg::Vec3(0.0, _cubwidth, 0.0));
	CreateBox();
}

MeasureBuildBoard::~MeasureBuildBoard()
{
}
/**
创建Box面板
*/
void MeasureBuildBoard::CreateBox(osg::Vec4 boxColor, float width, float height) {
	BuildBoard::CreateBox(boxColor, width, height);
	if (mXIcon.valid()) {
		_geode->removeChild(mXIcon);
		mXIcon.~ref_ptr();
	}
	if (mYIcon.valid()) {
		_geode->removeChild(mYIcon);
		mYIcon.~ref_ptr();
	}
	if (mZIcon.valid()) {
		_geode->removeChild(mZIcon);
		mZIcon.~ref_ptr();
	}
	mXIcon = CreateIcon("XIcon", osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	mYIcon = CreateIcon("YIcon", osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	mZIcon = CreateIcon("ZIcon", osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	if (_XLabel.valid()) {
		_geode->removeChild(_XLabel);
		_XLabel.~ref_ptr();
	}
	_XLabel = CreateText("X", "X", _cubwidth - 2);
	_XLabel->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	if (_YLabel.valid()) {
		_geode->removeChild(_XLabel);
		_YLabel.~ref_ptr();
	}
	_YLabel = CreateText("Y", "Y", _cubwidth - 2);
	_YLabel->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	if (_ZLabel.valid()) {
		_geode->removeChild(_XLabel);
		_ZLabel.~ref_ptr();
	}
	_ZLabel = CreateText("Z", "Z", _cubwidth - 2);
	_ZLabel->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));

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

	UpdateBoxPos();

	mXIcon->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	mYIcon->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	mZIcon->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
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
	osg::Vec3 rowpos2 = rowpos1 - osg::Y_AXIS* chheight * 2 - osg::Y_AXIS* _padding;
	//Y轴图标位置
	osg::Vec3 rowpos3 = rowpos2 - osg::Y_AXIS*_cubwidth;
	//Z轴图标位置
	osg::Vec3 rowpos4 = rowpos3 - osg::Y_AXIS*_cubwidth;
	//X文本位置
	osg::Vec3 rowtxt2 = rowpos2 + osg::X_AXIS*(_cubwidth + _padding) + osg::Y_AXIS*(((float)_cubwidth - chheight));
	//Y文本位置
	osg::Vec3 rowtxt3 = rowpos3 + osg::X_AXIS*(_cubwidth + _padding) + osg::Y_AXIS*(((float)_cubwidth - chheight));
	//Z文本位置
	osg::Vec3 rowtxt4 = rowpos4 + osg::X_AXIS*(_cubwidth + _padding) + osg::Y_AXIS*(((float)_cubwidth - chheight));

	if (mXIcon.valid()) {
		osg::Vec3Array *vericon1 = new osg::Vec3Array;
		for (int i = 0; i < _cubrelpos.size(); ++i) {
			vericon1->push_back(_cubrelpos[i] + rowpos2);
		}
		mXIcon->setVertexArray(vericon1);
	}
	if (_XLabel.valid()) {
		_XLabel->setPosition(rowpos2 + osg::X_AXIS * 3 + osg::Y_AXIS * 2);
	}
	if (mYIcon.valid()) {
		osg::Vec3Array *vericon2 = new osg::Vec3Array;
		for (int i = 0; i < _cubrelpos.size(); ++i) {
			vericon2->push_back(_cubrelpos[i] + rowpos3);
		}
		mYIcon->setVertexArray(vericon2);
	}
	if (_YLabel.valid()) {
		_YLabel->setPosition(rowpos3 + osg::X_AXIS * 3 + osg::Y_AXIS * 2);
	}
	if (mZIcon.valid()) {
		osg::Vec3Array *vericon3 = new osg::Vec3Array;
		for (int i = 0; i < _cubrelpos.size(); ++i) {
			vericon3->push_back(_cubrelpos[i] + rowpos4);
		}
		mZIcon->setVertexArray(vericon3);
	}
	if (_ZLabel.valid()) {
		_ZLabel->setPosition(rowpos4 + osg::X_AXIS * 3 + osg::Y_AXIS * 2);
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