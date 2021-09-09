#pragma once

#include <string>

using namespace std;

class Input
{
	enum class State { keyUpRep = 0, keyDown = 1, keyDownRep = 2, keyUp = 3 }; //0-놓고 있음, 1-한번 누름 2-누르고 있음, 3-한번놓음

private:
	static State state[9];
	static int key[9];
	static string name[9];

public:

	static void update();  //키상태 업데이트

	//키검사 함수
	static bool getKeyDown(string keyName);
	static bool getKeyUp  (string keyName);
	static bool getKey    (string keyName);
};