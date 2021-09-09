#include "framework.h"

RotateBlockCollider::RotateBlockCollider(float px, float py) : GameObject("Collider", "", true, px, py)
{

}

RotateBlockCollider::~RotateBlockCollider()
{

}

void RotateBlockCollider::start()
{
	addBoxCollider2D(10, 10, 20, 20);
}

void RotateBlockCollider::onDrawGizmos()
{
	drawRect(getPx() + 10, getPy() + 10, getPx()+30, getPy()+30, 0, 0, 128);
}