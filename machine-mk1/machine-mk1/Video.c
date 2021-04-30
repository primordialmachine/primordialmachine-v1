#include "Video.h"

#include <stdio.h>
#include "Images.h"
#include "Fonts.h"
#include "ShaderProgram.h"

int Machine_Video_startup() {
  int result;
  result = Machine_Images_startup();
  if (result) {
    fprintf(stderr, "%s:%d: Machine_Images_startup() failed\n", __FILE__, __LINE__);
    return result;
  }
  result = Machine_Fonts_startup();
  if (result) {
    fprintf(stderr, "%s:%d: Machine_Fonts_startup() failed\n", __FILE__, __LINE__);
    Machine_Images_shutdown();
    return result;
  }
  return 0;
}

void Machine_Video_shutdown() {
  Machine_Fonts_shutdown();
  Machine_Images_shutdown();
}

void Machine_Video_bindTexture(size_t textureUnit, Machine_Texture* texture) {
  Machine_UtilitiesGl_call(glActiveTexture(GL_TEXTURE0 + textureUnit));
  Machine_UtilitiesGl_call(glBindTexture(GL_TEXTURE_2D, texture->id));
}

void Machine_Video_bindShaderProgram(Machine_ShaderProgram* shaderProgram) {
  Machine_UtilitiesGl_call(glUseProgram(shaderProgram->programId));
}
