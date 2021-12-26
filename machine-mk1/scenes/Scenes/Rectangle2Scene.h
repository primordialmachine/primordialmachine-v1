#if !defined(MACHINE_SCENES_RECTANGLE2SCENE_H_INCLUDED)
#define MACHINE_SCENES_RECTANGLE2SCENE_H_INCLUDED

#include "Scenes/Scene.h"

MACHINE_DECLARE_CLASSTYPE(Rectangle2Scene)

void Rectangle2Scene_construct(Rectangle2Scene* self, size_t numberOfArguments,
                               Machine_Value const* arguments);

Rectangle2Scene* Rectangle2Scene_create(Machine_VideoContext *videoContext);

#endif // MACHINE_SCENES_RECTANGLE2SCENE_H_INCLUDED
