/// @file Video/Texture.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_TEXTURE_H_INCLUDED)
#define MACHINE_VIDEO_TEXTURE_H_INCLUDED



#if !defined(MACHINE_VIDEO_PRIVATE)
#error("Do not include this file directly, include `_Video.h` instead.")
#endif

#include "_Runtime.h"



MACHINE_DECLARE_CLASSTYPE(Machine_Texture);

struct Machine_Texture_Class {
  Machine_Object_Class parent;
};

struct Machine_Texture {
  Machine_Object parent;
};

/// @brief Construct this texture.
/// @param self This texture.
/// @param numberOfArguments, arguments The arguments.
void Machine_Texture_construct(Machine_Texture* self, size_t numberOfArguments, Machine_Value const* arguments);



#endif // MACHINE_VIDEO_TEXTURE_H_INCLUDED
