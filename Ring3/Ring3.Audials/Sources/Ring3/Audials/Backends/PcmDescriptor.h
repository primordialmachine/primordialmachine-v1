#if !defined(RING3_AUDIALS_BACKENDS_PCMDESCRIPTOR_H_INCLUDED)
#define RING3_AUDIALS_BACKENDS_PCMDESCRIPTOR_H_INCLUDED

// For "int64_t".
#include <inttypes.h>

typedef struct _PcmDescriptor {
  
  /// @brief The number of channels.
  /// Must be @a 1 (mono) or @a 2 (stereo).
  int64_t numberOfChannels;
  
  /// @brief The samples per second per channel.
  /// Must be @a 8000 (8kHz/8000Hz), @a 44100 (44.1kHz/44100Hz), or @a 48000 (48kHz/48000Hz). 
  int64_t samplesPerSecondPerChannel;
  
  /// @brief The bits per sample
  /// Must be @a 8 or @a 16.
  int64_t bitsPerSample;
  
} _PcmDescriptor;

#endif // RING3_AUDIALS_BACKENDS_PCMDESCRIPTOR_H_INCLUDED
