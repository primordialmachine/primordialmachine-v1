/// @file Video/FontsContext.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_FONTSCONTEXT_H_INCLUDED)
#define MACHINE_VIDEO_FONTSCONTEXT_H_INCLUDED

#if !defined(MACHINE_VIDEO_PRIVATE)
#error("Do not include this file directly, include `_Video.h` instead.")
#endif
#include "_Runtime.h"
typedef struct Machine_Font Machine_Font;

MACHINE_DECLARE_CLASSTYPE(Machine_FontsContext);

struct Machine_FontsContext_Class {
  Machine_Object_Class parent;
  Machine_Font* (*createFont)(Machine_FontsContext* self, Machine_String* path,
                              Machine_Integer pointSize);
};

struct Machine_FontsContext {
  Machine_Object parent;
};

/// @brief Construct this images context.
/// @param self This font context.
/// @param numberOfArguments, arguments The arguments.
void Machine_FontsContext_construct(Machine_FontsContext* self, size_t numberOfArguments,
                                    const Machine_Value* arguments);

/// @brief Create a font from a file given the pathname of the file and the font size in points.
/// @param self This font context.
/// @param path The path of the file.
/// @param pointSize The font size in points.
/// @return The font.
Machine_Font* Machine_FontsContext_createFont(Machine_FontsContext* self, Machine_String* path,
                                              Machine_Integer pointSize);

#endif // MACHINE_VIDEO_IMAGESCONTEXT_H_INCLUDED
