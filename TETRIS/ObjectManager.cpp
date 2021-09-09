#include "framework.h"



vector<GameObject*> ObjectManager::gameObject[MAX_LAYER];
bool ObjectManager::isLeftCollider = TRUE;
bool ObjectManager::isRightCollider = TRUE;
bool ObjectManager::isDownCollider = TRUE;
int  ObjectManager::deadLinesAmount = 0;

void ObjectManager::instantiate(GameObject* o, int layer)
{
	gameObject[layer].push_back(o);
	o->start();
}

void ObjectManager::destroy(GameObject* o)
{
	//충돌검사쌍의 사용이 끝난후..삭제할 수 있도록...삭제...정보 표시를함//
	o->setDead(true);
}

void ObjectManager::update()
{
	//객체들 업데이트(이동, 발사)//
	for (int layer = 0; layer < MAX_LAYER; layer++)
	{
		for (int i = 0; i < gameObject[layer].size(); i++)
		{
			gameObject[layer][i]->update();
		}
	}
}

void ObjectManager::clearDead()
{
	//충돌 검사 이후에...삭제 표시 오브젝트를 제거하기//
	for (int layer = 0; layer < MAX_LAYER; layer++)
	{
		for (int i = 0; i < gameObject[layer].size(); i++)
		{
			if (gameObject[layer][i]->getDead() == true)
			{
				delete gameObject[layer][i];							//객체 삭제
				gameObject[layer].erase(gameObject[layer].begin() + i); //stl vector의 주소 저장 공간 삭제
				
				i--;  //삭제 대상인덱스를 건너뀌는것을 방지하기 위해서..인덱스를 감소시킴


			}
		}
	}

	while (deadLinesAmount >= 1)
	{
		TetrisBlockController::SetTotalSpawnedBlocksAmount(TetrisBlockController::GetTotalSpawnedBlocksAmount() - (Global::GetWIDTH() / 40));

		--deadLinesAmount;
	}

}

void ObjectManager::checkCollision()
{
	TetrisBlockController::SetisCanRollingBlock(TRUE);

	isDownCollider = isRightCollider = isLeftCollider = TRUE;

	checkBorderReached();

	if (gameObject[1].size() <= 4) return;

	for (int i = gameObject[1].size() - 4; i < gameObject[1].size(); i++)
	{
		for (int j = 0; j < gameObject[1].size() - 4; j++)
		{
			GameObject* objI = gameObject[1][i];
			GameObject* objJ = gameObject[1][j];

			checkObjectCollision(objI, objJ, objJ->getPx(), objJ->getPy());

			GameObject* RotobjI = gameObject[2][i];
			GameObject* RotobjJ = gameObject[1][j];

			checkObjectRotateCollision(RotobjI, RotobjJ);
		}
	}	
}

void ObjectManager::checkObjectCollision(GameObject* objI, GameObject* objJ, int targetxPos, int targetyPos)
{
	vector<BoxCollider2D*> boxI = objI->getBoxCollider2D();
	vector<BoxCollider2D*> boxJ = objJ->getBoxCollider2D();

	for (int ii = 0; ii < boxI.size(); ii++)
	{
		for (int jj = 0; jj < boxJ.size(); jj++)
		{
			//박스좌표 구하기
			float x0I, y0I, x1I, y1I; //boxI 충돌체의 사각형 꼭지점 좌표
			float x0J, y0J, x1J, y1J; //boxJ 충돌체의 사각형 꼭지점 좌표

			boxI[ii]->getBoxVertex(x0I, y0I, x1I, y1I);
			boxJ[jj]->getBoxVertex(x0J, y0J, x1J, y1J);

			if (!(x1J < x0I || x1I < x0J || y1I < y0J || y1J < y0I)) //if (x1J >= x0I && x1I >= x0J && y1I >= y0J && y1J >= y0I)					
			{


				//충돌 이벤트..알려주기//
				objI->onTriggerStay(objJ);  //objI에게..objJ하고 충돌중임을 알림
				objJ->onTriggerStay(objI);  //objJ에게..objI하고 충돌줌임을 알림


				int CheckColliderXPos = x0J - targetxPos;
				int CheckColliderYPos = y0J - targetyPos;

				if (CheckColliderXPos == 2 && CheckColliderYPos == -1)
				{
					isDownCollider = FALSE;
				}


				if (CheckColliderXPos == -1)
				{
					isRightCollider = FALSE;
				}


				if (CheckColliderXPos == 39)
				{
					isLeftCollider = FALSE;
				}

			}
		}
	}
}

