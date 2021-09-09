#pragma once

#include "Animation.h"

class BackGround : public Animation
{
private:

public:
	BackGround(int px, int py);
	~BackGround();

	void start();
};