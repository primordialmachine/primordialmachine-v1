/// @file Ring3/Fonts/FreeType2/_Include.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_FONTS_FREETYPE2_PRIVATE (1)
#include "Ring3/Fonts/FreeType2/_Include.h"

#include "Ring3/Fonts/FreeType2/FontsContext.h"
#undef RING3_FONTS_FREETYPE2_PRIVATE


Ring1_NoDiscardReturn() Ring3_FontsContext*
Machine_DefaultFonts_createContext
  (
    Ring3_VisualsContext* videoContext,
    Ring3_ImagesContext* imagesContext
  )
{ return Ring1_cast(Ring3_FontsContext*, Machine_Fonts_FontsContext_create(videoContext, imagesContext)); }
