#if !defined(SCENE4_H_INCLUDED)
#define SCENE4_H_INCLUDED

#include "Scene.h"

MACHINE_DECLARE_CLASSTYPE(Scene4)

void Scene4_construct(Scene4* self, size_t numberOfArguments, Machine_Value const* arguments);

Scene4* Scene4_create(Machine_VideoContext *videoContext);

#endif // SCENE4_H_INCLUDED
