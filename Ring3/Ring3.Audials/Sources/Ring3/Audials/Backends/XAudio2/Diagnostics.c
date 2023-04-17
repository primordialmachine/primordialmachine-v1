#include "Ring3/Audials/Backends/XAudio2/Diagnostics.h"

#if Ring3_Audials_Backend == Ring3_Audials_Backend_XAudio2

static inline char const*
_toString
  (
    HRESULT status
  )
{
  switch (status) {
  case XAUDIO2_E_INVALID_CALL: {
    static char const* String = "XAudio 2 invalid call";
    return String;
  } break;
  case XAUDIO2_E_XMA_DECODER_ERROR: {
    static char const* String = "XAudio 2 XMA decoder error";
    return String;
  } break;
  case XAUDIO2_E_XAPO_CREATION_FAILED: {
    static char const* String = "XAudio 2 XAPO creation failed";
    return String;
  } break;
  case XAUDIO2_E_DEVICE_INVALIDATED: {
    static char const* String = "XAudio 2 device invalidated";
    return String;
  } break;
  default: {
    static char const* String = "XAudio 2 unknown error";
    return String;
  } break;
  };
}

void
_ERROR1
  (
    char const* file,
    int line,
    HRESULT error,
    char const* format,
    ...
  )
{
  fprintf(stderr, "%s:%d: ", __FILE__, __LINE__);
  fprintf(stderr, " XAudio2 error: %s: ", _toString(error));
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
}

#endif // #if Ring3_Audials_Backend == Ring3_Audials_Backend_XAudio2
