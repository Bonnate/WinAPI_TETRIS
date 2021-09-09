#pragma once

#include "GameObject.h"

class RotateBlockCollider : public GameObject
{
private:

public:
	RotateBlockCollider(float px, float py);
	~RotateBlockCollider();

	void start();
	void onDrawGizmos();
};