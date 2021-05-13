#if !defined(SCENE2_H_INCLUDED)
#define SCENE2_H_INCLUDED

#include "scene.h"

typedef struct Scene2 Scene2;

void Scene2_construct(Scene2* self, size_t numberOfArguments, const Machine_Value* arguments);

Scene2* Scene2_create();

#endif // SCENE2_H_INCLUDED
