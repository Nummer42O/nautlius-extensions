#include "logging.h"

#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>


#ifdef NELOG_USE_COLOR
#define NELOG_COLOR_TRACE "\e[0;36m"
#define NELOG_COLOR_DEBUG "\e[0;34m"
#define NELOG_COLOR_INFO  "\e[0;32m"
#define NELOG_COLOR_WARN  "\e[0;33m"
#define NELOG_COLOR_ERROR "\e[0;31m"
#define NELOG_COLOR_FATAL "\e[0;35m"
#define NELOG_NO_COLOR    "\e[0m"
#else
#define NELOG_COLOR_TRACE ""
#define NELOG_COLOR_DEBUG ""
#define NELOG_COLOR_INFO  ""
#define NELOG_COLOR_WARN  ""
#define NELOG_COLOR_ERROR ""
#define NELOG_COLOR_FATAL ""
#define NELOG_NO_COLOR    ""
#endif // defined(NELOG_USE_COLOR)

const char *nelog_level_to_string(loglevel_t logLevel)
{
  switch (logLevel)
  {
    case NELOG_TRACE:
      return NELOG_COLOR_TRACE  "TRACE" NELOG_NO_COLOR;
    case NELOG_DEBUG:
      return NELOG_COLOR_DEBUG  "DEBUG" NELOG_NO_COLOR;
    case NELOG_INFO:
      return NELOG_COLOR_INFO   "INFO"  NELOG_NO_COLOR;
    case NELOG_WARN:
      return NELOG_COLOR_WARN   "WARN"  NELOG_NO_COLOR;
    case NELOG_ERROR:
      return NELOG_COLOR_ERROR  "ERROR" NELOG_NO_COLOR;
    case NELOG_FATAL:
      return NELOG_COLOR_FATAL  "FATAL" NELOG_NO_COLOR;
    default:
      return NULL;
  }
}

loglevel_t nelog_globalLogLevel = NELOG_NULL_OPT;
void nelog_set_level(loglevel_t globalLogLevel)
{
  nelog_globalLogLevel = globalLogLevel;
}

#define NELOG_TIMESTAMP_SIZE 26ul
void nelog_print(loglevel_t logLevel, const char *functionName, const char *printFormat, ...)
{
  time_t timer = time(NULL);
  struct tm *tm_info = localtime(&timer);

  char timestamp[NELOG_TIMESTAMP_SIZE];
  strftime(
    timestamp,
    NELOG_TIMESTAMP_SIZE, "%Y-%m-%d %H:%M:%S",
    tm_info
  );

  const char *logLevelName = nelog_level_to_string(logLevel);
  assert(logLevelName);

  size_t formatSize = \
    NELOG_TIMESTAMP_SIZE  + 3ul \
    + strlen(logLevelName)    + 3ul \
    + strlen(functionName)    + 2ul \
    + strlen(printFormat)     + 1ul;
  char *concatPrintFormat = malloc(formatSize);

  sprintf(
    concatPrintFormat, "[%s] %s - %s: %s",
    timestamp, logLevelName, functionName, printFormat
  );

  va_list args;
  va_start(args, concatPrintFormat);
  vprintf(concatPrintFormat, args);
  va_end(args);

  free(concatPrintFormat);
}
