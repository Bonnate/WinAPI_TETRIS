#include "framework.h"

HWND Global::hWnd_ = { 0, };
int Global::HEIGHT = 0;
int Global::WIDTH = 0;

void Global::SetHWND(HWND hwnd)
{
	hWnd_ = hwnd;
}
HWND Global::GetHWND()
{
	return hWnd_;
}

void Global::SetWIDTH(int width)
{
	WIDTH = width;
}

void Global::SetHEIGHT(int height)
{
	HEIGHT = height;
}

int Global::GetWIDTH()
{
	return WIDTH;
}

int Global::GetHEIGHT()
{
	return HEIGHT;
}