#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/ImagesDecoder.h"
#undef RING3_VISUALS_PRIVATE


MACHINE_DEFINE_CLASSTYPE(Ring3_ImagesDecoder,
                         Machine_Object,
                         NULL,
                         &Ring3_ImagesDecoder_construct,
                         NULL,
                         NULL,
                         NULL);

void
Ring3_ImagesDecoder_construct
  (
    Ring3_ImagesDecoder* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_ImagesDecoder_getType());
}
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
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_ImagesDecoder, decode,
                                    sourceBytes,
                                    numberOfSourceBytes,
                                    targetBytes,
                                    numberOfTargetBytes,
                                    targetPixelFormat,
                                    targetWidth,
                                    targetHeight); }
