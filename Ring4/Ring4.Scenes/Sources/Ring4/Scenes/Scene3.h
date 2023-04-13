#if !defined(SCENE3_H_INCLUDED)
#define SCENE3_H_INCLUDED

#include "Scene.h"

MACHINE_DECLARE_CLASSTYPE(Scene3);

void
Scene3_construct
  (
    Scene3* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Scene3*
Scene3_create
  (
    Ring3_VisualsContext* visualsContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  );

#endif // SCENE3_H_INCLUDED
