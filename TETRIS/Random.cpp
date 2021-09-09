#include "framework.h"

void Random::Init()
{
    srand(time(nullptr));
}

int Random::Range(int min, int max)
{
    int r = rand() % (max - min + 1) + min;
    return r;
}