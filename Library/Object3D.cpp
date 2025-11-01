#include "Object3D.h"

Object3D::Object3D()
{
	hModel_ = -1;
}

Object3D::~Object3D()
{
}

void Object3D::Update()
{
}

void Object3D::Draw()
{
	MATRIX ms = MGetScale(transform_.scale_);
	MATRIX mrx = MGetRotX(transform_.rotation_.x);
	MATRIX mry = MGetRotY(transform_.rotation_.y);
	MATRIX mrz = MGetRotZ(transform_.rotation_.z);
	MATRIX mt = MGetTranslate(transform_.position_);
	MATRIX m = ms * mrz * mrx * mry * mt;
	MV1SetMatrix(hModel_, m);
	MV1DrawModel(hModel_);
}