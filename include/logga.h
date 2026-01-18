#ifndef LOGGA_H
#define LOGGA_H

#include <stdio.h>

typedef enum {
    LOGGA_TRACE = 0,
    LOGGA_DEBUG,
    LOGGA_INFO,
    LOGGA_WARN,
    LOGGA_ERROR,
} logga_level_t;

const char *logga_lvtostr(logga_level_t level);

typedef struct {
    char *name;
    logga_level_t level;
    FILE *outfile;
} logga_t;

/** Set defaults. */
void logga_init(logga_t *logga);

void logga_trace(logga_t *logga, char *msg, ...);
void logga_debug(logga_t *logga, char *msg, ...);
void logga_info(logga_t *logga, char *msg, ...);
void logga_warn(logga_t *logga, char *msg, ...);
void logga_error(logga_t *logga, char *msg, ...);

#ifdef NO_LOGGA_PREFIX
#define TRACE LOGGA_TRACE 
#define DEBUG LOGGA_DEBUG
#define INFO  LOGGA_INFO
#define WARN  LOGGA_WARN
#define ERROR LOGGA_ERROR
#define trace logga_trace 
#define debug logga_debug
#define info  logga_info
#define warn  logga_warn
#define error logga_error
#endif

#endif  // LOGGA_H
