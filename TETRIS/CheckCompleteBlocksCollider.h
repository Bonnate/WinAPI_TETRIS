#pragma once

#include "GameObject.h"

class CheckCompleteBlocksCollider : public GameObject
{
private:

public:
	CheckCompleteBlocksCollider(float px, float py);
	~CheckCompleteBlocksCollider();

	void start();
	void onDrawGizmos();
};