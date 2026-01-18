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


static FILE *OUTFILE = NULL;
static logga_level_t logga_level = LOGGA_INFO;

void logga_set_outfile(FILE *outfile)
{
    OUTFILE = outfile;
}

void logga_set_level(logga_level_t level)
{
    logga_level = level;
}

static void logga(char *level, char *msg, va_list ap)
{
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    time_t secs = tp.tv_sec;
    long ms = tp.tv_nsec / 1000000L;
    struct tm tinfo;
    gmtime_r(&secs, &tinfo);

    char *log_head = NULL;
    asprintf(&log_head, "[%04d-%02d-%02d %02d:%02d:%02d,%03ld] %s: ",
             tinfo.tm_year + 1900, tinfo.tm_mon + 1, tinfo.tm_mday,
             tinfo.tm_hour, tinfo.tm_min, tinfo.tm_sec, ms,
             level);

    char *msg_formatted = NULL;
    vasprintf(&msg_formatted, msg, ap);

    size_t log_head_len = strlen(log_head);
    size_t msgf_len = strlen(msg_formatted);
    size_t total_len = log_head_len + msgf_len + 1;
    char *buf = malloc(total_len);
    strncpy(buf, log_head, log_head_len);
    strncpy(buf + log_head_len, msg_formatted, msgf_len);
    buf[total_len - 1] = '\0';

    fprintf(OUTFILE, "%s\n", buf);

    free(msg_formatted);
    free(log_head);
    free(buf);
}

void logga_trace(char *msg, ...)
{
    if (logga_level > LOGGA_TRACE) return;
    va_list ap;
    va_start(ap, msg);
    logga("TRACE", msg, ap);
    va_end(ap);
}

void logga_debug(char *msg, ...)
{
    if (logga_level > LOGGA_DEBUG) return;
    va_list ap;
    va_start(ap, msg);
    logga("DEBUG", msg, ap);
    va_end(ap);
}

void logga_info(char *msg, ...)
{
    if (logga_level > LOGGA_INFO) return;
    va_list ap;
    va_start(ap, msg);
    logga("INFO", msg, ap);
    va_end(ap);
}

void logga_warn(char *msg, ...)
{
    if (logga_level > LOGGA_WARN) return;
    va_list ap;
    va_start(ap, msg);
    logga("WARNING", msg, ap);
    va_end(ap);
}

void logga_error(char *msg, ...)
{
    va_list ap;
    va_start(ap, msg);
    logga("ERROR", msg, ap);
    va_end(ap);
}
