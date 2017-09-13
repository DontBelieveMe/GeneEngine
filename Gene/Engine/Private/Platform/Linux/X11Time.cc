#include <Platform/Time.h>
#include <unistd.h>

using namespace Gene::Platform;

void GameTime::Sleep(float milliseconds)
{
    float microseconds = milliseconds * 1000;
    usleep(microseconds);
}