void ObjectManager::checkBlocksComplete()
{
	printf("TOTAL: %d\nOBJ1: %d\nOBJ2: %d\n", TetrisBlockController::GetTotalSpawnedBlocksAmount(), gameObject[1].size(), gameObject[2].size());

	if (gameObject[1].size() < 0) return;

	vector<BoxCollider2D*> boxI = gameObject[3][0]->getBoxCollider2D();

	for (int i = 0; i < Global::GetHEIGHT() / 40; ++i)
	{
		int CompleteStacksPerLine = 0;

		for (int j = 0; j < gameObject[1].size() - TetrisBlockController::GetControllingBlocksAmount(); ++j)
		{
			vector<BoxCollider2D*> boxJ = gameObject[1][j]->getBoxCollider2D();

			for (int k = 0; k < boxJ.size(); ++k)
			{
				//박스좌표 구하기
				float x0I, y0I, x1I, y1I; //boxI 충돌체의 사각형 꼭지점 좌표
				float x0J, y0J, x1J, y1J; //boxJ 충돌체의 사각형 꼭지점 좌표

				boxI[i]->getBoxVertex(x0I, y0I, x1I, y1I);
				boxJ[k]->getBoxVertex(x0J, y0J, x1J, y1J);

				if (!(x1J < x0I || x1I < x0J || y1I < y0J || y1J < y0I)) //if (x1J >= x0I && x1I >= x0J && y1I >= y0J && y1J >= y0I)					
				{
					++CompleteStacksPerLine;
					break;
				}
			}
		}

		if (CompleteStacksPerLine >= Global::GetWIDTH() / 40)
		{	
			++deadLinesAmount;

			for (int j = 0; j < gameObject[1].size() - TetrisBlockController::GetControllingBlocksAmount(); ++j)
			{
				vector<BoxCollider2D*> boxJ = gameObject[1][j]->getBoxCollider2D();

				for (int k = 0; k < boxJ.size(); ++k)
				{
					//박스좌표 구하기
					float x0I, y0I, x1I, y1I; //boxI 충돌체의 사각형 꼭지점 좌표
					float x0J, y0J, x1J, y1J; //boxJ 충돌체의 사각형 꼭지점 좌표

					boxI[i]->getBoxVertex(x0I, y0I, x1I, y1I);
					boxJ[k]->getBoxVertex(x0J, y0J, x1J, y1J);

					if (!(x1J < x0I || x1I < x0J || y1I < y0J || y1J < y0I)) //if (x1J >= x0I && x1I >= x0J && y1I >= y0J && y1J >= y0I)					
					{
						destroy(gameObject[1][j]);
						destroy(gameObject[2][j]);

						
						break;
					}
				}
			}
			for (int h = i - 1; h >= 0; --h)
			{
				printf("%d", h);
					
				for (int z = 0; z < gameObject[1].size() - TetrisBlockController::GetControllingBlocksAmount(); ++z)
				{
					vector<BoxCollider2D*> boxJ = gameObject[1][z]->getBoxCollider2D();

					for (int k = 0; k < boxJ.size(); ++k)
					{
						//박스좌표 구하기
						float x0I, y0I, x1I, y1I; //boxI 충돌체의 사각형 꼭지점 좌표
						float x0J, y0J, x1J, y1J; //boxJ 충돌체의 사각형 꼭지점 좌표

						boxI[h]->getBoxVertex(x0I, y0I, x1I, y1I);
						boxJ[k]->getBoxVertex(x0J, y0J, x1J, y1J);

						if (!(x1J < x0I || x1I < x0J || y1I < y0J || y1J < y0I)) //if (x1J >= x0I && x1I >= x0J && y1I >= y0J && y1J >= y0I)
						{
							gameObject[1][z]->translate(0, 40);
							gameObject[2][z]->translate(0, 40);

							break;
						}
					}
				}
			}
		}
	}
}

void ObjectManager::checkObjectRotateCollision(GameObject* objI, GameObject* objJ)
{
	vector<BoxCollider2D*> boxI = objI->getBoxCollider2D();
	vector<BoxCollider2D*> boxJ = objJ->getBoxCollider2D();

	for (int ii = 0; ii < boxI.size(); ii++)
	{
		for (int jj = 0; jj < boxJ.size(); jj++)
		{
			//박스좌표 구하기
			float x0I, y0I, x1I, y1I; //boxI 충돌체의 사각형 꼭지점 좌표
			float x0J, y0J, x1J, y1J; //boxJ 충돌체의 사각형 꼭지점 좌표

			boxI[ii]->getBoxVertex(x0I, y0I, x1I, y1I);
			boxJ[jj]->getBoxVertex(x0J, y0J, x1J, y1J);

			if (!(x1J < x0I || x1I < x0J || y1I < y0J || y1J < y0I)) //if (x1J >= x0I && x1I >= x0J && y1I >= y0J && y1J >= y0I)					
			{
				//printf("Cannot Rolling!\n");
				TetrisBlockController::SetisCanRollingBlock(FALSE);
			}
		}
	}
}

