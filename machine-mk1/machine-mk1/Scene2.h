#if !defined(SCENE2_H_INCLUDED)
#define SCENE2_H_INCLUDED



#include "Scene.h"



MACHINE_DECLARE_CLASSTYPE(Scene2)

void Scene2_construct(Scene2* self, size_t numberOfArguments, Machine_Value const* arguments);

Scene2* Scene2_create();



#endif // SCENE2_H_INCLUDED
