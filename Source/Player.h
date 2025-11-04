#pragma once
#include "../Library/Object3D.h"

class Player : public Object3D {
public:
	Player(VECTOR3 pos);
	~Player();
	void Update() override;
	void Draw() override;
private:
};