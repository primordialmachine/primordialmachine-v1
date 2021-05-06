#if !defined(MACHINE_SCENE_H_INCLUDED)
#define MACHINE_SCENE_H_INCLUDED

typedef struct Scene Scene;

typedef void Scene_OnCanvaSizeChangedCallback(Scene* self, float width, float height);

typedef void Scene_StartupCallback(Scene* self);

typedef void Scene_UpdateCallback(Scene* self, float width, float height);

typedef void Scene_ShutdownCallback(Scene* self);

/// The lifecycle of a scene
/// (0) Scene object is created.
/// (1) Call to "startup". If this call succeeds then proceed at (2). Otherwise proceed at (1) or at (4).
/// (2) Possibly empty sequence of calls to "onCanvasSizeChanged", "onUpdate", "onRender".
/// (3) Call to "shutdown". Either continue at (1) or (4).
/// (4) Scene object is destroyed.
struct Scene {

  Scene_OnCanvaSizeChangedCallback* onCanvasSizeChanged;

  Scene_StartupCallback* startup;

  Scene_UpdateCallback* update;

  Scene_ShutdownCallback* shutdown;
};

void Scene_visit(Scene* self);

int Scene_construct(Scene* self);

void Scene_destruct(Scene* self);

/// @brief Invoked exactly once before a sequence of calls to onCanvasSizeChanged and update.
/// @param scene This scene.
void Scene_startup(Scene* scene);

/// @brief Invoked if the canvas size has changed.
/// @param self This scene.
/// @param width The new width.
/// @param height The new height.
void Scene_onCanvaSizeChanged(Scene* self, float width, float height);

void Scene_update(Scene* self, float width, float height);

void Scene_shutdown(Scene* self);

#endif // MACHINE_SCENE_H_INCLUDED
