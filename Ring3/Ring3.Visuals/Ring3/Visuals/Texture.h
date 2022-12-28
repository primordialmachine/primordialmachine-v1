/// @file Ring3/Visuals/Texture.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_TEXTURE_H_INCLUDED)
#define RING3_VISUALS_TEXTURE_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/Texture.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/_Include.h"

/// @brief The base of all textures.
MACHINE_DECLARE_CLASSTYPE(Ring3_Texture);

struct Ring3_Texture_Class {
  Machine_Object_Class parent;
};

struct Ring3_Texture {
  Machine_Object parent;
};

/// @brief Construct this texture.
/// @param self This texture.
/// @param numberOfArguments, arguments The arguments.
void
Ring3_Texture_construct
  (
    Ring3_Texture* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

#endif // RING3_VISUALS_TEXTURE_H_INCLUDED
