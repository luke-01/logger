#include "logger.h"

static const char* COLOR_CODES[] = {
    "\x1b[0m",
    "\x1b[30m", "\x1b[31m", "\x1b[32m", "\x1b[33m",
    "\x1b[34m", "\x1b[35m", "\x1b[36m", "\x1b[37m",
};

void loggerCreate(Logger* log) {
    log->output_fp = stderr;
    log->colors_enabled = true;
    log->level_colors[LogTrace] = LogColorWhite;
    log->level_colors[LogDebug] = LogColorCyan;
    log->level_colors[LogInfo]  = LogColorGreen;
    log->level_colors[LogWarn]  = LogColorYellow;
    log->level_colors[LogError] = LogColorRed;
    log->level_colors[LogFatal] = LogColorMagenta;
}

void loggerDelete(Logger* log) {
    if (fileno(log->output_fp) > 2) fclose(log->output_fp);
}

// Sets a log file and stops outputing to stderr (if it was the previous output_fp), also disables
// colors so that the file isn't littered with ansi escape codes
void loggerSetLogFile(Logger* log, const char* file) {
    if (fileno(log->output_fp) > 2) fclose(log->output_fp);
    log->output_fp = fopen(file, "a");
    log->colors_enabled = false;
}

void loggerLog(Logger* log, LogLevel lvl, const char* fmt, ...) {
    LogColor color = log->level_colors[lvl];
    if (log->colors_enabled) fprintf(log->output_fp, "%s", COLOR_CODES[color]);

    va_list args;
    va_start(args, fmt);
    vfprintf(log->output_fp, fmt, args);
    va_end(args);

    if (log->colors_enabled) fprintf(log->output_fp, "%s", COLOR_CODES[0]);
    fprintf(log->output_fp, "\n");
}
