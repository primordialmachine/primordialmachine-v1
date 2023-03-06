/// @file _Fonts.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_FONTS_PRIVATE (1)
#include "_Fonts.h"
#include "FontsContext.h"



Ring3_FontsContext* Machine_DefaultFonts_createContext(Ring3_VisualsContext* videoContext, Ring3_ImagesContext* imagesContext) {
  return (Ring3_FontsContext*)Machine_Fonts_FontsContext_create(videoContext, imagesContext);
}
