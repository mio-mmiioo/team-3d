#include "Camera.h"

namespace {
	static float DISTANCE = 500.0f;		// ƒLƒƒƒ‰‚©‚ç‚Ì‹——£
	static float LOOK_HIEGHT = 180.0f;	// ‹“_‚Ì‚‚³
};

Camera::Camera()
{
	cameraPosition_ = VECTOR3(0, 0, -DISTANCE);
	targetPosition_ = VECTOR3(0, 0, 0);
	SetCameraPositionAndTarget_UpVecY(cameraPosition_, targetPosition_);
}

Camera::~Camera()
{
}

void Camera::Update()
{
}
