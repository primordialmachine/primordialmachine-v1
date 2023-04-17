/// @file Ring3/Audials/Demo/Main.c
/// @copyright Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
/// @brief Demo playing a 220hz sine wave.

#include "Ring3/Audials/_Include.h"

#include <stdlib.h>

#include "Ring3/Audials/_Include.h"

// For "Sleep".
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

static Ring3_Audials_PcmBuffer* g_pcmBuffer = NULL;

static _Source* g_source = NULL;

static _Buffer* g_buffer = NULL;

void
createVoice
  (
  )
{
  Ring3_Audials_PcmDescriptor* pcmDescriptor = Ring3_Audials_PcmDescriptor_create(2, 44100, 16);
  g_pcmBuffer = Ring3_Audials_PcmBuffer_create(10, pcmDescriptor, Mkx_Audials_GeneratorId_Sine220);

  if (_Source_create(&g_source)) {
    Ring2_jump();
  }
  _PcmDescriptor _pcmDescriptor;
  _pcmDescriptor.bitsPerSample = pcmDescriptor->bitsPerSample;
  _pcmDescriptor.numberOfChannels = pcmDescriptor->numberOfChannels;
  _pcmDescriptor.samplesPerSecondPerChannel = pcmDescriptor->samplesPerSecondPerChannel;
  if (_Buffer_create(&g_buffer, &_pcmDescriptor, g_pcmBuffer->bytes, g_pcmBuffer->numberOfBytes)) {
    _Source_unref(g_source);
    g_source = NULL;
    Ring2_jump();
  }

  if (_Source_attach(g_source, g_buffer)) {
    _Buffer_unref(g_buffer);
    g_buffer = NULL;
    _Source_unref(g_source);
    g_source = NULL;
    Ring2_jump();
  }

  if (_Source_play(g_source)) {
    _Buffer_unref(g_buffer);
    g_buffer = NULL;
    _Source_unref(g_source);
    g_source = NULL;
    Ring2_jump();
  }

  // Let the sound play.
  bool isPlaying = true;
  while (Ring1_Status_Success == Ring1_Status_get() && isPlaying) {
    if (_Source_isPlaying(&isPlaying, g_source)) {
      break;
    }
    Sleep(10);
  }

  if (Ring1_Status_Success != Ring1_Status_get()) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
}

void
destroyVoice
  (
  )
{
  if (g_source) {
    _Source_unref(g_source);
    g_source = NULL;
  }
  if (g_buffer) {
    _Buffer_unref(g_buffer);
    g_buffer = NULL;
  }
  if (g_pcmBuffer) {
    g_pcmBuffer = NULL;
  }
}

void
Ring3_Audials_Demo_startup
  (
  )
{
  if (_startup()) {
    Ring2_jump();
  }
}

void
Ring3_Audials_Demo_shutdown
  (
  )
{
  _shutdown();
}

static void
main1
  (
  )
{
  Ring2_JumpTarget jumpTarget;
  Ring3_Audials_Demo_startup();

  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    createVoice();
    Ring2_popJumpTarget();
    destroyVoice();
    Ring3_Audials_Demo_shutdown();
  } else {
    Ring2_popJumpTarget();
    destroyVoice();
    Ring3_Audials_Demo_shutdown();
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
    Ring3_Audials_Demo_startup();
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
  Ring3_Audials_Demo_shutdown();
  Ring2_Context_shutdown();
  return result;
}
