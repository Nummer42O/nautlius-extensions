#include "logging.h"

#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>


#ifdef NELOGGING_USE_COLOR
#define NELOGGING_COLOR_TRACE "\e[0;36m"
#define NELOGGING_COLOR_DEBUG "\e[0;34m"
#define NELOGGING_COLOR_INFO  "\e[0;32m"
#define NELOGGING_COLOR_WARN  "\e[0;33m"
#define NELOGGING_COLOR_ERROR "\e[0;31m"
#define NELOGGING_COLOR_FATAL "\e[0;35m"
#define NELOGGING_NO_COLOR    "\e[0m"
#else
#define NELOGGING_COLOR_TRACE ""
#define NELOGGING_COLOR_DEBUG ""
#define NELOGGING_COLOR_INFO  ""
#define NELOGGING_COLOR_WARN  ""
#define NELOGGING_COLOR_ERROR ""
#define NELOGGING_COLOR_FATAL ""
#define NELOGGING_NO_COLOR    ""
#endif // defined(NELOGGING_USE_COLOR)

const char *nelogging_level_to_string(loglevel_t logLevel)
{
  switch (logLevel)
  {
    case NELOGGING_TRACE:
      return NELOGGING_COLOR_TRACE  "TRACE" NELOGGING_NO_COLOR;
    case NELOGGING_DEBUG:
      return NELOGGING_COLOR_DEBUG  "DEBUG" NELOGGING_NO_COLOR;
    case NELOGGING_INFO:
      return NELOGGING_COLOR_INFO   "INFO"  NELOGGING_NO_COLOR;
    case NELOGGING_WARN:
      return NELOGGING_COLOR_WARN   "WARN"  NELOGGING_NO_COLOR;
    case NELOGGING_ERROR:
      return NELOGGING_COLOR_ERROR  "ERROR" NELOGGING_NO_COLOR;
    case NELOGGING_FATAL:
      return NELOGGING_COLOR_FATAL  "FATAL" NELOGGING_NO_COLOR;
    default:
      return NULL;
  }
}

#define NELOGGING_TIMESTAMP_SIZE 26ul
void nelogging_print(loglevel_t logLevel, const char *functionName, const char *printFormat, ...)
{
  time_t timer = time(NULL);
  struct tm *tm_info = localtime(&timer);

  char timestamp[NELOGGING_TIMESTAMP_SIZE];
  strftime(
    timestamp,
    NELOGGING_TIMESTAMP_SIZE, "%Y-%m-%d %H:%M:%S",
    tm_info
  );

  const char *logLevelName = nelogging_level_to_string(logLevel);
  assert(logLevelName);

  size_t formatSize = \
    NELOGGING_TIMESTAMP_SIZE  + 3ul \
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
