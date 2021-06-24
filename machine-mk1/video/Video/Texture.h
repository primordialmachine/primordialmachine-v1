#if !defined(MACHINE_VIDEO_TEXTURE_H_INCLUDED)
#define MACHINE_VIDEO_TEXTURE_H_INCLUDED



#include "_Runtime.h"



MACHINE_DECLARE_CLASSTYPE(Machine_Texture);

struct Machine_Texture {
  Machine_Object parent;
};

/// @brief Construct this texture.
/// @param self This texture.
/// @param numberOfArguments, arguments The arguments.
void Machine_Texture_construct(Machine_Texture* self, size_t numberOfArguments, const Machine_Value* arguments);



#endif // MACHINE_VIDEO_TEXTURE_H_INCLUDED
