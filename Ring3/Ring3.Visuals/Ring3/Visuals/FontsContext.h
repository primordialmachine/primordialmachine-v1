/// @file Ring3/Visuals/FontsContext.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_FONTSCONTEXT_H_INCLUDED)
#define RING3_VISUALS_FONTSCONTEXT_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/FontsContext.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"
typedef struct Ring3_Font Ring3_Font;

MACHINE_DECLARE_CLASSTYPE(Ring3_FontsContext);

struct Ring3_FontsContext_Class {
  Machine_Object_Class parent;
  Ring3_Font*
  (*createFont)
    (
      Ring3_FontsContext* self,
      Ring2_String* path,
      Ring2_Integer pointSize
    );
};

struct Ring3_FontsContext {
  Machine_Object parent;
};

/// @brief Construct this fonts context.
/// @param self This font context.
/// @param numberOfArguments, arguments The arguments.
void
Ring3_FontsContext_construct
  (
    Ring3_FontsContext* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Create a font from a file given the pathname of the file and the font size in points.
/// @param self This font context.
/// @param path The path of the file.
/// @param pointSize The font size in points.
/// @return The font.
Ring3_Font*
Ring3_FontsContext_createFont
  (
    Ring3_FontsContext* self,
    Ring2_String* path,
    Ring2_Integer pointSize
  );

#endif // RING3_VISUALS_FONTSCONTEXT_H_INCLUDED
