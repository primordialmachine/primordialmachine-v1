#if !defined(MACHINE_SCENES_RECTANGLE2SCENE_H_INCLUDED)
#define MACHINE_SCENES_RECTANGLE2SCENE_H_INCLUDED

#include "Ring4/Scenes/Scene.h"

MACHINE_DECLARE_CLASSTYPE(Rectangle2Scene)

void
Rectangle2Scene_construct
  (
    Rectangle2Scene* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Rectangle2Scene*
Rectangle2Scene_create
  (
    Ring3_VisualsContext* videoContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  );

#endif // MACHINE_SCENES_RECTANGLE2SCENE_H_INCLUDED
