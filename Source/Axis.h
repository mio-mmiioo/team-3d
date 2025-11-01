#pragma once
#include "../Library/Object3D.h"

class Axis : public Object3D
{
public:
	Axis();
	~Axis();
	void Draw() override;
};