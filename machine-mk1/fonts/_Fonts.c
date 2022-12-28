/// @file _Fonts.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_FONTS_PRIVATE (1)
#include "_Fonts.h"
#include "FontsContext.h"



Machine_FontsContext* Machine_DefaultFonts_createContext(Machine_VideoContext* videoContext, Ring3_ImagesContext* imagesContext) {
  return (Machine_FontsContext*)Machine_Fonts_FontsContext_create(videoContext, imagesContext);
}
