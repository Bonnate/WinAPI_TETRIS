#pragma once

#include "TetrisBlock.h"
#include "ObjectManager.h"
#include "deltaTime.h"
#include "Random.h"
#include <vector>

using namespace std;

class TetrisBlockController
{
private:
	static int TotalSpawnedBlocksAmount;
	static int ControllingBlockType;
	static int ControllingBlockstateId;
	static bool isCanRollingBlock;
	static int ControllingBlocksAmount;

public:
	static void SpawnBlocks(int type, int px, int py);
	static void BlockControlUpdate();
	static void SetisCanRollingBlock(bool value);
	static void SetControllingBlockstateId(int value);
	static void RollBlocks();
	static int  GetControllingBlocksAmount();
	static void SetTotalSpawnedBlocksAmount(int index);
	static int  GetTotalSpawnedBlocksAmount();
};

