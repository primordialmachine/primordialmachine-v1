#if !defined(RING3_IMAGESTRANSCODERS_LIBPNG_IMAGESDECODER_H_INCLUDED)
#define RING3_IMAGESTRANSCODERS_LIBPNG_IMAGESDECODER_H_INCLUDED

#if !defined(RING3_IMAGESTRANSCODERS_LIBPNG_PRIVATE)
#error("Do not include `Ring3/ImagesTranscoders/LibPng/ImagesDecoder.h` directly. Include `Ring3/Images/LibPng/_Include.h` instead.")
#endif

#include "Ring3/Visuals/_Include.h"


MACHINE_DECLARE_CLASSTYPE(Ring3_ImagesTranscoders_LibPng_ImagesDecoder)

void
Ring3_ImagesTranscoders_LibPng_ImagesDecoder_construct
  (
    Ring3_ImagesTranscoders_LibPng_ImagesDecoder* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Ring3_ImagesTranscoders_LibPng_ImagesDecoder*
Ring3_ImagesTranscoders_LibPng_ImagesDecoder_create
  (
  );


#endif // RING3_IMAGESTRANSCODERS_LIBPNG_IMAGESDECODER_H_INCLUDED
