#include "framework.h"

Input::State  Input::state[9] = { State::keyUpRep, State::keyUpRep,State::keyUpRep,State::keyUpRep, State::keyUpRep,State::keyUpRep,State::keyUpRep, State::keyUpRep, State::keyUpRep };  //0-놓고 있음, 1-한번 누름 2-누르고 있음, 3-한번놓음
int			  Input::key[9]   = { VK_LBUTTON     , VK_RBUTTON     , VK_MBUTTON    ,  VK_LEFT      , VK_RIGHT       , VK_UP         , VK_DOWN        , VK_SPACE       , 'Z' };
string		  Input::name[9]  = { "lbutton"      , "rbuttom"      , "mbutton",       "left",           "right",       "up"         ,  "down"        , "space",         "z" };

void Input::update()
{
	//키배열의...상태업데이트
	for (int i = 0; i < 9; i++)
	{
		if (state[i] == State::keyUpRep)       //State::keyUpRep-놓고 있음
		{
			if (GetAsyncKeyState(key[i]) != 0) //눌림
			{
				state[i] = State::keyDown;  // 한번 누름 상태로..전이
			}
			else //놓임
			{
				//state = 0;
			}
		}
		else if (state[i] == State::keyDown) //한번 누름 
		{
			//cout << "키를 한번 누름" << endl;

			if (GetAsyncKeyState(key[i]) != 0) //눌림
			{
				state[i] = State::keyDownRep;  //누르고 있음 상태로..전이
			}
			else //놓임
			{
				state[i] = State::keyUp;//한번놓음 상태로..전이
			}
		}
		else if (state[i] == State::keyDownRep) //누르고 있음
		{
			//cout << ".";

			if (GetAsyncKeyState(key[i]) == 0) //놓임
			{
				state[i] = State::keyUp;  //한번놓음 상태로..전이
			}
			else //눌림
			{
				//state = 2;
			}

		}
		else if (state[i] == State::keyUp) //3-한번놓음
		{
			//cout << "키를 한번 놓음" << endl;

			if (GetAsyncKeyState(key[i]) == 0) //키가 놓임
			{
				state[i] = State::keyUpRep;  //놓고 있음 상태로..전이
			}
			else //키 눌림
			{
				state[i] = State::keyUpRep; // 한번 누름 상태로..전이
			}
		}
	}
}

bool Input::getKeyDown(string keyName)
{
	//키이름 ... 인덱스 찾기//
	for (int i = 0; i < 9; i++)
	{
		if (name[i] == keyName)
		{
			if (state[i] == State::keyDown)
			{
				return true;
			}
			else {
				return false;
			}
		}
	}
	
	return false; //이름 배열에..키 이름이 없는 경우 (무조건 안눌림)
}

bool Input::getKeyUp(string keyName)
{
	//키이름 ... 인덱스 찾기//
	for (int i = 0; i < 9; i++)
	{
		if (name[i] == keyName)
		{
			if (state[i] == State::keyUp)
			{
				return true;
			}
			else {
				return false;
			}
		}
	}

	return false; //이름 배열에..키 이름이 없는 경우 (무조건 안눌림)
}

bool Input::getKey(string keyName)
{
	//키이름 ... 인덱스 찾기//
	for (int i = 0; i < 9; i++)
	{
		if (name[i] == keyName)
		{
			if (state[i] == State::keyDownRep || state[i] == State::keyDown)
			{
				return true;
			}
			else {
				return false;
			}
		}
	}

	return false; //이름 배열에..키 이름이 없는 경우 (무조건 안눌림)
}