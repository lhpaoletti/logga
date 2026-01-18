/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Luis Paoletti <lh.paoletti@gmail.com>
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "logga.h"


static char *get_log_head(logga_level_t level, char *name)
{
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    time_t secs = tp.tv_sec;
    long ms = tp.tv_nsec / 1000000L;
    struct tm tinfo;
    gmtime_r(&secs, &tinfo);

    char *log_head = NULL;
    if (name != NULL) {
        asprintf(
            &log_head, "[%04d-%02d-%02d %02d:%02d:%02d,%03ld] %s (%s): ",
            tinfo.tm_year + 1900, tinfo.tm_mon + 1, tinfo.tm_mday,
            tinfo.tm_hour, tinfo.tm_min, tinfo.tm_sec, ms,
            logga_lvtostr(level), name
        );
    } else {
        asprintf(
            &log_head, "[%04d-%02d-%02d %02d:%02d:%02d,%03ld] %s: ",
            tinfo.tm_year + 1900, tinfo.tm_mon + 1, tinfo.tm_mday,
            tinfo.tm_hour, tinfo.tm_min, tinfo.tm_sec, ms,
            logga_lvtostr(level)
        );
    }

    return log_head;
}

static char *concatenate(char *str1, char *str2)
{
    size_t str1_len = strlen(str1);
    size_t str2_len = strlen(str2);
    size_t total_len = str1_len + str2_len + 1;
    char *buf = malloc(total_len);
    strncpy(buf, str1, str1_len);
    strncpy(buf + str1_len, str2, str2_len);
    buf[total_len - 1] = '\0';
    return buf;
}

static void log(logga_t *logga, char *msg, va_list ap)
{
    char *log_head = get_log_head(logga->level, logga->name);
    char *msg_formatted = NULL;
    vasprintf(&msg_formatted, msg, ap);
    char *log_msg = concatenate(log_head, msg_formatted);

    fprintf(logga->outfile, "%s\n", log_msg);

    free(log_msg);
    free(msg_formatted);
    free(log_head);
}

const char *logga_lvtostr(logga_level_t level)
{
    switch (level) {
        case LOGGA_TRACE: return "TRACE";
        case LOGGA_DEBUG: return "DEBUG";
        case LOGGA_INFO:  return "INFO";
        case LOGGA_WARN:  return "WARNING";
        case LOGGA_ERROR: return "ERROR";
        default: {
            char *log_head = get_log_head(LOGGA_ERROR, "logga");
            char *msg = "unexhaustive options (logga_lvtostr)";
            char *log_msg = concatenate(log_head, msg);
            fprintf(stderr, "%s\n", log_msg);
            free(log_msg);
            free(log_head);
            exit(1);
        }
    }
}

void logga_init(logga_t *logga)
{
    logga->name = NULL;
    logga->level = LOGGA_INFO;
    logga->outfile = stderr;
}

void logga_trace(logga_t *logga, char *msg, ...)
{
    if (logga->level > LOGGA_TRACE) return;
    va_list ap;
    va_start(ap, msg);
    log(logga, msg, ap);
    va_end(ap);
}

void logga_debug(logga_t *logga, char *msg, ...)
{
    if (logga->level > LOGGA_DEBUG) return;
    va_list ap;
    va_start(ap, msg);
    log(logga, msg, ap);
    va_end(ap);
}

void logga_info(logga_t *logga, char *msg, ...)
{
    if (logga->level > LOGGA_INFO) return;
    va_list ap;
    va_start(ap, msg);
    log(logga, msg, ap);
    va_end(ap);
}

void logga_warn(logga_t *logga, char *msg, ...)
{
    if (logga->level > LOGGA_WARN) return;
    va_list ap;
    va_start(ap, msg);
    log(logga, msg, ap);
    va_end(ap);
}

void logga_error(logga_t *logga, char *msg, ...)
{
    va_list ap;
    va_start(ap, msg);
    log(logga, msg, ap);
    va_end(ap);
}
