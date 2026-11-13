/* snprintf is C99; this makes glibc declare it in the C89 build too */
#define _ISOC99_SOURCE

#include <devkit/log/log.h>

#include <stdio.h>
#include <time.h>

/******************************************************************************
 *
 * 				LOCAL INTERFACE
 *
 ******************************************************************************/

LOC const char *s_level_name(LogLevel lvl);
LOC void s_timestamp(char *buf);
LOC void s_log_intern(LogLevel lvl, const char *file, s32 line, char *msg);

/******************************************************************************
 *
 * 				PUBLIC FUNCTIONS
 *
 ******************************************************************************/

PUB void log_msg(const LogLevel lvl, const char *file, s32 line,
        char *msg)
{
        char buf[LOG_MESSAGE_LENGTH];

        /* Create log message, cut off if it is too long for the buffer */
        snprintf(buf, sizeof(buf), "%s", msg);

        /* Push s32o log */
        s_log_intern(lvl, file, line, buf);
}

PUB void log_s(const LogLevel lvl, const char *file, s32 line,
        const char *fmt, char *s)
{
        char buf[LOG_MESSAGE_LENGTH];

        /* Create log message, cut off if it is too long for the buffer */
        snprintf(buf, sizeof(buf), fmt, s);

        /* Push s32o log */
        s_log_intern(lvl, file, line, buf);
}

PUB void log_ss(const LogLevel lvl, const char *file, s32 line,
                const char *fmt, char *s1, char *s2)
{
        char buf[LOG_MESSAGE_LENGTH];

        /* Create log message, cut off if it is too long for the buffer */
        snprintf(buf, sizeof(buf), fmt, s1, s2);

        /* Push s32o log */
        s_log_intern(lvl, file, line, buf);
}

PUB void log_i(const LogLevel lvl, const char *file, s32 line,
                const char *fmt, s32 i)
{
        char buf[LOG_MESSAGE_LENGTH];

        /* Create log message, cut off if it is too long for the buffer */
        snprintf(buf, sizeof(buf), fmt, i);

        /* Push s32o log */
        s_log_intern(lvl, file, line, buf);
}

PUB void log_ii(const LogLevel lvl, const char *file, s32 line,
                const char *fmt, s32 i1, s32 i2)
{
        char buf[LOG_MESSAGE_LENGTH];

        /* Create log message, cut off if it is too long for the buffer */
        snprintf(buf, sizeof(buf), fmt, i1, i2);

        /* Push s32o log */
        s_log_intern(lvl, file, line, buf);
}

PUB void log_iii(const LogLevel lvl, const char *file, s32 line,
                const char *fmt, s32 i1, s32 i2, s32 i3)
{
        char buf[LOG_MESSAGE_LENGTH];

        /* Create log message, cut off if it is too long for the buffer */
        snprintf(buf, sizeof(buf), fmt, i1, i2, i3);

        /* Push s32o log */
        s_log_intern(lvl, file, line, buf);
}

PUB void log_iiii(const LogLevel lvl, const char *file, s32 line,
                const char *fmt, s32 i1, s32 i2, s32 i3, s32 i4)
{
        char buf[LOG_MESSAGE_LENGTH];

        /* Create log message, cut off if it is too long for the buffer */
        snprintf(buf, sizeof(buf), fmt, i1, i2, i3, i4);

        /* Push s32o log */
        s_log_intern(lvl, file, line, buf);
}

PUB void log_p(const LogLevel lvl, const char *file, s32 line,
                const char *fmt, void *p)
{
        char buf[LOG_MESSAGE_LENGTH];

        /* Create log message, cut off if it is too long for the buffer */
        snprintf(buf, sizeof(buf), fmt, p);

        /* Push s32o log */
        s_log_intern(lvl, file, line, buf);
}

/******************************************************************************
 *
 * 				LOCAL FUNCTIONS
 *
 ******************************************************************************/

LOC const char *s_level_name(LogLevel lvl)
{
        switch(lvl) {
                case LOG_DEBUG: return "DEBUG";
                case LOG_INFO: return "INFO";
                case LOG_WARN: return "WARN";
                case LOG_ERROR: return "ERROR";
                default: return "UNKNOWN";
        }
}

LOC void s_timestamp(char *buf)
{
        time_t t     = time(NULL);
        struct tm tm = *localtime(&t);

        sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d",
                        tm.tm_year + 1900,
                        tm.tm_mon + 1,
                        tm.tm_mday,
                        tm.tm_hour,
                        tm.tm_min,
                        tm.tm_sec);
}

LOC void s_log_intern(LogLevel lvl, const char *file, s32 line,
                char *msg)
{
        char buf[LOG_ENTRY_LENGTH];
        char ts[32];

        if(lvl == LOG_DEBUG) return;

        s_timestamp(ts);

        /**
         * Create the log entry.
         */
        snprintf(buf, sizeof(buf), "[%s] [%s:%d] [%s] %s",
                        ts,
                        file, line,
                        s_level_name(lvl),
                        msg);

        /**
         * Push log entry s32o stderr.
         */
        fprintf(stderr, "%s\n", buf);
}
