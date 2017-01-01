/*
 * @file         console_log.h
 * @author       Arthur Fait
 * @date         31.08.14
 *
 */

#ifndef CONSOLE_LOG_H
#define CONSOLE_LOG_H

#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <string>

namespace logging {

enum log_level
{
    debug,
    info,
    warning,
    error,
    fatal
};

/**
 * @brief print log
 *
 * @param level sets verbosity
 * @param file which cpp file
 * @param line whic line
 * @param message format string with with desiredmessage
 */
void log(log_level level, const char *file, int line, const char *message, ...);


} // namespace logging

#ifdef INFO_LOG_DISABLED
#define log_info(...) ((void)0)
#else
#define log_info(...) logging::log(logging::info, __FILE__, __LINE__, __VA_ARGS__)
#endif

#ifdef WARINING_LOG_DISABLED
#define log_warning(...) ((void)0)
#else
#define log_warning(...) logging::log(logging::warning, __FILE__, __LINE__, __VA_ARGS__)
#endif

#ifdef ERROR_LOG_DISABLED
#define log_error(...) ((void)0)
#else
#define log_error(...) logging::log(logging::error, __FILE__, __LINE__, __VA_ARGS__)
#endif


class LogScopeTime {
public:
    LogScopeTime(const std::string& message)
        :m_message(message)
    {
        clock_gettime(CLOCK_REALTIME, &__measure_start);
        __measure_stop.tv_sec = __measure_start.tv_sec;
        __measure_stop.tv_nsec = __measure_start.tv_nsec;
    }

    ~LogScopeTime() {
        float scopetime = elapsed();
        log_info("%s scope time: %f ms", m_message.c_str(), scopetime);
    }

    void restart() {
        clock_gettime(CLOCK_REALTIME, &__measure_start);
    }

    void logElapsed() {
        float scopetime = elapsed();
        log_info("%s elapsed time: %f ms", m_message.c_str(), scopetime);
    }

    float elapsed() {
        clock_gettime(CLOCK_REALTIME, &__measure_stop);
        return ((__measure_stop.tv_sec - __measure_start.tv_sec ) * 1000.0f + (float)(__measure_stop.tv_nsec - __measure_start.tv_nsec) / 1e+6f);
    }
private:
    std::string m_message;
    struct timespec __measure_start;
    struct timespec __measure_stop;
};

#endif // CONSOLE_LOG_H
