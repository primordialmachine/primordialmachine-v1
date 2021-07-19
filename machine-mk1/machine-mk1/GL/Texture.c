#include "./../GL/Texture.h"



static void Machine_GL_Texture_destruct(Machine_GL_Texture* self) {
  if (self->id) {
    glDeleteTextures(1, &self->id);
    self->id = 0;
  }
}

void Machine_GL_Texture_construct_fromImage(Machine_GL_Texture* self, Machine_Images_Image* image) {
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { {Machine_ValueFlag_Void, Machine_Void_Void} };
  Machine_Texture_construct((Machine_Texture*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_UtilitiesGl_call(glGenTextures(1, &self->id));
  Machine_UtilitiesGl_call(glBindTexture(GL_TEXTURE_2D, self->id));

  Machine_UtilitiesGl_call(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  Machine_UtilitiesGl_call(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  Machine_UtilitiesGl_call(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  Machine_UtilitiesGl_call(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

  Machine_Integer width, height;
  Machine_Images_Image_getSize(image, &width, &height);
  Machine_PixelFormat pixelFormat = Machine_Images_Image_getPixelFormat(image);
  void* pixels = Machine_Images_Image_getPixels(image);


  Machine_UtilitiesGl_call(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
  switch (pixelFormat) {
  case Machine_PixelFormat_BGR:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,
                                          height, 0, GL_BGR, GL_UNSIGNED_BYTE,
                                          pixels));
    break;
  case Machine_PixelFormat_BGRA:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
                                          height, 0, GL_BGRA, GL_UNSIGNED_BYTE,
                                          pixels));
    break;
  case Machine_PixelFormat_RGB:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,
                                          height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                                          pixels));
    break;
  case Machine_PixelFormat_RGBA:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
                                          height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                                          pixels));
    break;
  case Machine_PixelFormat_GRAYSCALE:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width,
                                          height, 0, GL_RED, GL_UNSIGNED_BYTE,
                                          pixels));
    break;
  default:
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  };
  Machine_setClassType((Machine_Object*)self, Machine_Texture_getClassType());
}

void Machine_GL_Texture_construct(Machine_GL_Texture* self, size_t numberOfArguments, const Machine_Value* arguments) {
  if (numberOfArguments == 1) {
    Machine_Images_Image* image = (Machine_Images_Image*)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 0, Machine_Images_Image_getClassType());
    Machine_GL_Texture_construct_fromImage(self, image);
  }
  else {
    Machine_setStatus(Machine_Status_InvalidNumberOfArguments);
    Machine_jump();
  }
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_GL_Texture, Machine_Texture, NULL, &Machine_GL_Texture_construct, &Machine_GL_Texture_destruct)


Machine_GL_Texture* Machine_GL_Texture_create(Machine_Images_Image* image) {
  Machine_ClassType* ty = Machine_GL_Texture_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 1;
  Machine_Value ARGUMENTS[1];
  Machine_Value_setObject(&ARGUMENTS[0], (Machine_Object*)image);
  Machine_GL_Texture* self = (Machine_GL_Texture*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
