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

/** Set log outfile. */
void logga_set_outfile(FILE *);
/** Set log level; default is LOGGA_INFO. */
void logga_set_level(logga_level_t level);

void logga_trace(char *msg, ...);
void logga_debug(char *msg, ...);
void logga_info(char *msg, ...);
void logga_warn(char *msg, ...);
void logga_error(char *msg, ...);

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
