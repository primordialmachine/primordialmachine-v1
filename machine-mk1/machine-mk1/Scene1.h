#if !defined(SCENE1_H_INCLUDED)
#define SCENE1_H_INCLUDED

#include "scene.h"

typedef struct Scene1 Scene1;

void Scene1_construct(Scene1* self, size_t numberOfArguments, const Machine_Value* arguments);

Scene1* Scene1_create();

#endif // SCENE1_H_INCLUDED
