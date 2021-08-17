//// @file FontsContext.c
/// @author Michael Heilmann (<michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reservied.
#define MACHINE_FONTS_PRIVATE (1)
#include "FontsContext.h"



#include "Font.h"
#include <ft2build.h>
#include FT_FREETYPE_H



static int g_referenceCount = 0;
static FT_Library g_library;

static void visit(Machine_Fonts_FontsContext* self) {
  if (self->videoContext) {
    Machine_visit(self->videoContext);
  }
  if (self->imageContext) {
    Machine_visit(self->imageContext);
  }
}

static void destruct(Machine_Fonts_FontsContext* self) {
  self->library = NULL;
  if (0 == --g_referenceCount) {
    FT_Done_FreeType(g_library);
  }
}

static Machine_Font* createFont(Machine_Fonts_FontsContext* self, Machine_String* path, Machine_Integer pointSize) {
  return (Machine_Font *)Machine_Fonts_Font_create((Machine_FontsContext *)self, path, pointSize);
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_Fonts_FontsContext, Machine_FontsContext, &visit, &Machine_Fonts_FontsContext_construct, &destruct);

static void constructClass(Machine_Fonts_FontsContext_Class* self) {
  ((Machine_FontsContext_Class*)self)->createFont = (Machine_Font * (*)(Machine_FontsContext*, Machine_String*, Machine_Integer)) & createFont;
}

void Machine_Fonts_FontsContext_construct(Machine_Fonts_FontsContext* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_FontsContext_construct((Machine_FontsContext*)self, numberOfArguments, arguments);
  self->videoContext = (Machine_VideoContext*)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 0, Machine_VideoContext_getClassType());
  self->imageContext = (Machine_ImagesContext *)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 1, Machine_ImagesContext_getClassType());
  if (0 == g_referenceCount) {
    FT_Error error = FT_Init_FreeType(&g_library);
    if (error) {
      Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "FT_Init_FreeType failed\n");
      Machine_setStatus(Machine_Status_EnvironmentFailed);
      Machine_jump();
    }
  }
  self->library = &g_library;
  g_referenceCount++;
  constructClass(self);
  Machine_setClassType((Machine_Object*)self, Machine_Fonts_FontsContext_getClassType());
}

Machine_Fonts_FontsContext* Machine_Fonts_FontsContext_create(Machine_VideoContext* videoContext, Machine_ImagesContext *imagesContext) {
  Machine_ClassType* ty = Machine_Fonts_FontsContext_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Machine_Value ARGUMENTS[2];
  Machine_Value_setObject(&ARGUMENTS[0], (Machine_Object*)videoContext);
  Machine_Value_setObject(&ARGUMENTS[1], (Machine_Object*)imagesContext);
  Machine_Fonts_FontsContext* self = (Machine_Fonts_FontsContext*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
