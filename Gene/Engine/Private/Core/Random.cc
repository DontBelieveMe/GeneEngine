// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#include <Core/Random.h>

#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace gene;

void Random::Seed(unsigned seed)
{
    srand(seed);
}

float Random::FloatRange(float min, float max)
{
    const float range = fabsf(min - max);
    return range * ((((float)rand()) / (float)RAND_MAX)) + min;
}

int Random::IntRange(int min, int max)
{
    return min + (rand() % (max - min + 1));
}