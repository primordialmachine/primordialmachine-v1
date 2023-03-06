#if !defined(SCENE1_H_INCLUDED)
#define SCENE1_H_INCLUDED

#include "Scene.h"

MACHINE_DECLARE_CLASSTYPE(Scene1)

void
Scene1_construct
  (
    Scene1* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Scene1*
Scene1_create
  (
    Ring3_VisualsContext* visualsContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  );

#endif // SCENE1_H_INCLUDED
