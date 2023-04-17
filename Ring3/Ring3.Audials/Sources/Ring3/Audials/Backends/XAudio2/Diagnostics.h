#if !defined(RING3_AUDIALS_BACKENDS_XAUDIO2_DIAGNOSTICS_H_INCLUDED)
#define RING3_AUDIALS_BACKENDS_XAUDIO2_DIAGNOSTICS_H_INCLUDED

#include "Ring3/Audials/Configuration.h"

#if Ring3_Audials_Backend == Ring3_Audials_Backend_XAudio2

// For "fprintf" and "stderr".
#include <stdio.h>

// For "CoInitializeEx" and others.
#include <Objbase.h>

// For "XAudio2Create" and others.
#include <Xaudio2.h>

void
_ERROR1
  (
    char const* file,
    int line,
    HRESULT error,
    char const* format,
    ...
  );

#define _ERROR(error, ...)  _ERROR1(__FILE__, __LINE__, error, __VA_ARGS__);

#endif // #if Ring3_Audials_Backend == Ring3_Audials_Backend_XAudio2

#endif // RING3_AUDIALS_BACKENDS_XAUDIO2_DIAGNOSTICS_H_INCLUDED
