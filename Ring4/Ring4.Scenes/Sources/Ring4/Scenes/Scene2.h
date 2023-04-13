#if !defined(SCENE2_H_INCLUDED)
#define SCENE2_H_INCLUDED

#include "Scene.h"

MACHINE_DECLARE_CLASSTYPE(Scene2)

void
Scene2_construct
  (
    Scene2* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Scene2*
Scene2_create
  (
    Ring3_VisualsContext* visualsContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  );

#endif // SCENE2_H_INCLUDED
