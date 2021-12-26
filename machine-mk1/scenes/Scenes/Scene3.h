#if !defined(SCENE3_H_INCLUDED)
#define SCENE3_H_INCLUDED

#include "Scene.h"

MACHINE_DECLARE_CLASSTYPE(Scene3);

void Scene3_construct(Scene3* self, size_t numberOfArguments, Machine_Value const* arguments);

Scene3* Scene3_create(Machine_VideoContext *videoContext);

#endif // SCENE3_H_INCLUDED
