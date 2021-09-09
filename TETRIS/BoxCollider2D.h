#pragma once

#include"GameObject.h"

class BoxCollider2D
{
private:
	float x, y;			 //사각형의 꼭지점 좌표
	float width, height; //사각형의 가로/세로
public:
	BoxCollider2D(float x, float y, float width, float height);
	virtual ~BoxCollider2D();

	//충돌체..좌표 가져오기//
	void getBox(float& x, float& y, float& width, float& height);
	void getBoxVertex(float& x0, float& y0, float& x1, float& y1);
	int getColliderXpos();
	int getColliderYpos();

	//충돌체..이동시키기//
	void translate(float x, float y);
};