//// @file Ring3/Fonts/FreeType2/FontsContext.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_FONTS_FREETYPE2_PRIVATE (1)
#include "Ring3/Fonts/FreeType2/FontsContext.h"

#include "Ring3/Fonts/FreeType2/Font.h"
#undef RING3_FONTS_FREETYPE2_PRIVATE

#include "Ring1/All/_Include.h"

#include <ft2build.h>
#include FT_FREETYPE_H


static int g_referenceCount = 0;
static FT_Library g_library;


static void
constructClass
  (
    Machine_Fonts_FontsContext_Class* self
  );

static Ring3_Font*
createFont
  (
    Machine_Fonts_FontsContext* self,
    Ring2_String* path,
    Ring2_Integer pointSize
  );

static void
destruct
  (
    Machine_Fonts_FontsContext* self
  );

static void
visit
  (
    Machine_Fonts_FontsContext* self
  );

MACHINE_DEFINE_CLASSTYPE(Machine_Fonts_FontsContext,
                         Ring3_FontsContext,
                         &visit,
                         &Machine_Fonts_FontsContext_construct,
                         &destruct,
                         &constructClass,
                         NULL);

static void
constructClass
  (
    Machine_Fonts_FontsContext_Class* self
  )
{
  ((Ring3_FontsContext_Class*)self)->createFont = (Ring3_Font * (*)(Ring3_FontsContext*, Ring2_String*, Ring2_Integer)) & createFont;
}

static Ring3_Font*
createFont
  (
    Machine_Fonts_FontsContext* self,
    Ring2_String* path,
    Ring2_Integer pointSize
  )
{ return (Ring3_Font*)Machine_Fonts_Font_create((Ring3_FontsContext*)self, path, pointSize); }

static void
destruct
  (
    Machine_Fonts_FontsContext* self
  )
{
  self->library = NULL;
  if (0 == --g_referenceCount) {
    FT_Done_FreeType(g_library);
  }
}

static void
visit
  (
    Machine_Fonts_FontsContext* self
  )
{
  if (self->videoContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->videoContext);
  }
  if (self->imageContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->imageContext);
  }
}

void
Machine_Fonts_FontsContext_construct
  (
    Machine_Fonts_FontsContext* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring3_FontsContext_construct((Ring3_FontsContext*)self, numberOfArguments, arguments);
  self->videoContext = (Ring3_VisualsContext*)Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 0, Ring3_VisualsContext_getType());
  self->imageContext = (Ring3_ImagesContext *)Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 1, Ring3_ImagesContext_getType());
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

Ring1_NoDiscardReturn() Machine_Fonts_FontsContext*
Machine_Fonts_FontsContext_create
  (
    Ring3_VisualsContext* videoContext,
    Ring3_ImagesContext *imagesContext
  )
{
  Machine_Type* ty = Machine_Fonts_FontsContext_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[2];
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,videoContext));
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,imagesContext));
  Machine_Fonts_FontsContext* self = Ring1_cast(Machine_Fonts_FontsContext*,
                                                Machine_allocateClassObject(ty,
                                                                            NUMBER_OF_ARGUMENTS,
                                                                            arguments));
  return self;
}
