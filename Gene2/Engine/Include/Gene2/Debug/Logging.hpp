// Copyright 2017-2019 Barney Wilks. All Rights Reserved

#pragma once

#include <Gene2/Core/Utility/Singleton.hpp>

#include <Gene2/Core/StdLib/String.hpp>
#include <Gene2/Core/StdLib/Array.hpp>
#include <Gene2/Core/StdLib/Memory.hpp>

#define G2_LOG_FMT(severity, ...) \
	g2::Logger::GetInstance()->LogMessage(severity, __LINE__, __FILE__, g2::LMF_FORMAT_STRING, __VA_ARGS__)

#define G2_TRACE(...) G2_LOG_FMT(g2::S_TRACE, __VA_ARGS__)
#define G2_WARN(...) G2_LOG_FMT(g2::S_WARN, __VA_ARGS__)
#define G2_ERROR(...) G2_LOG_FMT(g2::S_ERROR, __VA_ARGS__)
#define G2_FATAL(...) G2_LOG_FMT(g2::S_FATAL, __VA_ARGS__)

#define G2_CORE_LOGGER g2::Logger::GetInstance

namespace g2 {
	enum ELogSeverity {
		S_TRACE = 1 << 0,
		S_WARN  = 1 << 1,
		S_ERROR = 1 << 2,
		S_FATAL = 1 << 3
	};
	
	enum ELogMessageFormat {
		LMF_LITERAL_STRING,
		LMF_FORMAT_STRING
	};

	struct ILoggerRoute {
		virtual void HandleDispatchedMessage(ELogSeverity severity, const String& message) = 0;
	};

	struct ConsoleLoggerRoute : public ILoggerRoute {
		virtual void HandleDispatchedMessage(ELogSeverity severity, const String& message);
	};

	class Logger : public Singleton<Logger> {
	private:
		const char* GetSeverityAsString(ELogSeverity severity);

		Array<UniquePtr<ILoggerRoute>> m_routes;
	public:
		template <typename T>
		void AddRoute() {
			UniquePtr<ILoggerRoute> route = g2::MakeUnique<T>();
			m_routes.push_back(std::move(route));
		}
		
		void LogMessage(ELogSeverity severity, int line, const char* file, ELogMessageFormat fmt) 
		{
			G2_MARK_VARIABLE_UNUSED(severity);
			G2_MARK_VARIABLE_UNUSED(line);
			G2_MARK_VARIABLE_UNUSED(file);
			G2_MARK_VARIABLE_UNUSED(fmt);
		}

		template <typename... Args>
		void LogMessage(ELogSeverity severity,
						int line, const char* file, ELogMessageFormat formatStringType,
						const String& formatString, const Args&... args)
		{
			String message = g2::FormatString(formatString, args...);
			
			if (formatStringType == LMF_LITERAL_STRING)
			{
				message	= formatString;
			}
			G2_MARK_VARIABLE_UNUSED(file);
			const char* severityString = this->GetSeverityAsString(severity);
			String output = g2::FormatString("({0}:{1}) [{2}]: {3}", /*file*/"", line, severityString, message);

			for (const auto& route : m_routes)
			{
				route->HandleDispatchedMessage(severity, output);
			}
		}
	};
}
