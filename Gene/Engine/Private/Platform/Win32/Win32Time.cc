#include <Platform/OS.h>
#if defined(GENE_OS_WINDOWS)
    #include <Platform/Time.h>
    #include <Windows.h>

    using namespace Gene::Platform;

    void GameTime::Sleep(float milliseconds)
    {
        ::Sleep(milliseconds);
    }
#endif