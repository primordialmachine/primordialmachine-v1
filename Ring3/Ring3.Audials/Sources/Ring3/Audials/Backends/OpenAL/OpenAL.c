/// @file Ring3/Audials/Backends/OpenAL/OpenAL.c
/// @copyright Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
/// @brief OpenAL Backend.
/// See https://www.openal-soft.org/ for more information on OpenAL.

#include "Ring3/Audials/Backends/OpenAL/OpenAL.h"

#if Ring3_Audials_Backend == Ring3_Audials_Backend_OpenAL

#include "Ring3/Audials/Backends/OpenAL/Diagnostics.h"

// For sin().
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// For "int16_t" and "INT16_MAX".
#include <stdint.h>

// For "assert".
#include <assert.h>

// For malloc, realloc, and free.
#include <malloc.h>
// For memcpy.
#include <memory.h>

#pragma comment(lib, "openal32.lib")

#include <AL/alc.h>
#include <AL/al.h>
#include <AL/alext.h>

/// The OpenAL context.
static ALCcontext* g_context;

/// The OpenAL device.
static ALCdevice* g_device;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct _Buffer {
  int rc; /// The reference count of this buffer.
  void* p;
  uint64_t n;
  _PcmDescriptor pcmDescriptor;
  ALuint id;
};

static int
_Buffer_upload
  (
    _Buffer* buffer
  );

static void
_Buffer_destroy
  (
    _Buffer* buffer
  );

static int
_Buffer_upload
  (
    _Buffer* buffer
  )
{
  ALenum error;
  if (buffer->pcmDescriptor.numberOfChannels == 2) {
    if (buffer->pcmDescriptor.bitsPerSample == 16)
      alBufferData(buffer->id, AL_FORMAT_STEREO16, buffer->p, buffer->n, buffer->pcmDescriptor.samplesPerSecondPerChannel);
    else if (buffer->pcmDescriptor.bitsPerSample == 8)
      alBufferData(buffer->id, AL_FORMAT_STEREO8, buffer->p, buffer->n, buffer->pcmDescriptor.samplesPerSecondPerChannel);
    else {
      return 1;
    }
  } else if (buffer->pcmDescriptor.numberOfChannels == 1) {
    if (buffer->pcmDescriptor.bitsPerSample == 16)
      alBufferData(buffer->id, AL_FORMAT_MONO16, buffer->p, buffer->n, buffer->pcmDescriptor.samplesPerSecondPerChannel);
    else if (buffer->pcmDescriptor.bitsPerSample == 8)
      alBufferData(buffer->id, AL_FORMAT_MONO8, buffer->p, buffer->n, buffer->pcmDescriptor.samplesPerSecondPerChannel);
    else {
      return 1;
    }
  } else {
    return 1;
  }
  if ((error = alGetError()) != AL_NO_ERROR) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    _ERROR(error, "unnable to upload buffer data to OpenAL buffer\n");
    return 1;
  }
  return 0;
}

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

  if (buffer->id != 0) {
    alDeleteBuffers(1, &buffer->id);
    buffer->id = 0;
  }

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
  ALenum error;
  alGenBuffers(1, &buffer1->id);
  if ((error = alGetError()) != AL_NO_ERROR) {
    _ERROR(error, "unable to create OpenAL buffer\n");
    free(buffer1->p);
    buffer1->p = NULL;
    free(buffer1);
    buffer = NULL;
    return 1;
  }

  if (_Buffer_upload(buffer1)) {
    alDeleteBuffers(1, &buffer1->id);
    buffer1->id = 0;
    free(buffer1->p);
    buffer1->p = NULL;
    free(buffer1);
    buffer1 = NULL;
    return 1;
  }

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
  _Buffer* buffer;
  ALuint id;
};

