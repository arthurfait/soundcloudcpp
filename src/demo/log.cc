/*
 * @file         console_log.cc
 * @author       Arthur Fait
 * @date         31.08.14
 *
 */

 #include "log.h"

 namespace logging {

void log(log_level level, const char *file, int line, const char *message, ...)
{
    const size_t kMAX_MESSAGE_LENGTH = 512;
    char buffer[kMAX_MESSAGE_LENGTH];
    va_list args;
    va_start(args, message);
    vsnprintf(buffer, kMAX_MESSAGE_LENGTH, message, args);

    switch (level) {
    case debug:
        printf("\033[35m[LOG_DEBUG at %s:%d]:\033[m ", file, line);
        break;
    case info:
        printf("\033[32m[LOG_INFO at %s:%d]:\033[m ", file, line);
        break;
    case warning:
        printf("\033[33m[LOG_WARNING at %s:%d]:\033[m ", file, line);
        break;
    case error:
        printf("\033[31m[LOG_ERROR at %s:%d]:\033[m ", file, line);
        break;
    case fatal:
        printf("\033[31m[LOG_FATAL at %s:%d]:\033[m ", file, line);
        break;
    default:
        printf("\033[32m[LOG_INFO at %s:%d]:\033[m ", file, line);
    }
    printf("%s", buffer);
    printf("\n");
    va_end(args);
}

} // namespace logging
