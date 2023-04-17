/// @file Ring3/Audials/Backends/XAudio2/XAudio2.c
/// @copyright Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
/// @brief XAudio2 Backed.
/// See https://docs.microsoft.com/en-us/windows/win32/xaudio2/ for more information on XAudio 2.

#include "Ring3/Audials/Backends/XAudio2/XAudio2.h"

#if Ring3_Audials_Backend == Ring3_Audials_Backend_XAudio2

#include "Ring3/Audials/Backends/XAudio2/SourceVoice.h"

// For "sin".
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// For "int16_t" and "INT16_MAX".
#include <stdint.h>

// For "assert".
#include <assert.h>

static const bool g_debugEnabled = true;

// For "CoInitializeEx" and others.
#include <Objbase.h>

// For "XAudio2Create" and others.
#include <Xaudio2.h>
#pragma comment(lib, "Xaudio2.lib")

static IXAudio2* g_pxaudio2 = NULL;

static IXAudio2MasteringVoice* g_pMasteringVoice = NULL;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct _Buffer {
  int rc; /// The reference count of this buffer.
  void* p;
  uint64_t n;
  _PcmDescriptor pcmDescriptor;
  XAUDIO2_BUFFER impl;
};

static void
_Buffer_destroy
  (
    _Buffer* buffer
  );

static void
_Buffer_destroy
  (
    _Buffer* buffer
  )
{
  assert(NULL != buffer);
  assert(0 == buffer->rc);
  free(buffer->p);
  buffer->p = NULL;
  buffer->n = 0;
  free(buffer);
}

int
_Buffer_create
  (
    _Buffer** buffer,
    _PcmDescriptor const* pcmDescriptor,
    void *p,
    size_t n
  )
{
  _Buffer *buffer1 = malloc(sizeof(_Buffer));
  if (!buffer1) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return 1;
  }
  buffer1->pcmDescriptor = *pcmDescriptor;
  buffer1->p = malloc(n);
  if (!buffer1->p) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    free(buffer1);
    buffer1 = NULL;
    return 1;
  }
  memcpy(buffer1->p, p, n);
  buffer1->n = n;
  memset(&buffer1->impl, 0, sizeof(buffer1->impl));
  buffer1->impl.pAudioData = (BYTE const*)buffer1->p;
  buffer1->impl.AudioBytes = buffer1->n;
  buffer1->impl.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
  buffer1->impl.pContext = buffer1;
  buffer1->rc = 1;
  *buffer = buffer1;
  return 0;
}

void
_Buffer_ref
  (
    _Buffer* buffer
  )
{
  buffer->rc++;
}

void
_Buffer_unref
  (
    _Buffer* buffer
  )
{
  if (0 == --buffer->rc) {
    _Buffer_destroy(buffer);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct _Source {
  int rc;
  _SourceVoice* sourceVoice;
};

int
_Source_create
  (
    _Source** source
  )
{
  _Source* source1 = malloc(sizeof(_Source));
  if (!source1) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return 1;
  }
  memset(source1, 0, sizeof(_Source));
  //
  source1->rc = 1;
  //
  *source = source1;
  //
  return 0;
}

void
_Source_destroy
  (
    _Source* source
  )
{
  assert(NULL != source);
  assert(0 == source->rc);
  if (source->sourceVoice) {
    _SourceVoice_unref(source->sourceVoice);
    source->sourceVoice = NULL;
  }
  free(source);
}

void
_Source_ref
  (
    _Source* source
  )
{ source->rc++; }

void
_Source_unref
  (
    _Source* source
  )
{
  if (0 == --source->rc) {
    _Source_destroy(source);
  }
}

int
_Source_attach
  (
    _Source* source,
    _Buffer* buffer
  )
{
  if (source->sourceVoice) {
    _SourceVoice_unref(source->sourceVoice);
    source->sourceVoice = NULL;
  }
  if (_SourceVoice_create(&source->sourceVoice, g_pxaudio2, &buffer->pcmDescriptor)) {
    return 1;
  }
  HRESULT hr;
  if (FAILED(hr = source->sourceVoice->sourceVoice->lpVtbl->SubmitSourceBuffer(source->sourceVoice->sourceVoice,
                                                                               &buffer->impl, NULL))) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    _ERROR(hr, "unable to submit XAudio2 source buffer\n");
    return 1;
  }
  _Buffer_ref(buffer); // We submitted the buffer, hence increment its reference count by 1.
  return 0;
}

int
_Source_play
  (
    _Source* source
  )
{
  if (!source) {
    return 1;
  }
  if (!source->sourceVoice) {
    return 1;
  }
  HRESULT hr;
  if (FAILED(hr = source->sourceVoice->sourceVoice->lpVtbl->Start(source->sourceVoice->sourceVoice, 0, 0))) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    _ERROR(hr, "unable to start XAudio2 source voice\n");
    return 1;
  }
  return 0;
}

int
_Source_isPlaying
  ( 
    bool *isPlaying,
    _Source* source
  )
{
  return _SourceVoid_isPlaying(isPlaying, source->sourceVoice);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int
_startup
  (
  )
{
  HRESULT hr;

  // (1)
  hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
  if (FAILED(hr)) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    _ERROR(hr, "unable to initialize COM\n");
    return 1;
  }

  // (2)
  if (FAILED(hr = XAudio2Create(&g_pxaudio2, 0, XAUDIO2_DEFAULT_PROCESSOR))) {
    // (1)
    CoUninitialize();
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    _ERROR(hr, "unable to initialize XAudio2\n");
    return 1;
  }

  if (g_debugEnabled) {
    // To see the trace output, you need to view ETW logs for this application:
    //    Go to Control Panel, Administrative Tools, Event Viewer.
    //    View->Show Analytic and Debug Logs.
    //    Applications and Services Logs / Microsoft / Windows / XAudio2.
    //    Right click on Microsoft Windows XAudio2 debug logging, Properties,
    //    then Enable Logging, and hit OK
    XAUDIO2_DEBUG_CONFIGURATION debug = { 0 };
    debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
    debug.BreakMask = XAUDIO2_LOG_ERRORS;
    g_pxaudio2->lpVtbl->SetDebugConfiguration(g_pxaudio2, &debug, 0);
  }

  // (3)
  if (FAILED(hr = g_pxaudio2->lpVtbl->CreateMasteringVoice(g_pxaudio2,
                                                           &g_pMasteringVoice,
                                                           XAUDIO2_DEFAULT_CHANNELS,
                                                           XAUDIO2_DEFAULT_SAMPLERATE,
                                                           0,
                                                           NULL,
                                                           NULL,
                                                           AudioCategory_GameMedia))) {
    // (2)
    if (g_pxaudio2) {
      g_pxaudio2->lpVtbl->Release(g_pxaudio2);
      g_pxaudio2 = NULL;
    }
    // (1)
    CoUninitialize();
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    _ERROR(hr, "unable to create XAudio2 mastering voice\n");
    return 1;
  }
  return 0;
}

void
_shutdown
  (
  )
{
  // (3)
  if (g_pMasteringVoice) {
    g_pMasteringVoice->lpVtbl->DestroyVoice(g_pMasteringVoice);
    g_pMasteringVoice = NULL;
  }

  // (2)
  if (g_pxaudio2) {
    g_pxaudio2->lpVtbl->Release(g_pxaudio2);
    g_pxaudio2 = NULL;
  }

  // (1)
  CoUninitialize();
}

#endif
