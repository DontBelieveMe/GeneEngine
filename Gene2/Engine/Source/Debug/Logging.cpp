// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Gene2/Debug/Logging.hpp>
#include <Gene2/Debug/Assert.hpp>

#include <iostream>

using namespace g2;

const char* Logger::GetSeverityAsString(LogSeverity severity)
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

void ConsoleLoggerRoute::HandleDispatchedMessage(const String& message)
{
	std::cout << message << std::endl;
}