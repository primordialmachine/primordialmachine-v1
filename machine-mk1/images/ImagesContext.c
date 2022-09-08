#define MACHINE_IMAGES_PRIVATE (1)
#include "ImagesContext.h"



#include "Image.h"



static void constructClass(Machine_Images_ImagesContext_Class* self);

static Machine_Images_Image* createFromPath(Machine_Images_ImagesContext* self, Ring2_String* path) {
  return Machine_Images_Image_createImageFromPath(path);
}

static Machine_Images_Image* createDirect(Machine_Images_ImagesContext* self, Machine_PixelFormat pixelFormat, Ring2_Integer width, Ring2_Integer height, Machine_ByteBuffer* pixels) {
  return Machine_Images_Image_createImageDirect(pixelFormat, width, height, pixels);
}

static void constructClass(Machine_Images_ImagesContext_Class* self) {
  ((Machine_ImagesContext_Class*)self)->createDirect = (Machine_Image * (*)(Machine_ImagesContext*, Machine_PixelFormat, Ring2_Integer, Ring2_Integer, Machine_ByteBuffer*)) & createDirect;
  ((Machine_ImagesContext_Class*)self)->createFromPath = (Machine_Image * (*)(Machine_ImagesContext*, Ring2_String*)) & createFromPath;
}

MACHINE_DEFINE_CLASSTYPE(Machine_Images_ImagesContext, Machine_ImagesContext, NULL,
                         &Machine_Images_ImagesContext_construct, NULL, &constructClass, NULL);

void Machine_Images_ImagesContext_construct(Machine_Images_ImagesContext* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Machine_ImagesContext_construct((Machine_ImagesContext*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Machine_Images_ImagesContext_getType());
}

Machine_Images_ImagesContext* Machine_Images_ImagesContext_create() {
  Machine_ClassType* ty = Machine_Images_ImagesContext_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Ring2_Value ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Images_ImagesContext* self = (Machine_Images_ImagesContext*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
