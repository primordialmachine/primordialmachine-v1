#include "Texture.h"


static void Machine_Texture_destruct(Machine_Texture* self) {
  if (self->id) {
    glDeleteTextures(1, &self->id);
    self->id = 0;
  }
}

static void Machine_Texture_finalize(Machine_Texture* self) {
  Machine_Texture_destruct(self);
}

Machine_Texture* Machine_Texture_create(Machine_Images_Image* image) {
  Machine_Texture* self = Machine_allocate(sizeof(Machine_Texture), (void (*)(void*)) NULL,
                                                                    (void (*)(void*)) & Machine_Texture_finalize);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  Machine_UtilitiesGl_call(glGenTextures(1, &self->id));
  Machine_UtilitiesGl_call(glBindTexture(GL_TEXTURE_2D, self->id));
  
  Machine_UtilitiesGl_call(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  Machine_UtilitiesGl_call(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  Machine_UtilitiesGl_call(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  Machine_UtilitiesGl_call(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
  
  int width, height;
  Machine_Images_Image_getSize(image, &width, &height);
  Machine_Images_PixelFormat pixelFormat = Machine_Images_Image_getPixelFormat(image);
  void* pixels = Machine_Images_Image_getPixels(image);


  Machine_UtilitiesGl_call(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
  switch (pixelFormat) {
  case Machine_Images_PixelFormat_BGR:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,
                             height, 0, GL_BGR, GL_UNSIGNED_BYTE,
                             pixels));
    break;
  case Machine_Images_PixelFormat_BGRA:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
                             height, 0, GL_BGRA, GL_UNSIGNED_BYTE,
                             pixels));
    break;
  case Machine_Images_PixelFormat_RGB:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,
                             height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                             pixels));
    break;
  case Machine_Images_PixelFormat_RGBA:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
                             height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                             pixels));
    break;
  case Machine_Images_PixelFormat_GRAYSCALE:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width,
                                          height, 0, GL_RED, GL_UNSIGNED_BYTE,
                                          pixels));
    break;
  default:
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  };

  return self;
}
