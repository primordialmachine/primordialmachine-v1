/// @file Fonts.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_FONTS_FONTSCONTEXT_H_INCLUDED)
#define MACHINE_FONTS_FONTSCONTEXT_H_INCLUDED



#if !defined(MACHINE_FONTS_PRIVATE)
#error("Do not include this file directly, include `_Fonts.h` instead.")
#endif
#include "_Video.h"
#include <ft2build.h>
#include FT_FREETYPE_H



MACHINE_DECLARE_CLASSTYPE(Machine_Fonts_FontsContext);

struct Machine_Fonts_FontsContext_Class {
  Machine_FontsContext_Class parent;
};

struct Machine_Fonts_FontsContext {
  Machine_FontsContext parent;
  Machine_VideoContext* videoContext;
  Machine_ImagesContext* imageContext;
  FT_Library *library;
};

/// @brief Construct this fonts context.
/// @param self This fonts context.
/// @param numberOfArguments, arguments The arguments.
/// <code>(Machine.ImagesContext imagesContext)</code>
void Machine_Fonts_FontsContext_construct(Machine_Fonts_FontsContext* self, size_t numberOfArguments, Machine_Value const* arguments);

Machine_Fonts_FontsContext* Machine_Fonts_FontsContext_create(Machine_VideoContext* videoContext, Machine_ImagesContext* imagesContext);



#endif // MACHINE_FONTS_FONTSCONTEXT_H_INCLUDED
