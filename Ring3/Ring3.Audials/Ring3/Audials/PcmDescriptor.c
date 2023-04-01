/// @file Ring3/Audials/PcmDescriptor.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_AUDIALS_PRIVATE (1)
#include "Ring3/Audials/PcmDescriptor.h"
#undef RING3_AUDIALS_PRIVATE

#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"

MACHINE_DEFINE_CLASSTYPE(Ring3_Audials_PcmDescriptor,
                         Machine_Object,
                         NULL,
                         &Ring3_Audials_PcmDescriptor_construct,
                         NULL,
                         NULL,
                         NULL)

void
Ring3_Audials_PcmDescriptor_construct
  (
    Ring3_Audials_PcmDescriptor* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (numberOfArguments != 3) {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();

  }
  self->numberOfChannels = Ring2_CallArguments_getIntegerArgument(numberOfArguments, arguments, 0);
  if (self->numberOfChannels < 1 || self->numberOfChannels > Ring3_Audials_MaximumNumberOfChannels) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  self->samplesPerSecondPerChannel = Ring2_CallArguments_getIntegerArgument(numberOfArguments, arguments, 1);
  if (self->samplesPerSecondPerChannel != 8000 &&
      self->samplesPerSecondPerChannel != 44100 &&
      self->samplesPerSecondPerChannel != 48000) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  self->bitsPerSample = Ring2_CallArguments_getIntegerArgument(numberOfArguments, arguments, 2);
  if (self->bitsPerSample != 8 &&
      self->bitsPerSample != 16) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_Audials_PcmDescriptor_getType());
}

Ring1_CheckReturn() Ring3_Audials_PcmDescriptor*
Ring3_Audials_PcmDescriptor_create
  (
    Ring2_Integer numberOfChannels,
    Ring2_Integer samplesPerSecondPerChannel,
    Ring2_Integer bitsPerSample
  )
{
  Machine_Type* ty = Ring3_Audials_PcmDescriptor_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value arguments[3];
  Ring2_Value_setInteger(&arguments[0], numberOfChannels);
  Ring2_Value_setInteger(&arguments[1], samplesPerSecondPerChannel);
  Ring2_Value_setInteger(&arguments[2], bitsPerSample);
  Ring3_Audials_PcmDescriptor* self = Ring1_cast(Ring3_Audials_PcmDescriptor *, Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}
