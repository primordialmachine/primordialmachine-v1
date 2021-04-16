#if !defined(MACHINE_SCENE_H_INCLUDED)
#define MACHINE_SCENE_H_INCLUDED

typedef struct Scene Scene;

typedef int Scene_StartupCallback(Scene* self);

typedef int Scene_UpdateCallback(Scene* self, float width, float height);

typedef void Scene_ShutdownCallback(Scene* self);

struct Scene {

  Scene_StartupCallback* startup;

  Scene_UpdateCallback* update;

  Scene_ShutdownCallback* shutdown;
};

void Scene_visit(Scene* self);

int Scene_construct(Scene* self);

void Scene_destruct(Scene* self);

int Scene_startup(Scene* scene);

int Scene_update(Scene* self, float width, float height);

void Scene_shutdown(Scene* self);

#endif // MACHINE_SCENE_H_INCLUDED
