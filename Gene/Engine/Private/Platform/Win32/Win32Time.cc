// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Platform/OS.h>
#if defined(GENE_OS_WINDOWS)
    #include <Platform/Time.h>
    #include <Windows.h>

    using namespace Gene::Platform;

    void GameTime::Sleep(float milliseconds)
    {
        ::Sleep(static_cast<DWORD>(milliseconds));
    }
#endif
