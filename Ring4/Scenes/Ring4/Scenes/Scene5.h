#if !defined(SCENE5_H_INCLUDED)
#define SCENE5_H_INCLUDED

#include "Scene.h"

MACHINE_DECLARE_CLASSTYPE(Scene5)

void
Scene5_construct
  (
    Scene5* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Scene5*
Scene5_create
  (
    Ring3_VisualsContext* visualsContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  );

#endif // SCENE5_H_INCLUDED
