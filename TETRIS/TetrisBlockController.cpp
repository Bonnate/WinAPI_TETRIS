#include "framework.h"

int TetrisBlockController::TotalSpawnedBlocksAmount = 0;
int TetrisBlockController::ControllingBlockType = 0;
int TetrisBlockController::ControllingBlockstateId = 0;
int TetrisBlockController::ControllingBlocksAmount = 0;
bool TetrisBlockController::isCanRollingBlock = TRUE;

void TetrisBlockController::SpawnBlocks(int type, int px, int py)
{
	ControllingBlockType = type;
	ControllingBlockstateId = 0;
	TotalSpawnedBlocksAmount += 4;

	switch (type)
	{
	case 0:
		ObjectManager::instantiate(new TetrisBlock(0 +px, 0 +py), 1);
		ObjectManager::instantiate(new TetrisBlock(40+px, 0 +py), 1);
		ObjectManager::instantiate(new TetrisBlock(80+px, 0 +py), 1);
		ObjectManager::instantiate(new TetrisBlock(120+px, 0 +py), 1);

		ObjectManager::instantiate(new RotateBlockCollider(40+px, -40 +py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40+px, 0   +py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40+px, 40  +py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40+px, 80  +py), 2);
		
		ControllingBlocksAmount = 4;

		break;

	case 1:
		ObjectManager::instantiate(new TetrisBlock(0 +px, 0 +py), 1);
		ObjectManager::instantiate(new TetrisBlock(0 +px, 40+py), 1);
		ObjectManager::instantiate(new TetrisBlock(40+px, 40+py), 1);
		ObjectManager::instantiate(new TetrisBlock(80+px, 40+py), 1);

		ObjectManager::instantiate(new RotateBlockCollider(40 + px, 40 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(0 + px, 40 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(0 + px, 80 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(0 + px, 120 + py), 2);

		ControllingBlocksAmount = 4;

		break;

	case 2:
		ObjectManager::instantiate(new TetrisBlock(80+px, 0 +py), 1);
		ObjectManager::instantiate(new TetrisBlock(80+px, 40+py), 1);
		ObjectManager::instantiate(new TetrisBlock(40 +px,40+py), 1);
		ObjectManager::instantiate(new TetrisBlock(0 +px, 40+py), 1);

		ObjectManager::instantiate(new RotateBlockCollider(80 + px, 80 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40 + px, 80 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40 + px, 40 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40 + px, 00 + py), 2);

		ControllingBlocksAmount = 4;

		break;

	case 3:
		ObjectManager::instantiate(new TetrisBlock(0 +px, 0 +py), 1);
		ObjectManager::instantiate(new TetrisBlock(40+px, 0 +py), 1);
		ObjectManager::instantiate(new TetrisBlock(0 +px, 40+py), 1);
		ObjectManager::instantiate(new TetrisBlock(40+px, 40+py), 1);

		ObjectManager::instantiate(new RotateBlockCollider(0 + px, 0 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40 + px, 0 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(0 + px, 40 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40 + px, 40 + py), 2);

		ControllingBlocksAmount = 4;

		break;

	case 4:
		ObjectManager::instantiate(new TetrisBlock(80+px, 0 +py), 1);
		ObjectManager::instantiate(new TetrisBlock(40+px, 0 +py), 1);
		ObjectManager::instantiate(new TetrisBlock(40 +px, 40+py), 1);
		ObjectManager::instantiate(new TetrisBlock(0+px, 40+py), 1);

		ObjectManager::instantiate(new RotateBlockCollider(80 + px, 80 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(80 + px, 40 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40 + px, 40 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40 + px, 00 + py), 2);

		ControllingBlocksAmount = 4;

		break;

	case 5:
		ObjectManager::instantiate(new TetrisBlock(40+px, 0 +py), 1);
		ObjectManager::instantiate(new TetrisBlock(0 +px, 40+py), 1);
		ObjectManager::instantiate(new TetrisBlock(40+px, 40+py), 1);
		ObjectManager::instantiate(new TetrisBlock(80+px, 40+py), 1);

		ObjectManager::instantiate(new RotateBlockCollider(80 + px, 40 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40 + px, 0 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40 + px, 40 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40 + px, 80 + py), 2);

		ControllingBlocksAmount = 4;

		break;

	case 6:
		ObjectManager::instantiate(new TetrisBlock(0 +px, 0 +py), 1);
		ObjectManager::instantiate(new TetrisBlock(40+px, 0 +py), 1);
		ObjectManager::instantiate(new TetrisBlock(40+px, 40+py), 1);
		ObjectManager::instantiate(new TetrisBlock(80+px, 40+py), 1);

		ObjectManager::instantiate(new RotateBlockCollider(0 + px, 0 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(0 + px, 40 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40 + px, 40 + py), 2);
		ObjectManager::instantiate(new RotateBlockCollider(40 + px, 80 + py), 2);

		ControllingBlocksAmount = 4;

		break;
	}
}

void TetrisBlockController::BlockControlUpdate()
{
	ObjectManager::controlBlocks();

	if (Input::getKeyDown("space"))
		RollBlocks();
}

void TetrisBlockController::SetisCanRollingBlock(bool value)
{
	isCanRollingBlock = value;
}

void TetrisBlockController::SetControllingBlockstateId(int value)
{
	ControllingBlockstateId = value;
}

void TetrisBlockController::RollBlocks()
{
	static vector<GameObject*> _1st_Layer, _2nd_Layer;

	ObjectManager::getTetrisBlockObjectManager(_1st_Layer, _2nd_Layer);

	if (!isCanRollingBlock) return;

	switch(ControllingBlockType)
	{
	case 0:
		if (ControllingBlockstateId == 0)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(40, -40);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(0, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(-40, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(-80, 80);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(-40, 40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(40, -40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(80, -80);

			ControllingBlockstateId = 1;
		}

		else if (ControllingBlockstateId == 1)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(-40, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(0, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(40, -40);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(80, -80);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(40, -40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(-40, 40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(-80, 80);

			ControllingBlockstateId = 0;

		}
			
		return;

	case 1:

		if (ControllingBlockstateId == 0)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(40, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(0, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(-40, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(-80, 80);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(0, 40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(40, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, -40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(-40, -80);

			ControllingBlockstateId = 1;
		}

		else if (ControllingBlockstateId == 1)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(0, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(40, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, -40);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(-40, -80);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(-40, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(0, 40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(40, 00);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(80, -40);

			ControllingBlockstateId = 2;

		}

		else if (ControllingBlockstateId == 2)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(-40, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(0, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(40, 00);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(80, -40);
													
			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(0, -80);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(-40, -40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(40, 40);

			ControllingBlockstateId = 3;

		}

		else if (ControllingBlockstateId == 3)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(0, -80);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(-40, -40);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(40, 40);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(40, 40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(-40, 40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(-80, 80);

			ControllingBlockstateId = 0;

		}

		return;

	case 2:

		if (ControllingBlockstateId == 0)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(0, 80); 
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(-40, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(0,0);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(40, -40);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(-80, -40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(-40, -80);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, -40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(40, 0);

			ControllingBlockstateId = 1;
		}

		else if (ControllingBlockstateId == 1)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(-80, -40);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(-40, -80);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, -40);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(40, 0);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(40,-40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(80,0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(40,40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(0,80);

			ControllingBlockstateId = 2;

		}

		else if (ControllingBlockstateId == 2)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(40, -40);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(80, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(40, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(0, 80);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(40, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(0, 40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(-40, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(-80, -40);

			ControllingBlockstateId = 3;

		}

		else if (ControllingBlockstateId == 3)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(40, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(0, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(-40, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(-80, -40);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(0, 80);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(-40, 40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(40, -40);

			ControllingBlockstateId = 0;

		}

		return;

	case 3:

		return;

	case 4:

		if (ControllingBlockstateId == 0)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(0, 80);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(40, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(40, -40);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(0, -80);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(-40, -40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(-40, +40);

			ControllingBlockstateId = 1;
		}

		else if (ControllingBlockstateId == 1)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(0, -80);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(-40, -40);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(-40, +40);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(0, 80);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(40, 40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(40, -40);

			ControllingBlockstateId = 0;

		}

		return;

	case 5:

		if (ControllingBlockstateId == 0)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(40, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(40, -40);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(-40, 40);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(-40, 40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(40, 40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(-40, -40);

			ControllingBlockstateId = 1;
		}

		else if (ControllingBlockstateId == 1)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(-40, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(40, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(-40, -40);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(-40, -40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(-40, 40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(40, -40);

			ControllingBlockstateId = 2;

		}

		else if (ControllingBlockstateId == 2)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(-40, -40);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(-40, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(40, -40);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(40, -40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(-40, -40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(40, 40);

			ControllingBlockstateId = 3;

		}

		else if (ControllingBlockstateId == 3)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(40, -40);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(-40, -40);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(40, 40);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(40, 40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(40, -40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(-40, 40);

			ControllingBlockstateId = 0;

		}

		return;

	case 6:

		if (ControllingBlockstateId == 0)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(0, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(-40, 40);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(-40, 40);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(40, -40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(40, -40);

			ControllingBlockstateId = 1;
		}

		else if (ControllingBlockstateId == 1)
		{
			_1st_Layer[TotalSpawnedBlocksAmount - 4]->translate(0, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 3]->translate(40, -40);
			_1st_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_1st_Layer[TotalSpawnedBlocksAmount - 1]->translate(40, -40);

			_2nd_Layer[TotalSpawnedBlocksAmount - 4]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 3]->translate(-40, 40);
			_2nd_Layer[TotalSpawnedBlocksAmount - 2]->translate(0, 0);
			_2nd_Layer[TotalSpawnedBlocksAmount - 1]->translate(-40, 40);

			ControllingBlockstateId = 0;

		}

		return;
	}
}

int TetrisBlockController::GetControllingBlocksAmount()
{
	return ControllingBlocksAmount;
}

void TetrisBlockController::SetTotalSpawnedBlocksAmount(int index)
{
	TotalSpawnedBlocksAmount = index;
}

int TetrisBlockController::GetTotalSpawnedBlocksAmount()
{
	return TotalSpawnedBlocksAmount;
}