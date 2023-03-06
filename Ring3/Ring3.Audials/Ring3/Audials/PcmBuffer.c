/// @file Ring3/Audials/PcmBuffer.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring3/Audials/PcmBuffer.h"

#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"

// For sin(). For M_PI.
#include <math.h>

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

// For malloc(). For free().
#include <malloc.h>

static void
Ring3_Audials_PcmBuffer_visit
  (
    Ring3_Audials_PcmBuffer* self
  )
{
  if (self->pcmDescriptor) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->pcmDescriptor);
  }
}

static void
Ring3_Audials_PcmBuffer_destruct
  (
    Ring3_Audials_PcmBuffer *self
  )
{
  if (self->bytes) {
    Ring1_Memory_deallocate(self->bytes);
    self->bytes = NULL;
  }
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Audials_PcmBuffer,
                         Machine_Object,
                         &Ring3_Audials_PcmBuffer_visit,
                         &Ring3_Audials_PcmBuffer_construct,
                         &Ring3_Audials_PcmBuffer_destruct,
                         NULL,
                         NULL)



static int16_t
toI16
  (
    double v
  )
{
  if (v < INT16_MIN) {
    return INT16_MIN;
  } else if (v > INT16_MAX) {
    return INT16_MAX;
  } else {
    return (int16_t)v;
  }
}

static int8_t
toI8
  (
    double v
  )
{
  if (v < INT8_MIN) {
    return INT8_MIN;
  } else if (v > INT8_MAX) {
    return INT8_MAX;
  } else {
    return (int8_t)v;
  }
}

static void
writeToAllChannels_i16
  (
    Ring3_Audials_PcmBuffer* self,
    uint32_t index,
    int16_t value
  )
{
  int16_t* bytes = (int16_t*)self->bytes;
  for (uint32_t i = 0, n = self->pcmDescriptor->numberOfChannels; i < n; ++i) {
    bytes[index * self->pcmDescriptor->numberOfChannels + i] = value;
  }
}

static void
writeToAllChannels_i8
  (
    Ring3_Audials_PcmBuffer* self,
    uint32_t index,
    int8_t value
  )
{
  int8_t* bytes = (int8_t*)self->bytes;
  for (uint32_t i = 0, n = self->pcmDescriptor->numberOfChannels; i < n; ++i) {
    bytes[index * self->pcmDescriptor->numberOfChannels + i] = value;
  }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void
Ring3_Audials_PcmBuffer_construct
  (
    Ring3_Audials_PcmBuffer* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  ) 
{
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), NUMBER_OF_ARGUMENTS, ARGUMENTS);

  self->length = Ring2_CallArguments_getIntegerArgument(numberOfArguments, arguments, 0);
  if (self->length < 0 || self->length > Ring3_Audials_MaximumLength) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  self->pcmDescriptor = Ring1_cast(Ring3_Audials_PcmDescriptor *, Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 1, Ring3_Audials_PcmDescriptor_getType()));
  Ring2_Integer generatorId = Ring2_CallArguments_getIntegerArgument(numberOfArguments, arguments, 2);
  //
  uint32_t totalSamples = self->length * self->pcmDescriptor->samplesPerSecondPerChannel;
  if ((UINT32_MAX / (self->pcmDescriptor->bitsPerSample / 8)) /
        self->pcmDescriptor->numberOfChannels <
      totalSamples) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  self->numberOfBytes = self->pcmDescriptor->bitsPerSample / 8 *
                        totalSamples *
                        self->pcmDescriptor->numberOfChannels;
  if (Ring1_Memory_allocate(&self->bytes, self->numberOfBytes)) {
    Ring2_jump();
  }

  switch (generatorId) {
    case Mkx_Audials_GeneratorId_Sine220: {
      double frequency = 220;
      double amplitude;
      if (self->pcmDescriptor->bitsPerSample == 16)
        amplitude = INT16_MAX;
      else if (self->pcmDescriptor->bitsPerSample == 8)
        amplitude = INT8_MAX;
      else {
        Ring1_Memory_deallocate(self->bytes);
        self->bytes = NULL;
        Ring1_Status_set(Ring1_Status_InvalidArgument);
        Ring2_jump();
      }
      double theta = 2.0 * M_PI * frequency;
      double time = 0.0;
      double deltaTime = 1.0 / (double)self->pcmDescriptor->samplesPerSecondPerChannel;
      // The sample rate aka samples per second denotes the number of samples for a single channel per second.
      // The most commonly used sample rate is 44100 Hz.
      // In our case we need to know how much time passed from one sample to another.
      // This time is constant and remains stable, but depends on sample rate.
      // So if our sample rate is 44100 Hz, it says that we should take 44100 samples per one second.
      // If we divide 1 over 44100 we get delta time between samples.
      // This is the delta time value.
      for (uint64_t i = 0, n = totalSamples; i < n; ++i) {
        double y = amplitude * sin(theta * time);

        if (self->pcmDescriptor->bitsPerSample == 16) {
          int16_t x = toI16(y);
          writeToAllChannels_i16(self, i, x);
        } else if (self->pcmDescriptor->bitsPerSample == 8) {
          int8_t x = toI8(y);
          writeToAllChannels_i8(self, i, x);
        } else {
          free(self->bytes);
          self->bytes = NULL;
          Ring1_Status_set(Ring1_Status_InvalidArgument);
          Ring2_jump();
        }
        time += deltaTime;
      }
    } break;  
    default: {
      free(self->bytes);
      self->bytes = NULL;
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    } break;
  };
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_Audials_PcmBuffer_getType());
}

Ring1_CheckReturn() Ring3_Audials_PcmBuffer*
Ring3_Audials_PcmBuffer_create
  (
    Ring2_Integer length,
    Ring3_Audials_PcmDescriptor *pcmDescriptor,
    Mkx_Audials_GeneratorId generatorId
  )
{
  Machine_ClassType* ty = Ring3_Audials_PcmBuffer_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value ARGUMENTS[3];
  Ring2_Value_setInteger(&ARGUMENTS[0], length);
  Ring2_Value_setObject(&ARGUMENTS[1], Ring1_cast(Machine_Object*, pcmDescriptor));
  Ring2_Value_setInteger(&ARGUMENTS[2], Ring1_cast(Ring2_Integer, generatorId));
  Ring3_Audials_PcmBuffer* self = Ring1_cast(Ring3_Audials_PcmBuffer *, Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}
