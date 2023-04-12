/// @file Ring3/Fonts/FreeType2/Font.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_FONTS_FREETYPE2_FONT_H_INCLUDED)
#define RING3_FONTS_FREETYPE2_FONT_H_INCLUDED

#if !defined(RING3_FONTS_FREETYPE2_PRIVATE)
#error("Do not include `Ring3/Fonts/FreeType2/Font.h` directly. Include `Ring3/Fonts/FreeType2/_Include.h` instead.")
#endif

#include "Ring3/Visuals/_Include.h"


MACHINE_DECLARE_CLASSTYPE(Machine_Fonts_Font)

/// @brief Load a font of the specified size.
/// @param fontsContext The fonts context.
/// @param path The path.
/// @param pointSize The point size.
/// @return A pointer to the font on success, null on failure.
Machine_Fonts_Font* Machine_Fonts_Font_create(Ring3_FontsContext* fontsContext, Ring2_String *path, Ring2_Integer pointSize);


#endif // MACHINE_FONTS_FONT_H_INCLUDED
