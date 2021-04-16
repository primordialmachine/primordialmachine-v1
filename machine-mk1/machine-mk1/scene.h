#if !defined(MACHINE_SCENE_H_INCLUDED)
#define MACHINE_SCENE_H_INCLUDED

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

#endif // MACHINE_SCENE_H_INCLUDED
