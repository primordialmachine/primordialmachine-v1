/// @file Ring3/Fonts/FreeType2/_Include.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_FONTS_FREETYPE2__INCLUDE_H_INCLUDED)
#define RING3_FONTS_FREETYPE2__INCLUDE_H_INCLUDED

#include "Ring3/Visuals/_Include.h"


Ring1_NoDiscardReturn() Ring3_FontsContext*
Machine_DefaultFonts_createContext
  (
    Ring3_VisualsContext* videoContext,
    Ring3_ImagesContext* imagesContext
  );


#endif // RING3_FONTS_FREETYPE2__INCLUDE_H_INCLUDED
