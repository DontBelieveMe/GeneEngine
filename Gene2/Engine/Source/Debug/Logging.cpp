// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Gene2/Debug/Logging.hpp>
#include <Gene2/Debug/Assert.hpp>

#include <Gene2/Platform/PlatformInfo.hpp>

#include <iostream>

using namespace g2;

const char* Logger::GetSeverityAsString(ELogSeverity severity)
{
	switch (severity)
	{
	case S_TRACE: return "trace";
	case S_WARN:  return "warn";
	case S_ERROR: return "error";
	case S_FATAL: return "fatal";
	}
	
	return nullptr;
}

#ifdef G2_PLATFORM_WINDOWS
#include <Windows.h>
#endif

void ConsoleLoggerRoute::HandleDispatchedMessage(ELogSeverity severity, const String& message)
{
#ifdef G2_PLATFORM_WINDOWS
	WORD color = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	switch (severity)
	{
	case S_ERROR:
	case S_FATAL: color = FOREGROUND_INTENSITY | FOREGROUND_RED; break;
	case S_WARN: color = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN; break;
	case S_TRACE: color = FOREGROUND_GREEN; break;
	}

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, color);
#endif

	std::cout << message << std::endl;

#ifdef G2_PLATFORM_WINDOWS
	SetConsoleTextAttribute(console, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#endif
}