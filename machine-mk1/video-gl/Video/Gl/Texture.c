/// @file Video/Gl/VideoContext.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/Texture.h"


#include "Ring1/All/_Include.h"


static void Machine_Gl_Texture_destruct(Machine_Gl_Texture* self) {
  if (self->id) {
    glDeleteTextures(1, &self->id);
    self->id = 0;
  }
}

void Machine_Gl_Texture_construct_fromImage(Machine_Gl_Texture* self, Ring3_Image* image) {
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring3_Texture_construct((Ring3_Texture*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_UtilitiesGl_call(glGenTextures(1, &self->id));
  Machine_UtilitiesGl_call(glBindTexture(GL_TEXTURE_2D, self->id));

  Machine_UtilitiesGl_call(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  Machine_UtilitiesGl_call(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  Machine_UtilitiesGl_call(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  Machine_UtilitiesGl_call(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

  Ring2_Integer width, height;
  Ring3_Image_getSize((Ring3_Image const *)image, &width, &height);
  Ring3_PixelFormat pixelFormat = Ring3_Image_getPixelFormat(image);
  void const* pixels = Ring3_Image_getPixels(image);


  Machine_UtilitiesGl_call(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
  switch (pixelFormat) {
  case Ring3_PixelFormat_BGR:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,
                                          height, 0, GL_BGR, GL_UNSIGNED_BYTE,
                                          pixels));
    break;
  case Ring3_PixelFormat_BGRA:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
                                          height, 0, GL_BGRA, GL_UNSIGNED_BYTE,
                                          pixels));
    break;
  case Ring3_PixelFormat_RGB:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,
                                          height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                                          pixels));
    break;
  case Ring3_PixelFormat_RGBA:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
                                          height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                                          pixels));
    break;
  case Ring3_PixelFormat_GRAYSCALE:
    Machine_UtilitiesGl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width,
                                          height, 0, GL_RED, GL_UNSIGNED_BYTE,
                                          pixels));
    break;
  default:
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  };
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Texture_getType());
}

void Machine_Gl_Texture_construct(Machine_Gl_Texture* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  if (numberOfArguments == 1) {
    Ring3_Image* image =
      (Ring3_Image*)
      Ring2_CallArguments_getObjectArgument
        (
          numberOfArguments, arguments, 0, Ring3_Image_getType()
        );
    Machine_Gl_Texture_construct_fromImage(self, image);
  } else {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gl_Texture, Ring3_Texture, NULL, &Machine_Gl_Texture_construct,
                         &Machine_Gl_Texture_destruct, NULL, NULL)

Machine_Gl_Texture* Machine_Gl_Texture_create(Ring3_Image* image) {
  Machine_Type* ty = Machine_Gl_Texture_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1];
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,image));
  Machine_Gl_Texture* self = Ring1_cast(Machine_Gl_Texture*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}
