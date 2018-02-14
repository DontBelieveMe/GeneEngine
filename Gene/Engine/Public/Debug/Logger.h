#pragma once

#include <string>
#include <iostream>

#define LOG_FILTER(priority) Gene::Logger::GetLogger()->SetFilter(priority)
#define LOG_CLEAR_FILTER() Gene::Logger::GetLogger()->SetFilter(0)

// #define DISABLE_LOGGING

#ifdef DISABLE_LOGGING
    #define LOG(...)
#else
    #define LOG Gene::Logger::GetLogger()->Log
#endif

namespace Gene {
    struct LogLevel {
        static const unsigned Error;
        static const unsigned Warning;
        static const unsigned Infomation;
        static const unsigned Assert;
    };

    /*
    TODO:
        -> Ideally I would want zero cost compile time filtering of log messages as well
        -> The ability to log to other output streams (text files, over a network/socket stream etc)
    */
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
            if (priority & LogLevel::Assert) return "Assert";

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
