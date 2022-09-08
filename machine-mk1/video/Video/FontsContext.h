/// @file Video/FontsContext.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_FONTSCONTEXT_H_INCLUDED)
#define MACHINE_VIDEO_FONTSCONTEXT_H_INCLUDED

#include "Video/_header.i"

MACHINE_DECLARE_CLASSTYPE(Machine_FontsContext);

struct Machine_FontsContext_Class {
  Machine_Object_Class parent;
  Machine_Font* (*createFont)(Machine_FontsContext* self, Ring2_String* path,
                              Ring2_Integer pointSize);
};

struct Machine_FontsContext {
  Machine_Object parent;
};

/// @brief Construct this images context.
/// @param self This font context.
/// @param numberOfArguments, arguments The arguments.
void Machine_FontsContext_construct(Machine_FontsContext* self, size_t numberOfArguments,
                                    Ring2_Value const* arguments);

/// @brief Create a font from a file given the pathname of the file and the font size in points.
/// @param self This font context.
/// @param path The path of the file.
/// @param pointSize The font size in points.
/// @return The font.
Machine_Font* Machine_FontsContext_createFont(Machine_FontsContext* self, Ring2_String* path,
                                              Ring2_Integer pointSize);

#endif // MACHINE_VIDEO_IMAGESCONTEXT_H_INCLUDED
