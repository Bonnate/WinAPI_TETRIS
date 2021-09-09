#pragma once

typedef unsigned int uint;

struct Image
{
	//로드이미지 변수들
	int width;	 //이미지 가로 
	int height;	 //이미지 세로
	uint* argb;  //이미지 픽셀데이타 저장(동적할당)배열
};

class Bitmap
{
private:
public:
	static void readBMP(const char* fileName, Image* img);
	static void readBMP(const char* fileName, int x, int y, int width, int height,  Image* img);

	static void drawBMP(float px, float py, Image* img);
};