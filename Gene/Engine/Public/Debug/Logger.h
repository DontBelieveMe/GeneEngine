#pragma once

#include <string>
#include <iostream>

#define LOG_FILTER(priority) Gene::Logger::GetLogger()->SetFilter(priority)
#define LOG_CLEAR_FILTER() Gene::Logger::GetLogger()->SetFilter(0)

#define LOG Gene::Logger::GetLogger()->Log

namespace Gene {
    struct LogLevel {
        static const unsigned Error = 1;
        static const unsigned Warning = 2;
        static const unsigned Infomation = 3;
    };

    class Logger {
    private:
        unsigned m_Filter;

        template <typename T, typename... Args>
        void LogData(const T& msg, const Args&... args) {
            std::cout << msg;
            LogData(args...);
        }

        void LogData() {}

        const char *GetPriorityString(const unsigned& priority)
        {
            if (priority & LogLevel::Error) return "Error";
            if (priority & LogLevel::Warning) return "Warning";
            if (priority & LogLevel::Infomation) return "Infomation";

            return "UnkownErrorLevel";
        }

    public:
        Logger() : m_Filter(0) {}

        template <typename... Args>
        void Log(const unsigned& priority, const std::string& message, const Args&... args)
        {
            if (m_Filter & priority) { return; }
            std::cout << "[GLog] [" << GetPriorityString(priority) << "]: " << message;
            LogData(args...);
            std::cout << "\n";
        }

        void SetFilter(const unsigned& priority)
        {
            m_Filter = priority;
        }

        static Logger *GetLogger() {
            static Logger logger;
            return &logger;
        }
    };
}