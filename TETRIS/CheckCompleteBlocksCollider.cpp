#include "framework.h"


CheckCompleteBlocksCollider::CheckCompleteBlocksCollider(float px, float py) :GameObject("", "CheckCompleteBlocks", true, px, py)
{

}

CheckCompleteBlocksCollider::~CheckCompleteBlocksCollider()
{

}


void CheckCompleteBlocksCollider::start()
{
	for (int i = 0; i < Global::GetHEIGHT() / 40; ++i)
	{
		addBoxCollider2D(10, 10 + (40 * i), Global::GetWIDTH() - 20, 20);
	}
	
}

void CheckCompleteBlocksCollider::onDrawGizmos()
{
	for (int i = 0; i < Global::GetHEIGHT() / 40; ++i)
	{
		drawLine(getPx() + 10, (getPy() + 20) + (40 * i), Global::GetWIDTH() - 10, (getPy() + 20) + (40 * i), 0, 255, 0);
	}
	
}