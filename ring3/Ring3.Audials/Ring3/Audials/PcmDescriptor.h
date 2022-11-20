/// @file Ring3/Audials/PcmDescriptor.h
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
#if !defined(RING3_AUDIALS_PCMDESCRIPTOR_H_INCLUDED)
#define RING3_AUDIALS_PCMDESCRIPTOR_H_INCLUDED

#include "Ring2/_Include.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/// @brie
/// We support up to 255 channels.
/// This does not mean, Ring3_Audials_MaximumNumberOfChannels channels are supported in all cases.
/// This means, not more than Ring3_Audials_MaximumNumberOfChannels channels are supported in any case.
#define Ring3_Audials_MaximumNumberOfChannels (255)

/// @brief
/// We support up to 16 bits per sample.
/// This does not mean, Ring3_Audials_MaximumBitsPerSample bits are supported in all cases.
/// This means, not more than Ring3_Audials_MaximumBitsPerSample bits are supported in any case.
#define Ring3_Audials_MaximumBitsPerSample (16)

/// @brief
/// The maximum length in seconds.
/// This does not mean, Ring3_Audials_MaximumLength lengths are supported in all cases.
/// This means, not more than Ring3_Audials_MaximumLength channels are supported in any case.
#define Ring3_Audials_MaximumLength (UINT32_MAX / 48000)

/// @brief
/// Humans can hear from 20Hz to 20000Hz.
/// We support a maximum frequency of 40000Hz.
/// Another term is "samples per second per channel".
#define Ring3_Audials_MaximumFrequencyPerChannel 40000

/// @brief A descriptor of PCM data.
/// @extends Machine.Object
MACHINE_DECLARE_CLASSTYPE(Ring3_Audials_PcmDescriptor);

struct Ring3_Audials_PcmDescriptor_Class {
  Machine_Object_Class _parent;
};

struct Ring3_Audials_PcmDescriptor {
  Machine_Object _parent;
  Ring2_Integer numberOfChannels;
  Ring2_Integer samplesPerSecondPerChannel;
  Ring2_Integer bitsPerSample;
};

/// @brief
/// Construct this Ring3_Audials_PcmDescriptor object.
/// @param self
/// A pointer to this Ring3_Audials_PcmDescriptor object.
/// @param numberOfChannels
/// The number of channels.
/// Must be greater than @a 0 and smaller than or equal to #Ring3_Audials_MaximumNumberOfChannels.
/// @param samplesPerSecondPerChannel
/// The samples per second in Hz per channel.
/// Must be greater than @a 0 and smaller than Ring3_Audials_MaximumFrequency/Ring3_Audials_MaximumSamplesPeSecond.
/// Must be @a 8000 (8kHz/8000Hz), @a 44100 (44.1kHz/44100Hz), or @a 48000 (48kHz/48000Hz). 
/// @param bitsPerSample
/// The bits per sample.
/// Must be greater than @a 0 and smaller than or equal to Ring3_Audials_MaximumBitsPerSample.
/// Must be @a 8 or @a 16.
/// @remarks
/// @code
/// construct
/// (
///   Ring2.Integer numberOfChannels,
///   Ring2.Integer samplesPerSecond,
///   Ring2.Integer bitsPerSample
/// )
/// @endcode
/// @error @a numberOfChannels is invalid value.
/// @error @a samplesPerSecondPerChannel is invalid value.
/// @error @a bitsPerSample is an invalid value.
void
Ring3_Audials_PcmDescriptor_construct
  (
    Ring3_Audials_PcmDescriptor* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Create a Ring3.Audials.PcmDescriptor object.
/// @param result A pointer to a Ring3.Audials.Audials_PcmDescriptor * variable.
/// @param numberOfChannels The number of channels.
/// @param samplesPerSecondPerChannel The samples per second.
/// @param bitsPerSample The bits per sample.
/// @return A pointer to the Ring3.Audials.PcmDescriptor object.
/// @see Ring1_Audials_PcmDescriptor_construct
Ring1_CheckReturn() Ring3_Audials_PcmDescriptor *
Ring3_Audials_PcmDescriptor_create
  (
    Ring2_Integer numberOfChannels,
    Ring2_Integer samplesPerSecondPerChannel,
    Ring2_Integer bitsPerSample
  );

#endif // RING3_AUDIALS_PCMDESCRIPTOR_H_INCLUDED
