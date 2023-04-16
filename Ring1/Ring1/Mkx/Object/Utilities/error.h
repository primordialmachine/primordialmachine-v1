
#include <stdarg.h> // For va_list, va_start and va_end.
#include <stdio.h> // For fprintf and stderr.

static inline void debug_f(const char *format, ...);

static inline void debug_fv(const char* format, va_list arguments);

/// @brief Report a debug information.
/// @param format a printf-style format string.
/// @param ... The arguments.
static inline void debug_f(const char* format, ...)
{
#if defined(_DEBUG)
  va_list arguments;
  va_start(arguments, format);
  debug_fv(format, arguments);
  va_end(arguments);
#endif
}

/// @brief Report an debug information.
/// @param format a printf-style format string.
/// @param arguments The arguments.
static inline void debug_fv(const char* format, va_list arguments)
{
#if defined(_DEBUG)
  vfprintf(stderr, format, arguments);
#endif
}

static inline void error_f(const char* format, ...);

static inline void error_fv(const char* format, va_list arguments);

/// @brief Report an error.
/// @param format a printf-style format string.
/// @param ... The arguments.
static inline void error_f(const char *format, ...)
{
  va_list arguments;
  va_start(arguments, format);
  error_fv(format, arguments);
  va_end(arguments);
}

/// @brief Report an error.
/// @param format a printf-style format string.
/// @param arguments The arguments.
static inline void error_fv(const char *format, va_list arguments)
{
  vfprintf(stderr, format, arguments);
}
