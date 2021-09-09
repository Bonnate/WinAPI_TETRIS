#include "framework.h"

float Time::currTime = 0;
float Time::prevTime = 0;
float Time::deltaTime= 0;

void Time::init()
{
	currTime = GetTickCount() / 1000.0f;  //현재   측정된 시간
	prevTime = currTime;                 //이전에 측정된 시간
	deltaTime = 0;                         //현재 시간에서... 이전시간을 뺀 시간차
}

void Time::update()
{
	currTime = GetTickCount() / 1000.0f;  //현재 측정된 시간		
	deltaTime = currTime - prevTime;       //델타타임 구하기
	prevTime = currTime;                  //다음번 반복에서..이전시간으로..사용하기 위해서..이전시간으로 저장함
}