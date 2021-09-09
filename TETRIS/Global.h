#pragma once

#include <Windows.h>

class Global
{
private:
	static HWND hWnd_;
	static int WIDTH;
	static int HEIGHT;

public:
	static void SetHWND(HWND hwnd);
	static HWND GetHWND();

	static void SetWIDTH(int width);
	static void SetHEIGHT(int height);
	
	static int GetWIDTH();
	static int GetHEIGHT();
};