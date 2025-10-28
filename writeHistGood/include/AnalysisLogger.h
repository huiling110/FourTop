#ifndef ANALYSISLOGGER_H
#define ANALYSISLOGGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>
#include "TString.h"

/**
 * @brief Simple logging utility for analysis code
 *
 * Provides colored console output and optional file logging
 * Usage: LOG_INFO << "Message"; LOG_WARNING << "Warning"; LOG_ERROR << "Error";
 */
class AnalysisLogger {
public:
    enum class Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

private:
    Level m_level;
    std::ostringstream m_buffer;
    static std::ofstream m_logFile;
    static bool m_colorEnabled;

    static const char* getLevelString(Level level) {
        switch (level) {
            case Level::DEBUG:   return "DEBUG";
            case Level::INFO:    return "INFO";
            case Level::WARNING: return "WARNING";
            case Level::ERROR:   return "ERROR";
            default:             return "UNKNOWN";
        }
    }

    static const char* getColorCode(Level level) {
        if (!m_colorEnabled) return "";
        switch (level) {
            case Level::DEBUG:   return "\033[36m";  // Cyan
            case Level::INFO:    return "\033[32m";  // Green
            case Level::WARNING: return "\033[33m";  // Yellow
            case Level::ERROR:   return "\033[31m";  // Red
            default:             return "\033[0m";
        }
    }

    static const char* getResetCode() {
        return m_colorEnabled ? "\033[0m" : "";
    }

    std::string getTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

public:
    explicit AnalysisLogger(Level level) : m_level(level) {}

    ~AnalysisLogger() {
        std::string message = m_buffer.str();
        std::string timestamp = getTimestamp();
        std::string levelStr = getLevelString(m_level);

        // Console output with color
        std::cout << getColorCode(m_level)
                  << "[" << timestamp << "] "
                  << "[" << levelStr << "] "
                  << message
                  << getResetCode() << std::endl;

        // File output (no color)
        if (m_logFile.is_open()) {
            m_logFile << "[" << timestamp << "] "
                      << "[" << levelStr << "] "
                      << message << std::endl;
            m_logFile.flush();
        }
    }

    template<typename T>
    AnalysisLogger& operator<<(const T& value) {
        m_buffer << value;
        return *this;
    }

    // Specialization for TString
    AnalysisLogger& operator<<(const TString& value) {
        m_buffer << value.Data();
        return *this;
    }

    static void setLogFile(const std::string& filename) {
        if (m_logFile.is_open()) {
            m_logFile.close();
        }
        m_logFile.open(filename, std::ios::app);
        if (!m_logFile.is_open()) {
            std::cerr << "Failed to open log file: " << filename << std::endl;
        }
    }

    static void setColorEnabled(bool enabled) {
        m_colorEnabled = enabled;
    }
};

// Static member initialization
inline std::ofstream AnalysisLogger::m_logFile;
inline bool AnalysisLogger::m_colorEnabled = true;

// Convenience macros
#define LOG_DEBUG   AnalysisLogger(AnalysisLogger::Level::DEBUG)
#define LOG_INFO    AnalysisLogger(AnalysisLogger::Level::INFO)
#define LOG_WARNING AnalysisLogger(AnalysisLogger::Level::WARNING)
#define LOG_ERROR   AnalysisLogger(AnalysisLogger::Level::ERROR)

#endif // ANALYSISLOGGER_H
