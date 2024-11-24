#ifndef NELOG_H
#define NELOG_H


typedef enum {
  NELOG_TRACE, NELOG_DEBUG, NELOG_INFO,
  NELOG_WARN, NELOG_ERROR, NELOG_FATAL,

  NELOG_NULL_OPT
} loglevel_t;


static loglevel_t nelog_globalLogLevel = NELOG_NULL_OPT;


const char *nelog_level_to_string(
  loglevel_t  logLevel
);

void nelog_set_level(
  loglevel_t globalLogLevel
);

void nelog_print(
  loglevel_t  logLevel,
  const char *functionName,
  const char *printFormat,
  ...
);


#ifndef __FUNCTION_NAME__
  #ifdef win32
    #define __FUNCTION_NAME__ __FUNCTION__
  #else
    #define __FUNCTION_NAME__ __func__
  #endif
#endif // !defined(__FUNCTION_NAME__)

#define nelog_log(logLevel, ...)        \
  if (logLevel >= nelog_globalLogLevel) \
  {                                     \
    nelog_print(                        \
      logLevel,                         \
      __FUNCTION_NAME__,                \
      __VA_ARGS__                       \
    );                                  \
  }

#define nelog_trace(...) nelog_log(NELOG_TRACE, __VA_ARGS__)

#define nelog_debug(...) nelog_log(NELOG_DEBUG, __VA_ARGS__)

#define nelog_info(...)  nelog_log(NELOG_INFO,  __VA_ARGS__)

#define nelog_warn(...)  nelog_log(NELOG_WARN,  __VA_ARGS__)

#define nelog_error(...) nelog_log(NELOG_ERROR, __VA_ARGS__)

#define nelog_fatal(...) nelog_log(NELOG_FATAL, __VA_ARGS__)

#endif // !defined(NELOG_H)