#define MACHINE_IMAGES_PRIVATE (1)
#include "ImagesContext.h"



#include "Image.h"



static void constructClass(Machine_Images_ImagesContext_Class* self);

static Machine_Images_Image* createFromPath(Machine_Images_ImagesContext* self, Machine_String* path) {
  return Machine_Images_Image_createImageFromPath(path);
}

static Machine_Images_Image* createDirect(Machine_Images_ImagesContext* self, Machine_PixelFormat pixelFormat, Machine_Integer width, Machine_Integer height, Machine_ByteBuffer* pixels) {
  return Machine_Images_Image_createImageDirect(pixelFormat, width, height, pixels);
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_Images_ImagesContext, Machine_ImagesContext, NULL, &Machine_Images_ImagesContext_construct, NULL);

static void constructClass(Machine_Images_ImagesContext_Class* self) {
  ((Machine_ImagesContext_Class*)self)->createDirect = (Machine_Image * (*)(Machine_ImagesContext *, Machine_PixelFormat, Machine_Integer, Machine_Integer, Machine_ByteBuffer *)) & createDirect;
  ((Machine_ImagesContext_Class*)self)->createFromPath = (Machine_Image * (*)(Machine_ImagesContext *, Machine_String*)) & createFromPath;
}

void Machine_Images_ImagesContext_construct(Machine_Images_ImagesContext* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_ImagesContext_construct((Machine_ImagesContext*)self, numberOfArguments, arguments);
  constructClass(self);
  Machine_setClassType((Machine_Object*)self, Machine_Images_ImagesContext_getClassType());
}

Machine_Images_ImagesContext* Machine_Images_ImagesContext_create() {
  Machine_ClassType* ty = Machine_Images_ImagesContext_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Images_ImagesContext* self = (Machine_Images_ImagesContext*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
