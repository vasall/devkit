#ifndef VASALL_DEVKIT_LOG_H
#define VASALL_DEVKIT_LOG_H

#include <devkit/scope.h>
#include <devkit/types.h>

/******************************************************************************
 *
 * 				 DEFINES/MACROS
 *
 ******************************************************************************/

#define LOG_ENTRY_LENGTH   1024 /* The maximum size of a log entry       */
#define LOG_MESSAGE_LENGTH 512 /* The maximum length of the log message */

/******************************************************************************
 *
 * 				   STRUCTURES
 *
 ******************************************************************************/

/* Log levels */
typedef enum LogLevel {
        LOG_DEBUG = 0,
        LOG_INFO  = 1,
        LOG_WARN  = 2,
        LOG_ERROR = 3
} LogLevel;

/******************************************************************************
 *
 * 				PUBLIC INTERFACE
 *
 ******************************************************************************/

/**
 * Fixed‑argument logging functions
 */
PUB void log_msg(LogLevel lvl, const char *file, s32 line,
                char *msg);

PUB void log_s(LogLevel lvl, const char *file, s32 line,
                const char *fmt, char *s);

PUB void log_ss(LogLevel lvl, const char *file, s32 line,
                const char *fmt, char *s1, char *s2);

PUB void log_i(LogLevel lvl, const char *file, s32 line,
                const char *fmt, s32 i);

PUB void log_ii(LogLevel lvl, const char *file, s32 line,
                const char *fmt, s32 i1, s32 i2);

PUB void log_iii(LogLevel lvl, const char *file, s32 line,
                const char *fmt, s32 i1, s32 i2, s32 i3);

PUB void log_iiii(LogLevel lvl, const char *file, s32 line,
                const char *fmt, s32 i1, s32 i2, s32 i3, s32 i4);

PUB void log_p(LogLevel lvl, const char *file, s32 line,
                const char *fmt, void *p);

/**
 * Macro wrappers (default level = LOG_INFO)
 */
#define LOG(lvl, msg) \
        log_msg(lvl, __FILE__, __LINE__, (msg))

#define LOG_S(lvl, fmt, s) \
        log_s(lvl, __FILE__, __LINE__, (fmt), (s))

#define LOG_SS(lvl, fmt, s1, s2) \
        log_ss(lvl, __FILE__, __LINE__, (fmt), (s1), (s2))

#define LOG_I(lvl, fmt, i) \
        log_i(lvl, __FILE__, __LINE__, (fmt), (i))

#define LOG_II(lvl, fmt, i1, i2) \
        log_ii(lvl, __FILE__, __LINE__, (fmt), (i1), (i2))

#define LOG_III(lvl, fmt, i1, i2, i3) \
        log_iii(lvl, __FILE__, __LINE__, (fmt), (i1), (i2), (i3))

#define LOG_IIII(lvl, fmt, i1, i2, i3, i4) \
        log_iiii(lvl, __FILE__, __LINE__, (fmt), (i1), (i2), (i3), (i4))

#define LOG_P(lvl, fmt, p) \
        log_p(lvl, __FILE__, __LINE__, (fmt), (p))

#endif /* VASALL_DEVKIT_LOG_H */
