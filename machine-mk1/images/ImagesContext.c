#define MACHINE_IMAGES_PRIVATE (1)
#include "ImagesContext.h"


#include "Ring1/All/_Include.h"
#include "Image.h"


static void constructClass(Machine_Images_ImagesContext_Class* self);

static Machine_Images_Image* createFromPath(Machine_Images_ImagesContext* self, Ring2_String* path) {
  return Machine_Images_Image_createImageFromPath(path);
}

static Machine_Images_Image* createDirect(Machine_Images_ImagesContext* self, Ring3_PixelFormat pixelFormat, Ring2_Integer width, Ring2_Integer height, Ring2_ByteBuffer* pixels) {
  return Machine_Images_Image_createImageDirect(pixelFormat, width, height, pixels);
}

static void constructClass(Machine_Images_ImagesContext_Class* self) {
  ((Ring3_ImagesContext_Class*)self)->createDirect = (Ring3_Image * (*)(Ring3_ImagesContext*, Ring3_PixelFormat, Ring2_Integer, Ring2_Integer, Ring2_ByteBuffer*)) & createDirect;
  ((Ring3_ImagesContext_Class*)self)->createFromPath = (Ring3_Image * (*)(Ring3_ImagesContext*, Ring2_String*)) & createFromPath;
}

MACHINE_DEFINE_CLASSTYPE(Machine_Images_ImagesContext, Ring3_ImagesContext, NULL,
                         &Machine_Images_ImagesContext_construct, NULL, &constructClass, NULL);

void Machine_Images_ImagesContext_construct(Machine_Images_ImagesContext* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Ring3_ImagesContext_construct((Ring3_ImagesContext*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Images_ImagesContext_getType());
}

Machine_Images_ImagesContext* Machine_Images_ImagesContext_create() {
  Machine_Type* ty = Machine_Images_ImagesContext_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Images_ImagesContext* self = Ring1_cast(Machine_Images_ImagesContext*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}
