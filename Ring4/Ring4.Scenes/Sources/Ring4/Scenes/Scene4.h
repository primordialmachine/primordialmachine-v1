#if !defined(SCENE4_H_INCLUDED)
#define SCENE4_H_INCLUDED

#include "Scene.h"

MACHINE_DECLARE_CLASSTYPE(Scene4)

void
Scene4_construct
  (
    Scene4* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Scene4*
Scene4_create
  (
    Ring3_VisualsContext* visualsContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  );

#endif // SCENE4_H_INCLUDED
