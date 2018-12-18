// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Core/Utility/Singleton.hpp>
#include <Gene2/Core/StdLib/String.hpp>

#include <iostream>

#define G2_LOG(message, ...) \
	g2::Logger::GetInstance()->LogMessage(message, __VA_ARGS__)

namespace g2 {
	class Logger : public Singleton<Logger> {
	public:
		template <typename... Args>
		void LogMessage(const String& formatString, const Args&... args)
		{
			String message = g2::FormatString(formatString, args...);

			std::cout << message << std::endl;
		}
	};
}