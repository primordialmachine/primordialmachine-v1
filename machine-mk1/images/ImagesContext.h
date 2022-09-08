#if !defined(MACHINE_IMAGES_IMAGESCONTEXT_H_INCLUDED)
#define MACHINE_IMAGES_IMAGESCONTEXT_H_INCLUDED



#if !defined(MACHINE_IMAGES_PRIVATE)
#error("Do not include `Images/ImagesContext.h` directly, include `_Images.h` instead.")
#endif
#include "_Video.h"



MACHINE_DECLARE_CLASSTYPE(Machine_Images_ImagesContext);

struct Machine_Images_ImagesContext_Class {
  Machine_ImagesContext_Class parent;
};

struct Machine_Images_ImagesContext {
  Machine_ImagesContext parent;
};

void Machine_Images_ImagesContext_construct(Machine_Images_ImagesContext* self, size_t numberOfArguments, Ring2_Value const* arguments);

Machine_Images_ImagesContext *Machine_Images_ImagesContext_create();



#endif // MACHINE_IMAGES_IMAGESCONTEXT_H_INCLUDED
