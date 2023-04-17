#if !defined(RING_AUDIALS_BACKENDS_XAUDIO2_SOURCEVOICE_H_INCLUDED)
#define RING_AUDIALS_BACKENDS_XAUDIO2_SOURCEVOICE_H_INCLUDED

#include "Ring3/Audials/Configuration.h"

#if Ring3_Audials_Backend == Ring3_Audials_Backend_XAudio2

#include "Ring3/Audials/Backends/XAudio2/Diagnostics.h"
#include "Ring3/Audials/Backends/PcmDescriptor.h"

// For "fprintf" and "stderr".
#include <stdio.h>
// For "assert".
#include <assert.h>
// for "bool", "true", "false".
#include <stdbool.h>
// For "CoInitializeEx" and others.
#include <Objbase.h>
// For "XAudio2Create" and others.
#include <Xaudio2.h>

// The connection of a XAUDIO2_BUFFER to an arbitrary XAudio2Source.
typedef struct _SourceVoice {
  int rc;
  IXAudio2VoiceCallbackVtbl callbacksVtbl;
  IXAudio2VoiceCallback callbacks;
  IXAudio2SourceVoice* sourceVoice;
  _PcmDescriptor pcmDescriptor;
} _SourceVoice;

int
_SourceVoice_construct
  (
    _SourceVoice* sourceVoice,
    IXAudio2* xaudio2,
    _PcmDescriptor const* pcmDescriptor
  );

int
_SourceVoice_create
  (
    _SourceVoice** sourceVoice,
    IXAudio2* xaudio2,
    _PcmDescriptor const* pcmDescriptor
  );

void
_SourceVoice_destruct
  (
    _SourceVoice* sourceVoice
  );

void
_SourceVoice_destroy
  (
    _SourceVoice* sourceVoice
  );

void
_SourceVoice_ref
  (
    _SourceVoice* sourceVoice
  );

void
_SourceVoice_unref
  (
    _SourceVoice* sourceVoice
  );

int
_SourceVoid_isPlaying
  (
    bool* isPlaying,
    _SourceVoice* sourceVoice
  );

#endif

#endif // RING_AUDIALS_BACKENDS_XAUDIO2_SOURCEVOICE_H_INCLUDED
