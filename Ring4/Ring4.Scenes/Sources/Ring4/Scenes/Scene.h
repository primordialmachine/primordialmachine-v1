#if !defined(MACHINE_SCENE_H_INCLUDED)
#define MACHINE_SCENE_H_INCLUDED

#include "Ring3/Input/_Include.h"
#include "Ring3/Visuals/_Include.h"

MACHINE_DECLARE_CLASSTYPE(Scene)

typedef void Scene_OnCanvaSizeChangedCallback(Scene* self, Ring3_CanvasSizeChangedEvent* event);

typedef void Scene_OnStartupCallback(Scene* self);

typedef void Scene_OnUpdateCallback(Scene* self, Ring2_Real32 width, Ring2_Real32 height);

typedef void Scene_OnShutdownCallback(Scene* self);

typedef void Scene_OnMousePointerEventCallback(Scene* self, Ring3_MousePointerEvent* event);

typedef void Scene_OnMouseButtonEventCallback(Scene* self, Ring3_MouseButtonEvent* event);

typedef void Scene_OnKeyboardKeyEventCallback(Scene* self, Ring3_KeyboardKeyEvent* event);

struct Scene_Class {
  Machine_Object_Class parent;

  Scene_OnCanvaSizeChangedCallback* onCanvasSizeChanged;

  Scene_OnMousePointerEventCallback* onMousePointerEvent;
  Scene_OnMouseButtonEventCallback* onMouseButtonEvent;
  Scene_OnKeyboardKeyEventCallback* onKeyboardKeyEvent;

  Scene_OnUpdateCallback* onUpdate;

  Scene_OnStartupCallback* onStartup;

  Scene_OnShutdownCallback* onShutdown;
};

/// The lifecycle of a scene
/// (0) Scene object is created.
/// (1) Call to "startup". If this call succeeds then proceed at (2). Otherwise proceed at (1) or at
/// (4). (2) Possibly empty sequence of calls to "onCanvasSizeChanged", "onUpdate", "onRender". (3)
/// Call to "shutdown". Either continue at (1) or (4). (4) Scene object is destroyed.
struct Scene {
  Machine_Object parent;
  Ring3_VisualsContext* visualsContext;
  Ring3_ImagesContext* imagesContext;
  Ring3_FontsContext* fontsContext;
};

/// @code
/// (
///   visualsContext : Ring3.VisualsContext,
///   imagesContext : Ring3.ImageContext,
///   fontsContext : Ring3.FontsContext
/// )
/// @endcode
void
Scene_construct
  (
    Scene* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Invoked exactly once before a sequence of calls to onCanvasSizeChanged and update.
/// @param self This scene.
void
Scene_onStartup
  (
    Scene* self
  );

/// @brief Invoked if the canvas size changed event was received.
/// @param self This scene.
/// @param event The event.
void
Scene_onCanvasSizeChanged
  (
    Scene* self,
    Ring3_CanvasSizeChangedEvent* event
  );

/// @brief Invoked if a mouse pointer event was received.
/// @param self This scene.
/// @param event The event.
/// @remarks Canvas coordinates have their origin in the left top corner of the canvas with the
/// positive x axis pointing right and the positive y axis pointing down.
void
Scene_onMousePointerEvent
  (
    Scene* self,
    Ring3_MousePointerEvent* event
  );

/// @brief Invoked if a mouse button event was received.
/// @param self This scene.
/// @param event The event.
/// @remarks Canvas coordinates have their origin in the left top corner of the canvas with the
/// positive x axis pointing right and the positive y axis pointing down.
void
Scene_onMouseButtonEvent
  (
    Scene* self,
    Ring3_MouseButtonEvent* event
  );

/// @brief Invoked if a keyboard key event was received.
/// @param self This scene.
/// @param event The event.
/// @remarks Canvas coordinates have their origin in the left top corner of the canvas with the
/// positive x axis pointing right and the positive y axis pointing down.
void
Scene_onKeyboardKeyEvent
  (
    Scene* self,
    Ring3_KeyboardKeyEvent* event
  );

void
Scene_onUpdate
  (
    Scene* self,
    Ring2_Real32 width,
    Ring2_Real32 height
  );

void
Scene_onShutdown
  (
    Scene* self
  );

/// @brief Get the video context of this scene.
/// @param self This scene.
/// @return The video context of this scene.
Ring1_NoDiscardReturn() Ring3_VisualsContext*
Scene_getVisualsContext
  (
    Scene* self
  );

/// @brief Get the fonts context of this scene.
/// @param self This scene.
/// @return The fonts context of this scene.
Ring1_NoDiscardReturn() Ring3_FontsContext*
Scene_getFontsContext
  (
    Scene* self
  );

/// @brief Get the images context of this scene.
/// @param self This scene.
/// @return The images context of this scene.
Ring1_NoDiscardReturn() Ring3_ImagesContext*
Scene_getImagesContext
  (
    Scene* self
  );

#endif // MACHINE_SCENE_H_INCLUDED
