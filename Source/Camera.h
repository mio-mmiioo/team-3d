#pragma once
#include "../Library/Object3D.h"

class Camera : public Object3D {
public:
	Camera();
	~Camera();
	void Update() override;
private:
	VECTOR3 cameraPosition_; // カメラの視点
	VECTOR3 targetPosition_; // カメラの注視点
};