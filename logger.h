#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

typedef enum { LogTrace=0, LogDebug, LogInfo, LogWarn, LogError, LogFatal } LogLevel;
typedef enum {
    LogColorReset=0,
    LogColorBlack, LogColorRed, LogColorGreen, LogColorYellow,
    LogColorBlue, LogColorMagenta, LogColorCyan, LogColorWhite
} LogColor;

typedef struct {
    LogColor level_colors[6];
    bool colors_enabled;
    FILE* output_fp;
} Logger;

// Initializes a logger that outputs to stderr with colors enabled
void loggerCreate(Logger* log);
void loggerDelete(Logger* log);
void loggerSetLogFile(Logger* log, const char* file);
void loggerLog(Logger* log, LogLevel lvl, const char* fmt, ...);

#endif
