#include "framework.h"

BackGround::BackGround(int px, int py) : Animation("", "", true, px, py)
{

}
BackGround::~BackGround()
{

}

void BackGround::start()
{
	addImage("Asset/게임배경/400_800.bmp", 0, 0, 400, 800, 0);
}
