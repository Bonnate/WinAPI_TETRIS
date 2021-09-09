#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

#include "BMP.h"
#include "graphic.h"

void Bitmap::readBMP(const char* fileName, Image* img)
{
	//비트맵파일헤더와 비트맵인포헤더..구조체//
	BITMAPFILEHEADER  fileHeader;
	BITMAPINFOHEADER  infoHeader;

	//비트맵 파일 읽기
	FILE* stream = fopen(fileName, "rb");

	if (stream != nullptr)
	{
		//비트맵파일 헤더..구조체 읽어오기
		fread(&fileHeader, sizeof(fileHeader), 1, stream);

		//----비트맵 파일 헤더...구조체...출력하기-----//
		//printf("-------비트맵 파일 헤더 구조체------\n");

		//printf("bfType 0X%X\n", fileHeader.bfType); //파일안에서..bmp파일 확인 코드(매직코드)
		//printf("bfSize %d\n", fileHeader.bfSize); //파일 크기
		//printf("bfReserved1 %d\n", fileHeader.bfReserved1); //나중사용 변수들
		//printf("bfReserved2 %d\n", fileHeader.bfReserved2); //나중사용 변수들
		//printf("bfOffBits   %d\n", fileHeader.bfOffBits);   //비트맵데이타(픽셀데이타)의 저장위치(간격)

		//비트맵인포 헤더..구조체 읽어오기//
		fread(&infoHeader, sizeof(infoHeader), 1, stream);

		//---비트맵 인포 헤더..구조체...출력하가---//
		//printf("------비트맵 인포 헤더..구조체 ------\n");
		//printf("이미지 크기 (%d x %d)\n", infoHeader.biWidth, infoHeader.biHeight);
		//printf("비트 수준  %d\n", infoHeader.biBitCount);
		//printf("이미지 로드 배열 크기 %d\n", infoHeader.biSizeImage);

		//픽셀데이타 배열 읽어오기//
		int length = infoHeader.biSizeImage / 4;

		img->width = infoHeader.biWidth;
		img->height = infoHeader.biHeight;
		img->argb = new uint[length];            //unsigned int 는 4바이트 공간

		fread(img->argb, sizeof(uint), length, stream);

		//파일 닫기
		fclose(stream);

	}
	else {
		printf("비트맵 파일을 열수 없습니다\n");
	}
}

void Bitmap::readBMP(const char* fileName, int x, int y, int width, int height, Image* img)
{
	//비트맵파일헤더와 비트맵인포헤더..구조체//
	BITMAPFILEHEADER  fileHeader;
	BITMAPINFOHEADER  infoHeader;

	//비트맵 파일 읽기
	FILE* stream = fopen(fileName, "rb");

	if (stream != nullptr)
	{
		//비트맵파일 헤더..구조체 읽어오기
		fread(&fileHeader, sizeof(fileHeader), 1, stream);

		//비트맵인포 헤더..구조체 읽어오기//
		fread(&infoHeader, sizeof(infoHeader), 1, stream);

		//픽셀데이타 배열 읽어오기//
		int length = width * height;

		img->width  = width;  
		img->height = height;
		img->argb   = new uint[length];            //unsigned int 는 4바이트 공간

		//이미지 영역으로...fseek 하기//
		int offset = (y * infoHeader.biWidth + x) * 4 ;
		fseek(stream, offset, SEEK_CUR);

		//좌우 빈공간 ...fseek 하기//
		int gap = (infoHeader.biWidth - width)*4;

		for (int i = 0; i < height; i++)
		{
			fread(img->argb + i*width, sizeof(uint), width, stream);
			fseek(stream, gap, SEEK_CUR);
		}

		//파일 닫기
		fclose(stream);

	}
	else {
		printf("비트맵 파일을 열수 없습니다\n");
	}

}

void Bitmap::drawBMP(float px, float py, Image* img)
{
	//이미지 출력하기//
	for (int y = 0; y < img->height; y++)
	{
		for (int x = 0; x < img->width; x++)
		{
			uint pixel = img->argb[y * img->width + x];

			setPixel(px + x, py + y, pixel);
		}
	}
}
