#include "framework.h"

TetrisBlock::TetrisBlock(float px, float py) : Animation("", "", true, px, py)
{

}

TetrisBlock::~TetrisBlock()
{

}

void TetrisBlock::start()
{
	addImage("Asset/블록_그린.bmp", 0, 0, 40, 40, 0);
	addImage("Asset/블록_노랑.bmp", 0, 0, 40, 40, 0);
	addImage("Asset/블록_노랑2.bmp", 0, 0, 40, 40, 0);
	addImage("Asset/블록_라임.bmp", 0, 0, 40, 40, 0);
	addImage("Asset/블록_보라.bmp", 0, 0, 40, 40, 0);
	addImage("Asset/블록_자주.bmp", 0, 0, 40, 40, 0);
	addImage("Asset/블록_진한노랑.bmp", 0, 0, 40, 40, 0);
	addImage("Asset/블록_핑크2.bmp", 0, 0, 40, 40, 0);

	addBoxCollider2D(2, -1, 36, 2);
	addBoxCollider2D(2, 1, 36, 40);
	addBoxCollider2D(-1, 2, 2, 36);
	addBoxCollider2D(39, 2, 2, 36);

	setImageDelay(1.0f);
}
void TetrisBlock::update()
{

}