// Copyright (c) 2022 Michael Heilmann. All rights reserved.
// XAudio 2 Demo.
// See https://docs.microsoft.com/en-us/windows/win32/xaudio2/ for more information on XAudio 2.

#include "Ring3/Audials/_Include.h"

#include <stddef.h>

#include <stdbool.h>

static const bool MKX_AUDIALS_DEMO_XAUDIO2_DEBUG_ENABLED = true;

// For sin().
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Fior int16_t and INT16_MAX.
#include <stdint.h>

// For CoInitializeEx().
#include <Objbase.h>

// For XAudio2Create().
#include <Xaudio2.h>

// For XAudio2Create.
#pragma comment(lib, "Xaudio2.lib")

static IXAudio2* g_pxaudio2 = NULL;

static IXAudio2MasteringVoice* g_pMasteringVoice = NULL;

static IXAudio2SourceVoice* g_sourceVoice = NULL;

static Ring3_Audials_PcmBuffer* g_pcmBuffer = NULL;

#include <stdio.h>

static void
logXaudio2Result
  (
    HRESULT hr
  )
{
  switch (hr) {
    case XAUDIO2_E_INVALID_CALL:
      fprintf(stderr, "XAudio 2 invalid call\n");
      break;
    case XAUDIO2_E_XMA_DECODER_ERROR:
      fprintf(stderr, "XAudio 2 XMA decoder error\n");
      break;
    case XAUDIO2_E_XAPO_CREATION_FAILED:
      fprintf(stderr, "XAudio 2 XAPO creation failed\n");
      break;
    case XAUDIO2_E_DEVICE_INVALIDATED:
      fprintf(stderr, "XAudio 2 device invalidated\n");
      break;
    default:
      fprintf(stderr, "XAudio 2 unknown error\n");
      break;
  };
}

void
Machine_Audio_Demo_startup
  (
  )
{
  HRESULT hr;

  // (1)
  hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
  if (FAILED(hr)) {
    logXaudio2Result(hr);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }

  // (2)
  if (FAILED(hr = XAudio2Create(&g_pxaudio2, 0, XAUDIO2_DEFAULT_PROCESSOR))) {
    // (1)
    CoUninitialize();
    logXaudio2Result(hr);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }

  if (MKX_AUDIALS_DEMO_XAUDIO2_DEBUG_ENABLED) {
    // To see the trace output, you need to view ETW logs for this application:
    //    Go to Control Panel, Administrative Tools, Event Viewer.
    //    View->Show Analytic and Debug Logs.
    //    Applications and Services Logs / Microsoft / Windows / XAudio2.
    //    Right click on Microsoft Windows XAudio2 debug logging, Properties,
    //    then Enable Logging, and hit OK 
    XAUDIO2_DEBUG_CONFIGURATION debug = {0};
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
    logXaudio2Result(hr);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
}

void
Machine_Audio_Demo_shutdown
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

static void
createVoice
  (
  )
{
  Ring3_Audials_PcmDescriptor* pcmDescriptor = Ring3_Audials_PcmDescriptor_create(2, 44100, 16);
  g_pcmBuffer = Ring3_Audials_PcmBuffer_create(10, pcmDescriptor, Mkx_Audials_GeneratorId_Sine220);

  HRESULT hr;

  WAVEFORMATEX wfmt = {0};
  
  wfmt.cbSize = 0;
  wfmt.wFormatTag = WAVE_FORMAT_PCM;
  wfmt.nChannels = g_pcmBuffer->pcmDescriptor->numberOfChannels;
  wfmt.nSamplesPerSec = g_pcmBuffer->pcmDescriptor->samplesPerSecondPerChannel;
  wfmt.wBitsPerSample = g_pcmBuffer->pcmDescriptor->bitsPerSample;
  wfmt.nBlockAlign = (wfmt.nChannels * wfmt.wBitsPerSample) / 8;
  wfmt.nAvgBytesPerSec = wfmt.nSamplesPerSec * wfmt.nBlockAlign;

  if (FAILED(hr = g_pxaudio2->lpVtbl->CreateSourceVoice(g_pxaudio2, &g_sourceVoice, &wfmt, 0, 1.0f, NULL, NULL, NULL))) {
    logXaudio2Result(hr);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }


  XAUDIO2_BUFFER buffer = {0};
  buffer.pAudioData = (BYTE const*)g_pcmBuffer->bytes;
  buffer.AudioBytes = g_pcmBuffer->numberOfBytes;
  buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

  if (FAILED(hr = g_sourceVoice->lpVtbl->SubmitSourceBuffer(g_sourceVoice, &buffer, NULL))) {
    g_sourceVoice->lpVtbl->DestroyVoice(g_sourceVoice);
    g_sourceVoice = NULL;
    logXaudio2Result(hr);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }

  if (FAILED(hr = g_sourceVoice->lpVtbl->Start(g_sourceVoice, 0, 0))) {
    g_sourceVoice->lpVtbl->DestroyVoice(g_sourceVoice);
    g_sourceVoice = NULL;
    logXaudio2Result(hr);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }

    // Let the sound play
  BOOL isRunning = TRUE;
  while (SUCCEEDED(hr) && isRunning) {
    XAUDIO2_VOICE_STATE state;
    g_sourceVoice->lpVtbl->GetState(g_sourceVoice, &state, 0);
    isRunning = (state.BuffersQueued > 0) != 0;

    Sleep(10);
  }
}

static void
destroyVoice
  (
  )
{
  if (g_sourceVoice) {
    g_sourceVoice->lpVtbl->DestroyVoice(g_sourceVoice);
    g_sourceVoice = NULL;
  }
  if (g_pcmBuffer) {
    g_pcmBuffer = NULL;
  }
}

static void main1() {
  Ring2_JumpTarget jumpTarget;
  Machine_Audio_Demo_startup();

  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    createVoice();
    Ring2_popJumpTarget();
    destroyVoice();
    Machine_Audio_Demo_shutdown();
  } else {
    Ring2_popJumpTarget();
    destroyVoice();
    Machine_Audio_Demo_shutdown();
    Ring2_jump();
  }
}

int
main
  (
    int argc,
    char** argv
  )
{
  int result = EXIT_SUCCESS;
  if (Ring2_Context_startup()) {
    return result;
  }
  Ring2_JumpTarget jumpTarget1;
  Ring2_pushJumpTarget(&jumpTarget1);
  if (!setjmp(jumpTarget1.environment)) {
    Machine_Audio_Demo_startup();
    Ring2_popJumpTarget();
  } else {
    Ring2_popJumpTarget();
    Ring2_Context_shutdown();
    result = EXIT_FAILURE;
    return result;
  }
  Ring2_pushJumpTarget(&jumpTarget1);
  if (!setjmp(jumpTarget1.environment)) {
    createVoice();
    Ring2_popJumpTarget();
  } else {
    Ring2_popJumpTarget();
    Ring2_Context_shutdown();
    result = EXIT_FAILURE;
    return result;
  }
  destroyVoice();
  Machine_Audio_Demo_shutdown();
  Ring2_Context_shutdown();
  return result;
}
