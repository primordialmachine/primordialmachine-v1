#include "Ring3/Audials/Backends/OpenAL/Diagnostics.h"

#if Ring3_Audials_Backend == Ring3_Audials_Backend_OpenAL

// For "va_list", "va_start", "va_end".
#include <stdarg.h>

static inline char const*
_toString
  (
    ALenum error
  )
{
  switch (error) {
  case AL_NO_ERROR: {
    static char const* String = "AL_NO_ERROR";
    return String;
  }
  break;
  case AL_INVALID_NAME: {
    static char const* String = "AL_INVALID_NAME";
    return String;
  }
  break;
  case AL_INVALID_ENUM: {
    static char const* String = "AL_INVALID_ENUM";
    return String;
  }
  break;
  case AL_INVALID_VALUE: {
    static char const* String = "AL_INVALID_VALUE";
    return String;
  }
  break;
  case AL_INVALID_OPERATION: {
    static char const* String = "AL_INVALID_OPERATION";
    return String;
  }
  break;
  case AL_OUT_OF_MEMORY: {
    static char const* String = "AL_OUT_OF_MEMORY";
    return String;
  }
  break;
  default: {
    static char const* String = "<UNKNOWN>";
    return String;
  }
  break;
  };
}

void
_ERROR1
  (
    char const* file,
    int line,
    ALenum error,
    char const *format,
    ...
  )
{
  fprintf(stderr, "%s:%d: ", __FILE__, __LINE__);
  fprintf(stderr, " OpenAL error: %s: ", _toString(error));
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
}
// Intentionally empty.

#endif // #if Ring3_Audials_Demo_Backend == Ring3_Audials_Demo_Backend_OpenAL
