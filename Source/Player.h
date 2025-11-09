#pragma once
#include "../Library/Object3D.h"

class Player : public Object3D {
public:
	Player(VECTOR3 pos);
	~Player();
	void Update() override;
	void Draw() override;
private:
	float moveSpeed_;

	bool isOnGround_; // ’n–Ê‚É‚Â‚¢‚Ä‚¢‚é¨true
	float velocityY_; // y•ûŒü‚É‰Á‚í‚é—Í
	float gravity_; // d—Í
	float jumpHeight_;
	float jumpV0_;
};