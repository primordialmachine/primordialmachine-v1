#if !defined(MACHINE_TEXTURE_H_INCLUDED)
#define MACHINE_TEXTURE_H_INCLUDED



#include "Machine.h"
#include "Images.h"
#include "UtilitiesGL.h"



typedef struct Machine_Texture Machine_Texture;

struct Machine_Texture {
  GLuint id;
};

Machine_Texture* Machine_Texture_create(Machine_Images_Image *image);


#endif // MACHINE_TEXTURE_H_INCLUDED
