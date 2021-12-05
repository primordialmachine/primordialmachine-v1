#if !defined(MACHINE_SCENES_RECTANGLE2SCENE_H_INCLUDED)
#define MACHINE_SCENES_RECTANGLE2SCENE_H_INCLUDED


#include "../Scene.h"


MACHINE_DECLARE_CLASSTYPE(Rectangle2Scene)

void Rectangle2Scene_construct(Rectangle2Scene* self, size_t numberOfArguments, Machine_Value const* arguments);

Rectangle2Scene* Rectangle2Scene_create();

#endif // MACHINE_SCENES_RECTANGLE2SCENE_H_INCLUDED
