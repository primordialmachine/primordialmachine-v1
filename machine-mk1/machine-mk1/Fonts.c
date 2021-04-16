#include "Fonts.h"

#include <stdio.h>

#include <ft2build.h>
#include FT_FREETYPE_H


static int referenceCount = 0;
static FT_Library library;


struct Machine_Fonts_Font {
  int referenceCount;
  FT_Face face;
};


int Machine_Fonts_startup() {
  if (referenceCount == INT_MAX) {
    return 1;
  }
  else if (referenceCount == 0) {
    FT_Error error;
    error = FT_Init_FreeType(&library);
    if (error) {
      fprintf(stderr, "%s:%d: FT_Init_FreeType failed\n", __FILE__, __LINE__);
      return 1;
    }
    referenceCount++;
    return 0;
  } else {
    referenceCount++;
    return 0;
  }
}

void Machine_Fonts_shutdown() {
  if (0 == --referenceCount) {
    FT_Done_FreeType(library);
  }
}

Machine_Fonts_Font* Machine_Fonts_createFont(const char *path, int pointSize) {
  if (Machine_Fonts_startup()) {
    return NULL;
  }
  Machine_Fonts_Font *font = malloc(sizeof(Machine_Fonts_Font));
  if (!font) {
    return NULL;
  }
  font->referenceCount = 1;
  return font;
}

void Machine_Fonts_Font_destroy(Machine_Fonts_Font* font) {
  if (0 == --font->referenceCount) {
    free(font);
    Machine_Fonts_shutdown();
  }
}
