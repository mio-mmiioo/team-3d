#include "Camera.h"

namespace {
	static float DISTANCE = 700.0f;		// ステージからの距離
	static float LOOK_HIEGHT = 180.0f;	// 視点の高さ
};

Camera::Camera()
{
	cameraPosition_ = VECTOR3(640.0f, 384.0f, -DISTANCE);
	targetPosition_ = VECTOR3(640.0f, 384.0f, 0);
	SetCameraPositionAndTarget_UpVecY(cameraPosition_, targetPosition_);
}

Camera::~Camera()
{
}

void Camera::Update()
{
}
