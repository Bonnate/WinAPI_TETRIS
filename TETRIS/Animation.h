#pragma once

#include "GameObject.h"
#include "BMP.h"

#include <vector>
using namespace std;

class Animation : public GameObject
{
private:
	//이미지 저장 배열//
	vector<Image> image[10];

	int index;  //애니메이션 이미지 인덱스
	int id;     //애니메이션 클립(clip) 아이디

	//이미지..타이머(애니메이션 속도 조절)//
	float imageTimer;
	float imageDelay;

public:
	Animation(string tag, string name, bool active, float px, float py);
	~Animation();

	void draw();

	void addImage(const char* fileName, int x, int y, int width, int height, int clipId);
	void addImage(const char* fileName, int clipId);
	void setClipId(int clipId);
	void setImageDelay(float delay);

	//애니메이션 이벤트 함수 추가하기//
	virtual void onAnimationEnd();
};