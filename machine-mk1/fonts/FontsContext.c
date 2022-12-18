//// @file FontsContext.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_FONTS_PRIVATE (1)
#include "FontsContext.h"


#include "Ring1/All/_Include.h"
#include "Font.h"
#include <ft2build.h>
#include FT_FREETYPE_H


static int g_referenceCount = 0;
static FT_Library g_library;

static void visit(Machine_Fonts_FontsContext* self) {
  if (self->videoContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->videoContext);
  }
  if (self->imageContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->imageContext);
  }
}

static void destruct(Machine_Fonts_FontsContext* self) {
  self->library = NULL;
  if (0 == --g_referenceCount) {
    FT_Done_FreeType(g_library);
  }
}

static Machine_Font* createFont(Machine_Fonts_FontsContext* self, Ring2_String* path, Ring2_Integer pointSize) {
  return (Machine_Font *)Machine_Fonts_Font_create((Machine_FontsContext *)self, path, pointSize);
}

static void constructClass(Machine_Fonts_FontsContext_Class* self);

MACHINE_DEFINE_CLASSTYPE(Machine_Fonts_FontsContext, Machine_FontsContext, &visit,
                         &Machine_Fonts_FontsContext_construct, &destruct, &constructClass, NULL);

static void constructClass(Machine_Fonts_FontsContext_Class* self) {
  ((Machine_FontsContext_Class*)self)->createFont = (Machine_Font * (*)(Machine_FontsContext*, Ring2_String*, Ring2_Integer)) & createFont;
}

void Machine_Fonts_FontsContext_construct(Machine_Fonts_FontsContext* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Machine_FontsContext_construct((Machine_FontsContext*)self, numberOfArguments, arguments);
  self->videoContext = (Machine_VideoContext*)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 0, Machine_VideoContext_getType());
  self->imageContext = (Machine_ImagesContext *)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 1, Machine_ImagesContext_getType());
  if (0 == g_referenceCount) {
    FT_Error error = FT_Init_FreeType(&g_library);
    if (error) {
      Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "FT_Init_FreeType failed\n");
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }
  }
  self->library = &g_library;
  g_referenceCount++;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Fonts_FontsContext_getType());
}

Machine_Fonts_FontsContext* Machine_Fonts_FontsContext_create(Machine_VideoContext* videoContext, Machine_ImagesContext *imagesContext) {
  Machine_ClassType* ty = Machine_Fonts_FontsContext_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value ARGUMENTS[2];
  Ring2_Value_setObject(&ARGUMENTS[0], (Machine_Object*)videoContext);
  Ring2_Value_setObject(&ARGUMENTS[1], (Machine_Object*)imagesContext);
  Machine_Fonts_FontsContext* self = (Machine_Fonts_FontsContext*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
