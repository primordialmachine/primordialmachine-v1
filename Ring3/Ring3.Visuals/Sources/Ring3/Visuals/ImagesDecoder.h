#if !defined(RING3_VISUALS_IMAGESDECODER_H_INCLUDED)
#define RING3_VISUALS_IMAGESDECODER_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/ImagesDecoder.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring3/Visuals/PixelFormat.h"


MACHINE_DECLARE_CLASSTYPE(Ring3_ImagesDecoder)

struct Ring3_ImagesDecoder_Class {
  Machine_Object_Class parent;
  void
  (*decode)
    (
      Ring3_ImagesDecoder* self,
      char const* sourceBytes,
      int64_t numberOfSourceBytes,
      void** targetBytes,
      int64_t* numberOfTargetBytes,
      Ring3_PixelFormat* targetPixelFormat,
      int* targetWidth,
      int* targetHeight
    );
};

struct Ring3_ImagesDecoder {
  Machine_Object parent;
};


void
Ring3_ImagesDecoder_construct
  (
    Ring3_ImagesDecoder* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

void
Ring3_ImagesDecoder_decode
  (
    Ring3_ImagesDecoder* self,
    char const* sourceBytes,
    int64_t numberOfSourceBytes,
    void** targetBytes,
    int64_t* numberOfTargetBytes,
    Ring3_PixelFormat* targetPixelFormat,
    int* targetWidth,
    int* targetHeight
  );


#endif // RING3_IMAGES_LIBPNG_IMAGESDECODER_H_INCLUDED
