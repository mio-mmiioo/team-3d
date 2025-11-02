#include "Camera.h"
#include "Screen.h"

namespace {
	const float DISTANCE = 700.0f;		// ステージからの距離
};

Camera::Camera()
{
	cameraPosition_ = VECTOR3(Screen::WIDTH / 2.0f, Screen::HEIGHT / 2.0f, -DISTANCE);
	targetPosition_ = VECTOR3(Screen::WIDTH / 2.0f, Screen::HEIGHT / 2.0f, 0);
	SetCameraPositionAndTarget_UpVecY(cameraPosition_, targetPosition_);
}

Camera::~Camera()
{
}

void Camera::Update()
{
}
