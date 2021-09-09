#include "framework.h"

Sprite::Sprite(string tag, string name, bool active, float px, float py)
	  :GameObject(tag, name, active, px, py)
{
	image.width  = 0;
	image.height = 0;
	image.argb   = nullptr;
}

Sprite::~Sprite()
{
	if (image.argb != nullptr)
	{
		delete[] image.argb;
	}
}

void Sprite::setImage(const char* fileName)
{
	Bitmap::readBMP(fileName, &image);
}

void Sprite::setImage(const char* fileName, int x, int y, int width, int height)
{
	Bitmap::readBMP(fileName, x, y, width, height,  &image);
}

void Sprite::draw()
{
	//이미지 그리기//
	float px = getPx();
	float py = getPy();

	Bitmap::drawBMP(px, py, &image);
}