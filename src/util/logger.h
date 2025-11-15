#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <mutex>

enum class LogLevel { DEBUG, INFO, WARNING, ERROR };

class Logger {
public:
    template<typename... Args>
    static void log(LogLevel level, const char* file, int line,
                    const char* func, Args&&... args)
    {
        std::ostringstream oss;
        append(oss, std::forward<Args>(args)...);

        std::lock_guard<std::mutex> lock(mutex_);   // thread-safe
        std::cout << "[" << levelToString(level) << "] "
                  << file << ":" << line << " (" << func << ") -> "
                  << oss.str() << std::endl;
    }

private:
    template<typename T>
    static void append(std::ostringstream& oss, T&& value) {
        oss << std::forward<T>(value);
    }

    template<typename T, typename... Args>
    static void append(std::ostringstream& oss, T&& value, Args&&... args) {
        oss << std::forward<T>(value);
        append(oss, std::forward<Args>(args)...);
    }

    static const char* levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG:   return "DEBUG";
            case LogLevel::INFO:    return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR:   return "ERROR";
            default:                return "UNKNOWN";
        }
    }

    static std::mutex mutex_;
};

#define LOG_DEBUG(...)   Logger::log(LogLevel::DEBUG, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_INFO(...)    Logger::log(LogLevel::INFO,  __FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_WARN(...)    Logger::log(LogLevel::WARNING, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_ERROR(...)   Logger::log(LogLevel::ERROR, __FILE__, __LINE__, __func__, __VA_ARGS__)