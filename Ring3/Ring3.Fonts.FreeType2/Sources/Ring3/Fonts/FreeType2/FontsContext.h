/// @file Ring3/Fonts/FreeType2/Fonts.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_FONTS_FREETYPE2_FONTSCONTEXT_H_INCLUDED)
#define RING3_FONTS_FREETYPE2_FONTSCONTEXT_H_INCLUDED

#if !defined(RING3_FONTS_FREETYPE2_PRIVATE)
#error("Do not include `Ring3/Fonts/FreeType2/FontsContext.h` directly. Include `Ring3/Fonts/FreeType2/_Include.h` instead.")
#endif

#include "Ring3/Visuals/_Include.h"

#include <ft2build.h>
#include FT_FREETYPE_H



MACHINE_DECLARE_CLASSTYPE(Machine_Fonts_FontsContext);

struct Machine_Fonts_FontsContext_Class {
  Ring3_FontsContext_Class parent;
};

struct Machine_Fonts_FontsContext {
  Ring3_FontsContext parent;
  Ring3_VisualsContext* videoContext;
  Ring3_ImagesContext* imageContext;
  FT_Library *library;
};

/// @brief Construct this fonts context.
/// @param self This fonts context.
/// @param numberOfArguments, arguments The arguments.
/// <code>(Machine.ImagesContext imagesContext)</code>
void
Machine_Fonts_FontsContext_construct
  (
    Machine_Fonts_FontsContext* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Machine_Fonts_FontsContext*
Machine_Fonts_FontsContext_create
  (
    Ring3_VisualsContext* videoContext,
    Ring3_ImagesContext* imagesContext
  );


#endif // RING3_FONTS_FREETYPE2_FONTSCONTEXT_H_INCLUDED
