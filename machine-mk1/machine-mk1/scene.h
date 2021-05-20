#if !defined(MACHINE_SCENE_H_INCLUDED)
#define MACHINE_SCENE_H_INCLUDED

#include "_Runtime.h"

MACHINE_DECLARE_CLASSTYPE(Scene)

typedef void Scene_OnCanvaSizeChangedCallback(Scene* self, float width, float height);

typedef void Scene_OnStartupCallback(Scene* self);

typedef void Scene_OnUpdateCallback(Scene* self, float width, float height);

typedef void Scene_OnShutdownCallback(Scene* self);

typedef void Scene_OnMousePointerEventCallback(Scene* self, float x, float y);

typedef void Scene_OnMouseButtonEventCallback(Scene* self, float x, float y, int index, int action);

/// The lifecycle of a scene
/// (0) Scene object is created.
/// (1) Call to "startup". If this call succeeds then proceed at (2). Otherwise proceed at (1) or at (4).
/// (2) Possibly empty sequence of calls to "onCanvasSizeChanged", "onUpdate", "onRender".
/// (3) Call to "shutdown". Either continue at (1) or (4).
/// (4) Scene object is destroyed.
struct Scene {

  Scene_OnCanvaSizeChangedCallback* onCanvasSizeChanged;

  Scene_OnMousePointerEventCallback* onMousePointerEvent;
  Scene_OnMouseButtonEventCallback* onMouseButtonEvent;

  Scene_OnUpdateCallback* onUpdate;

  Scene_OnStartupCallback* onStartup;

  Scene_OnShutdownCallback* onShutdown;
};

void Scene_visit(Scene* self);

void Scene_construct(Scene* self, size_t numberOfArguments, const Machine_Value* arguments);

void Scene_destruct(Scene* self);

/// @brief Invoked exactly once before a sequence of calls to onCanvasSizeChanged and update.
/// @param scene This scene.
void Scene_onStartup(Scene* scene);

/// @brief Invoked if the canvas size has changed.
/// @param self This scene.
/// @param width The new width.
/// @param height The new height.
void Scene_onCanvaSizeChanged(Scene* self, float width, float height);

/// @brief A button or key was pressed.
#define Machine_Pressed (1)

/// @brief A button or key was released.
#define Machine_Released (2)

/// @brief An event handler is a method invoked if an object receives an event.
/// The naming convention is <code>Type.on&lt;Event&gt;Event(...)</code> e.g.
/// <code>Scene.onMousePointerEvent(...)</code>.
/// This macro merely used to annotate such functions.
#define MACHINE_EVENTS_SINK()

/// @brief Invoked if a mouse pointer event was received.
/// @param self This scene.
/// @param x, y The position in canvas coordinates.
/// @remarks Canvas coordinates have their origin in the left top corner of the canvas with the positive x axis pointing right and the positive y axis pointing down.
MACHINE_EVENTS_SINK() void Scene_onMousePointerEvent(Scene* self, float x, float y);

/// @brief Invoked if a mouse button event was received.
/// @param self This scene.
/// @param x, y The position in canvas coordinates.
/// @param i The button index.
/// @param action The action (either Machine_Pressed or Machine_Released).
/// @remarks Canvas coordinates have their origin in the left top corner of the canvas with the positive x axis pointing right and the positive y axis pointing down.
MACHINE_EVENTS_SINK() void Scene_onMouseButtonEvent(Scene *self, float x, float y, int index, int action);

void Scene_onUpdate(Scene* self, float width, float height);

void Scene_onShutdown(Scene* self);

#endif // MACHINE_SCENE_H_INCLUDED