static int
_setSourceDefaults
  (
    _Source* source
  )
{
  // The default pitch property value of the source.
  static ALfloat const PITCH = 1.f;

  // The defautl gain property value of the source.
  static ALfloat const GAIN = 1.f;

  // The default position property value of the source.
  static ALfloat const POSITION[] = { 0.f, 0.f, 0.f };

  // The default velocity property value of the source.
  static ALfloat const VELOCITY[] = { 0.f, 0.f, 0.f };

  // The default loop property value of the source.
  // 1 if the source shall loop, 0 otherwise.
  const static ALint LOOP = 0;

  ALenum error;

  // Set the
  // - default pitch property value,
  // - the default gain property value,
  // - the default position property value,
  // - the default velocity property value, and
  // - the default loop property value.
	alSourcef (source->id, AL_PITCH, PITCH);
  if ((error = alGetError()) != AL_NO_ERROR) {
    _ERROR(error, "unable to set OpenAL source pitch to %e\n", PITCH);
     return 1;
  }

	alSourcef (source->id, AL_GAIN, GAIN);
  if ((error = alGetError()) != AL_NO_ERROR) {
    _ERROR(error, "unable to set OpenAL source gain to %e\n", GAIN);
    return 1;
  }

  alSourcefv(source->id, AL_POSITION, POSITION);
  if ((error = alGetError()) != AL_NO_ERROR) {
    _ERROR(error, "unable to set OpenAL source position to (%e, %e, %e)\n",
                  POSITION[0], POSITION[1], POSITION[3]);
    return 1;
  }

  alSourcefv(source->id, AL_VELOCITY, VELOCITY);
  if ((error = alGetError()) != AL_NO_ERROR) {
    _ERROR(error, "unable to set OpenAL source velocity to (%e,%e,%e)\n",
                  VELOCITY[0], VELOCITY[1], VELOCITY[2]);
    return 1;
  }

  alSourcei (source->id, AL_LOOPING, LOOP);
  if ((error = alGetError()) != AL_NO_ERROR) {
    _ERROR(error, "unable to set OpenAL source loop to %d\n", LOOP);
    return 1;
  }

  return 0;
}

static void
_Source_destroy
  (
    _Source* source
  )
{
  assert(NULL != source);
  assert(0 == source->rc);
  if (source->buffer) {
    alSourcei(source->id, AL_BUFFER, 0);
    _Buffer_unref(source->buffer);
    source->buffer = NULL;
  }
  if (source->id) {
    alDeleteSources(1, &source->id);
    source->id = 0;
  }
  free(source);
}

int
_Source_attach
  (
    _Source* source,
    _Buffer* buffer
  )
{
  if (source->buffer) {
    alSourcei(source->id, AL_BUFFER, 0);
    _Buffer_unref(source->buffer);
    source->buffer = NULL;
  }
  ALenum error;
  alSourcei(source->id, AL_BUFFER, buffer->id);
  if ((error = alGetError()) != AL_NO_ERROR) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    _ERROR(error, "unable to attach OpenAL source to buffer\n");
    return 1;
  }
  source->buffer = buffer;
  _Buffer_ref(buffer);
  return 0;
}

