/// @file Ring3/Audials/PcmBuffer.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(RING3_AUDIALS_PCMBUFFER_H_INCLUDED)
#define RING3_AUDIALS_PCMBUFFER_H_INCLUDED

#include "Ring3/Audials/PcmDescriptor.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Audials_PcmBuffer)

struct Ring3_Audials_PcmBuffer_Class {
  Machine_Object_Class _parent;
};

struct Ring3_Audials_PcmBuffer {
  Machine_Object _parent;

  /// @brief A pointer to an array of Bytes.
  void *bytes;

  /// @brief The descriptor. 
  Ring3_Audials_PcmDescriptor* pcmDescriptor;
  
  /// @brief The size of the array pointed to byte @a bytes.
  Ring2_Integer numberOfBytes;

  /// The duration of the buffer in seconds.
  Ring2_Integer length;

};

typedef int Mkx_Audials_GeneratorId;

#define Mkx_Audials_GeneratorId_Sine220 (1)

/// @brief
/// Initialize an Ring3.Audials.PcmBuffer object.
/// 
/// @param self
/// A pointer to a not initialized Ring3.Audials.PcmBuffer  object.
/// 
/// @param length
/// The length of the buffer, in seconds.
/// 
/// @param pcmDescriptor 
/// The duration of the buffer in seconds.
/// 
/// @param numberOfChannels
/// The number of channels of the buffe.
/// Must not be smaller than 1.
/// Must not be greater than Mkx_Audials_MaximumNumberOfChannels.
/// 
/// @param samplesPerSecond
/// The samples per second in Hz per channel.
/// Must be one of 8kHz (8000Hz), 44.1kHz (44100Hz), or 48kHz (48000Hz).
/// 
/// @param generatorId
/// The generator id of the generator to fill the buffer with.
/// Must be #Mkx_Audials_GeneratorId_Sine220.
/// 
/// @return
/// #MKX_AUDIALS_RESULT_SUCCESS on success, #MKX_AUDIALS_RESULT_FAILURE on failure.
void
Ring3_Audials_PcmBuffer_construct
  (
    Ring3_Audials_PcmBuffer *self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_CheckReturn() Ring3_Audials_PcmBuffer *
Ring3_Audials_PcmBuffer_create
  (
    Ring2_Integer length,
    Ring3_Audials_PcmDescriptor *pcmDescriptor,
    Mkx_Audials_GeneratorId generatorId
  );

#endif // RING3_AUDIALS_PCMBUFFER_H_INCLUDED
