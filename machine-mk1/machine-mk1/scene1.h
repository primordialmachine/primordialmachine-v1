#if !defined(SCENE1_H_INCLUDED)
#define SCENE1_H_INCLUDED

#include "scene.h"

#if 0
typedef struct Scene Scene;

typedef int Scene_StartupCallback(Scene* scene);

typedef int Scene_UpdateCallback(Scene* scene, float width, float height);

typedef void Scene_ShutdownCallback(Scene* scene);

struct Scene {
  
  Scene_StartupCallback* startup;
  
  Scene_UpdateCallback* update;
  
  Scene_ShutdownCallback* shutdown;

};

int Scene_startup(Scene* scene);

int Scene_update(Scene* scene, float width, float height);

void Scene_shutdown(Scene* scene);

void Scene_destroy(Scene* scene);
#endif

Scene* Scene1_create();






#endif // SCENE1_H_INCLUDED