int
_Source_play
  (
    _Source* source
  )
{
  if (!source->buffer) {
    return 1;
  }

  ALenum error;

  alSourcePlay(source->id);
  if ((error = alGetError()) != AL_NO_ERROR) {
    _ERROR(error, "unable to play OpenAL source\n");
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
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
  ALenum error;
  ALint state;
  alGetSourcei(source->id, AL_SOURCE_STATE, &state);
  if ((error = alGetError()) != AL_NO_ERROR) {
    _ERROR(error, "unable to retrieve OpenAL source state\n");
    return 1;
  }
  *isPlaying = (AL_PLAYING == state);
  return 0;
}

void
_Source_ref
  (
    _Source* source
  )
{
  source->rc++;
}

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
  source1->rc = 1;

  ALenum error;
  alGenSources(1, &source1->id);
  if ((error = alGetError()) != AL_NO_ERROR) {
    _ERROR(error, "unable to create OpenAL source\n");
    free(source1);
    source1 = NULL;
    return 1;
  }
  if (_setSourceDefaults(source1)) {
    alDeleteSources(1, &source1->id);
    source1->id = 0;
    free(source1);
    source1 = NULL;
    return 1;
  }
  *source = source1;
  return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int
_setListenerDefaults
  (
  )
{
  // The default position property value of the listener.
  static const ALfloat POSITION[] = { 0.0, 0.0, 0.0 };

  // The default velocity property value of the listener.
  static const ALfloat VELOCITY[] = { 0.0, 0.0, 0.0 };

  // The default orientation property value of the listener.
  static const ALfloat ORIENTATION[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

  ALenum error;

  // Set
  // - the default position property value,
  // - the default velocity property value, and 
  // - the default orientation property value.
  alListenerfv(AL_POSITION, POSITION);
  if ((error = alGetError()) != AL_NO_ERROR) {
    _ERROR(error, "unable to set OpenAL listener position to (%e,%e,%e)\n",
                  ORIENTATION[0], ORIENTATION[1], ORIENTATION[2]);
    return 1;
  }
  alListenerfv(AL_VELOCITY, VELOCITY);
  if ((error = alGetError()) != AL_NO_ERROR) {
    _ERROR(error, "unable to set OpenAL listener velocity to (%e,%e,%e).\n",
                  VELOCITY[0], VELOCITY[1], VELOCITY[2]);
    return 1;
  }
  alListenerfv(AL_ORIENTATION, ORIENTATION);
  if ((error = alGetError()) != AL_NO_ERROR) {
    _ERROR(error, "unable to set OpenAL listener orientation to (%e,%e,%e)/(%e,%e,%e)\n",
                  ORIENTATION[0], ORIENTATION[1], ORIENTATION[2],
                  ORIENTATION[3], ORIENTATION[4], ORIENTATION[5]);

    return 1;
  }
  return 0;
}

int
_startup
  (
  )
{
  // Step 1: Create device.
  g_device = alcOpenDevice(NULL);
  if (g_device == NULL) {
    fprintf(stderr, "%s:%d: unable to create OpenAL device '%s'\n", __FILE__, __LINE__, "NULL");
    return 1;
  }
  // Step 2: Create context.
  g_context = alcCreateContext(g_device, NULL);
  if (g_context == NULL) {
    fprintf(stderr, "%s:%d: uUnable to create OpenAL context\n", __FILE__, __LINE__);
    alcCloseDevice(g_device);
    g_device = NULL;
    return 1;
  }
  // Step 3: Activate context.
  if (!alcMakeContextCurrent(g_context)) {
    fprintf(stderr, "%s:%d: uUnable to activate OpenAL context\n", __FILE__, __LINE__);
    alcDestroyContext(g_context);
    g_context = NULL;
    alcCloseDevice(g_device);
    g_device = NULL;
    return 1;
  }

  if (_setListenerDefaults()) {
    if (!alcMakeContextCurrent(NULL)) {
      fprintf(stderr, "%s:%d: unable to deactivate OpenAL context\n", __FILE__, __LINE__);
    }
    alcDestroyContext(g_context);
    g_context = NULL;
    alcCloseDevice(g_device);
    g_device = NULL;
  }

  return 0;
}

void
_shutdown
  (
  )
{
  // Step 3: Deactivate context.
  if (g_context) {
    if (!alcMakeContextCurrent(NULL)) {
      fprintf(stderr, "%s:%d: unable to deactivate OpenAL context\n", __FILE__, __LINE__);
    }
  }
  // Step 2: Destroy context.
  if (g_context) {
    alcDestroyContext(g_context);
    g_context = NULL;
  }
  // Step 1: Destroy device.
  if (g_device != NULL) {
    alcCloseDevice(g_device);
    g_device = NULL;
  }
}

#endif
