#pragma once
#include "../Library/GameObject.h"

class Transform {
public:
	VECTOR3 position_;
	VECTOR3 rotation_;
	VECTOR3 scale_;
	Transform() {
		position_ = VECTOR3(0, 0, 0);
		rotation_ = VECTOR3(0, 0, 0);
		scale_ = VECTOR3(1, 1, 1);
	}
};

class Object3D : public GameObject
{
public:
	Object3D();
	virtual ~Object3D();
	virtual void Update() override;
	virtual void Draw() override;
	Transform GetTransform() { return transform_; }
protected:
	int hModel_;
	Transform transform_;
};
