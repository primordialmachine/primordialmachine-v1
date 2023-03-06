/// @file Font.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_FONTS_FONT_H_INCLUDED)
#define MACHINE_FONTS_FONT_H_INCLUDED



#if !defined(MACHINE_FONTS_PRIVATE)
#error("Do not include `Fonts/Font.h` directly. Include `_Fonts.h` instead.")
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
