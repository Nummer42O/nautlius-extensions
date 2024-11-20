#ifndef NELOGGING_H
#define NELOGGING_H


typedef enum {
  NELOGGING_TRACE, NELOGGING_DEBUG, NELOGGING_INFO,
  NELOGGING_WARN, NELOGGING_ERROR, NELOGGING_FATAL,

  NELOGGING_NULL_OPT
} loglevel_t;

const char *nelogging_level_to_string(
  loglevel_t  logLevel
);

void nelogging_print(
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

#define nelogging_log(logLevel, ...)  \
  if (true)                           \
  {                                   \
    nelogging_print(                  \
      logLevel,                       \
      __FUNCTION_NAME__,              \
      __VA_ARGS__                     \
    );                                \
  }

#define log_trace(...) nelogging_print(NELOGGING_TRACE, __FUNCTION_NAME__, __VA_ARGS__)

#define log_debug(...) nelogging_print(NELOGGING_DEBUG, __FUNCTION_NAME__, __VA_ARGS__)

#define log_info(...)  nelogging_print(NELOGGING_INFO,  __FUNCTION_NAME__, __VA_ARGS__)

#define log_warn(...)  nelogging_print(NELOGGING_WARN,  __FUNCTION_NAME__, __VA_ARGS__)

#define log_error(...) nelogging_print(NELOGGING_ERROR, __FUNCTION_NAME__, __VA_ARGS__)

#define log_fatal(...) nelogging_print(NELOGGING_FATAL, __FUNCTION_NAME__, __VA_ARGS__)

#endif // !defined(NELOGGING_H)