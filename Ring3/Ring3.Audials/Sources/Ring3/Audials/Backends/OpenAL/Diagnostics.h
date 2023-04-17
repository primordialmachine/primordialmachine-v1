#if !defined(RING3_AUDIALS_BACKENDS_OPENAL_DIAGNOSTICS_H_INCLUDED)
#define RING3_AUDIALS_BACKENDS_OPENAL_DIAGNOSTICS_H_INCLUDED

#include "Ring3/Audials/Configuration.h"

#if Ring3_Audials_Backend == Ring3_Audials_Backend_OpenAL

// For "fprintf" and "stderr".
#include <stdio.h>

#include <AL/al.h>

void
_ERROR1
  (
    char const* file,
    int line,
    ALenum error,
    char const* format,
    ...
  );

#define _ERROR(error, ...) \
  _ERROR1(__FILE__, __LINE__, error, __VA_ARGS__);

#endif // #if Ring3_Audials_Backend == Ring3_Audials_Backend_OpenAL

#endif // RING3_AUDIALS_BACKENDS_OPENAL_DIAGNOSTICS_H_INCLUDED
