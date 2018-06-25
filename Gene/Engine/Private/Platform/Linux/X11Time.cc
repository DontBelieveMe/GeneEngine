// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Platform/Time.h>
#include <unistd.h>

using namespace gene::platform;

void GameTime::Sleep(float milliseconds)
{
    float microseconds = milliseconds * 1000;
    usleep(microseconds);
}
