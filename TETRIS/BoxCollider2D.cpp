#include "framework.h"

BoxCollider2D::BoxCollider2D(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width  = width;
	this->height = height;
}

BoxCollider2D::~BoxCollider2D()
{}

void BoxCollider2D::getBox(float& x, float& y, float& width, float& height)
{
	x = this->x;
	y = this->y;

	width  = this->width;
	height = this->height;
}

void BoxCollider2D::translate(float x, float y)
{
	this->x = this->x + x;
	this->y = this->y + y;
}

void BoxCollider2D::getBoxVertex(float& x0, float& y0, float& x1, float& y1)
{
	x0 = x;
	y0 = y;

	x1 = x + width;
	y1 = y + height;
}

int BoxCollider2D::getColliderXpos()
{
	return this->x;
}

int BoxCollider2D::getColliderYpos()
{
	return this->y;
}