#if !defined(MACHINE_TEXTURE_H_INCLUDED)
#define MACHINE_TEXTURE_H_INCLUDED



#include "Machine.h"
#include "Images.h"
#include "UtilitiesGL.h"



typedef struct Machine_Texture Machine_Texture;

struct Machine_Texture {
  GLuint id;
};

/// @brief Create a texture from an image.
/// @param image A pointer to the image.
/// @return A pointer to the texture. 
Machine_Texture* Machine_Texture_create(Machine_Images_Image *image);

/// @brief Assign a texture to a texture unit.
/// @param uint The index of the unit.
/// @param texture The texture.
void Machine_Video_bindTexture(size_t unit, Machine_Texture *texture);

#endif // MACHINE_TEXTURE_H_INCLUDED
