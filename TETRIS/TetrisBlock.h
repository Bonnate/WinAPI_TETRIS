#pragma once

#include "Animation.h"

class TetrisBlock : public Animation
{
private:
	

public:
	TetrisBlock(float px, float py);
	~TetrisBlock();

	void start();
	void update();
};