void ObjectManager::draw()
{
	for (int layer = 0; layer < MAX_LAYER ; layer++)
	{
		for (int i = 0; i < gameObject[layer].size(); i++)
		{
			if (gameObject[layer][i]->getActive() == true)
			{
				gameObject[layer][i]->draw();
				//gameObject[layer][i]->onDrawGizmos();
			}
		}
	}
}

void ObjectManager::clear()
{
	for (int layer = 0; layer < MAX_LAYER ; layer++)
	{
		for (int i = 0; i < gameObject[layer].size(); i++)
		{
			delete gameObject[layer][i];
		}

		gameObject[layer].clear();
	}
}

void ObjectManager::controlBlocks()
{
	if (TetrisBlockController::GetTotalSpawnedBlocksAmount() <= 0) return;

	static float fallTimer = .0f;
	static float fallDelay = 0.05f;

	static float DownSetTimer = .0f;
	static float DownSetDelay = 1.0f;
	
	fallTimer += Time::deltaTime;

	if (!isDownCollider)
	{
		fallTimer = .0f;

		DownSetTimer += Time::deltaTime;
		if (DownSetTimer >= DownSetDelay)
		{
			TetrisBlockController::SpawnBlocks(Random::Range(0,6), 120, 120);
			DownSetTimer = .0f;

			return;
		}
	}

	if (Input::getKeyDown("left") && isLeftCollider)
	{
		for (int i = TetrisBlockController::GetTotalSpawnedBlocksAmount() - 4; i < TetrisBlockController::GetTotalSpawnedBlocksAmount(); ++i)
		{
			gameObject[1][i]->translate(-40, 0);
			gameObject[2][i]->translate(-40, 0);
		}
	}

	if (Input::getKeyDown("right") && isRightCollider)
	{
		for (int i = TetrisBlockController::GetTotalSpawnedBlocksAmount() - 4; i < TetrisBlockController::GetTotalSpawnedBlocksAmount(); ++i)
		{
			gameObject[1][i]->translate(40, 0);
			gameObject[2][i]->translate(40, 0);
		}
	}

	if (Input::getKey("down") && isDownCollider)
	{
		for (int i = TetrisBlockController::GetTotalSpawnedBlocksAmount() - 4; i < TetrisBlockController::GetTotalSpawnedBlocksAmount(); ++i)
		{
			fallTimer += Time::deltaTime * 2;
		}
	}


	if(fallTimer >= fallDelay && isDownCollider)
	{
		for (int i = TetrisBlockController::GetTotalSpawnedBlocksAmount() - 4; i < TetrisBlockController::GetTotalSpawnedBlocksAmount(); ++i)
		{
			gameObject[1][i]->translate(0, 4);
			gameObject[2][i]->translate(0, 4);
		}
	
		fallTimer = 0;
	}
}

void ObjectManager::checkBorderReached()
{
	if (gameObject[1].size() < 4) return;

	for (int i = gameObject[1].size() - 4 ; i < gameObject[1].size(); i++)
	{
		vector<BoxCollider2D*> CheckCollider = gameObject[1][i]->getBoxCollider2D();

		for (int j = 0; j < CheckCollider.size(); ++j)
		{
			if (CheckCollider[j]->getColliderYpos() >= Global::GetHEIGHT() - 40)
			{
				isDownCollider = FALSE;
			}
			if (CheckCollider[j]->getColliderXpos() >= Global::GetWIDTH() - 40)
			{
				isRightCollider = FALSE;
			}
			if (CheckCollider[j]->getColliderXpos() <= 0)
			{
				isLeftCollider = FALSE;
			}
		}
	}

	for (int i = gameObject[2].size() - 4; i < gameObject[2].size(); i++)
	{
		vector<BoxCollider2D*> CheckCollider = gameObject[2][i]->getBoxCollider2D();

		for (int j = 0; j < CheckCollider.size(); ++j)
		{
			if (CheckCollider[j]->getColliderYpos() >= Global::GetHEIGHT())
			{
				TetrisBlockController::SetisCanRollingBlock(FALSE);

				return;
			}
			if (CheckCollider[j]->getColliderXpos() >= Global::GetWIDTH())
			{
				TetrisBlockController::SetisCanRollingBlock(FALSE);

				return;
			}
			if (CheckCollider[j]->getColliderXpos() <= 0)
			{
				TetrisBlockController::SetisCanRollingBlock(FALSE);

				return;
			}
		}
	}


}

void ObjectManager::getTetrisBlockObjectManager(vector<GameObject*>& _1stLayer, vector<GameObject*>& _2ndLayer)
{
	_1stLayer = gameObject[1];
	_2ndLayer = gameObject[2];
}