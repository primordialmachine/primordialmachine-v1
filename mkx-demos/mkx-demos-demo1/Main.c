/// @file Main.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if defined(__cplusplus)
extern "C" {
#endif

#include "Ring3/Launcher/_Include.h"
#include "Ring4/Scenes/_Include.h"
#include <stdio.h>
#include <stdlib.h>


static Scene* g_scene = NULL;

static void
loadIcons
  (
  )
{
  static const char* PATHS[] = {
#define WINDOWS10_BLURRYICONHACK (1)
#if WINDOWS10_BLURRYICONHACK == 0
    "primordialmachine-16x16.png",
    "primordialmachine-20x20.png",
#endif
    "primordialmachine-24x24.png",
    "primordialmachine-32x32.png",
    "primordialmachine-40x40.png",
    "primordialmachine-48x48.png",
    "primordialmachine-64x64.png",
    "primordialmachine-96x96.png",
    "primordialmachine-110x110.png",
    "primordialmachine-114x114.png",
    "primordialmachine-135x135.png",
    "primordialmachine-140x140.png",
    "primordialmachine-180x180.png",
    "primordialmachine-256x256.png",
  };
  Ring2_Collections_List* vals = Ring1_cast(Ring2_Collections_List *, Ring2_Collections_ArrayList_create());
  for (size_t i = 0, n = (sizeof(PATHS) / sizeof(const char*)); i < n; ++i) {
    Ring3_Image* image = Ring3_ImagesContext_createImageFromPath(Ring3_Launcher_getImagesContext(),
                                                                 Ring2_String_fromC(false, PATHS[i]));
    Ring2_Value val;
    Ring2_Value_setObject(&val, (Machine_Object*)image);
    Ring2_Collections_List_append(vals, val);
  }
  Ring3_Canvas_setCanvasIcons(Ring3_Launcher_getCanvas(), vals);
}

static void
run
  (
    Scene* self
  )
{
  Ring2_Integer oldWidth, oldHeight;
  Ring3_Canvas_getFrameBuffersSize(Ring3_Launcher_getCanvas(),
                                   &oldWidth,
                                   &oldHeight);

  while (!Ring3_Canvas_getQuitRequested(Ring3_Launcher_getCanvas())) {
    Ring2_Integer newWidth, newHeight;
    Ring3_Canvas_getFrameBuffersSize(Ring3_Launcher_getCanvas(),
                                     &newWidth,
                                     &newHeight);
    if (oldWidth != newWidth || oldHeight != newHeight) {
      Scene_onCanvasSizeChanged(self, Ring3_CanvasSizeChangedEvent_create((Ring2_Real32)newWidth,
                                                                          (Ring2_Real32)newHeight));
      oldWidth = newWidth;
      oldHeight = newHeight;
    }
    Scene_onUpdate(self, (Ring2_Real32)oldWidth,
                         (Ring2_Real32)oldHeight);
    Ring2_Gc_run(Ring2_Gc_get(), NULL);
    Ring3_Canvas_swapFrameBuffers(Ring3_Launcher_getCanvas());
    Ring3_Canvas_pollEvents(Ring3_Launcher_getCanvas());
  }
}

static void
onMousePointerEvent
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Scene* self = Ring1_cast(Scene*,Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                        arguments,
                                                                        0,
                                                                        Scene_getType()));
  Ring3_MousePointerEvent* event = Ring1_cast(Ring3_MousePointerEvent*,
                                              Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                                    arguments,
                                                                                    1,
                                                                                    Ring3_MousePointerEvent_getType()));
  Scene_onMousePointerEvent(self, event);
  Ring2_Value_setVoid(result, Ring2_Void_Void);
}

static void
onMouseButtonEvent
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Scene* self = Ring1_cast(Scene*,Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                        arguments,
                                                                        0,
                                                                        Scene_getType()));
  Ring3_MouseButtonEvent* event = Ring1_cast(Ring3_MouseButtonEvent*,Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                                                           arguments,
                                                                                                           1,
                                                                                                           Ring3_MouseButtonEvent_getType()));
  Scene_onMouseButtonEvent(self, event);
  Ring2_Value_setVoid(result, Ring2_Void_Void);
}

static void
onKeyboardKeyEvent
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Scene* self = Ring1_cast(Scene*, Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                         arguments,
                                                                         0,
                                                                         Scene_getType()));
  Ring3_KeyboardKeyEvent* event = Ring1_cast(Ring3_KeyboardKeyEvent*, Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                                                            arguments,
                                                                                                            1,
                                                                                                            Ring3_KeyboardKeyEvent_getType()));
  Scene_onKeyboardKeyEvent(self, event);
  Ring2_Value_setVoid(result, Ring2_Void_Void);
}

static void
main0
  (
  )
{
  Ring3_Canvas_maximizeCanvas(Ring3_Launcher_getCanvas());
  loadIcons();
  Ring2_JumpTarget jumpTarget1; // To shutdown input.
  Ring2_pushJumpTarget(&jumpTarget1);
  if (!setjmp(jumpTarget1.environment)) {
    g_scene = (Scene*)Scene5_create(Ring3_Launcher_getVisualsContext(),
                                    Ring3_Launcher_getImagesContext(),
                                    Ring3_Launcher_getFontsContext());
    Ring3_Canvas_subscribeKeyboardKeyPressedEvent(Ring3_Launcher_getCanvas(),
                                                  Ring1_cast(Machine_Object*, g_scene), &onKeyboardKeyEvent);
    Ring3_Canvas_subscribeKeyboardKeyReleasedEvent(Ring3_Launcher_getCanvas(),
                                                   Ring1_cast(Machine_Object*, g_scene), &onKeyboardKeyEvent);
    Ring3_Canvas_subscribeMousePointerMovedEvent(Ring3_Launcher_getCanvas(),
                                                 Ring1_cast(Machine_Object*, g_scene), &onMousePointerEvent);
    Ring3_Canvas_subscribeMouseButtonPressedEvent(Ring3_Launcher_getCanvas(),
                                                  Ring1_cast(Machine_Object*, g_scene), &onMouseButtonEvent);
    Ring3_Canvas_subscribeMouseButtonReleasedEvent(Ring3_Launcher_getCanvas(),
                                                   Ring1_cast(Machine_Object*, g_scene), &onMouseButtonEvent);
    Scene_onStartup(g_scene);

    Ring2_JumpTarget jumpTarget2; // To shutdown scene.
    Ring2_pushJumpTarget(&jumpTarget2);
    if (!setjmp(jumpTarget2.environment)) {
      Ring2_Gc_lock(g_scene);
      Ring2_Gc_run(Ring2_Gc_get(), NULL);

      Ring2_Integer width, height;
      Ring3_Canvas_getFrameBuffersSize(Ring3_Launcher_getCanvas(),
                                       &width,
                                       &height);
      Scene_onCanvasSizeChanged(g_scene, Ring3_CanvasSizeChangedEvent_create((Ring2_Real32)width,
                                                                             (Ring2_Real32)height));

      run(g_scene);
      Ring2_popJumpTarget();

      Scene* s = g_scene;
      g_scene = NULL;
      Scene_onShutdown(s);
      Ring2_Gc_unlock(s);
    } else {
      Scene* s = g_scene;
      g_scene = NULL;
      Scene_onShutdown(s);
      Ring2_Gc_unlock(s);
      Ring2_popJumpTarget();
      Ring2_jump();
    }
    Ring2_popJumpTarget();
  } else {
    Ring2_popJumpTarget();
    Ring2_jump();
  }
}

static void
main1
  (
  )
{
  Ring2_JumpTarget jumpTarget1;
  bool videoStartedUp = false;
  Ring2_pushJumpTarget(&jumpTarget1);
  if (!setjmp(jumpTarget1.environment)) {
    Ring3_Launcher_startup();
    videoStartedUp = true;
    main0();
  }
  Ring2_popJumpTarget();
  if (videoStartedUp) {
    Ring3_Launcher_shutdown();
    videoStartedUp = false;
  }
}

int
main
  (
  )
{
  if (Ring2_Context_startup()) {
    fprintf(stderr, "%s:%d: Machine_startup() failed\n", __FILE__, __LINE__);
    return EXIT_FAILURE;
  }
  main1();
  Ring1_Status status = Ring1_Status_get();
  Ring2_Context_shutdown();
  return status == Ring1_Status_Success ? EXIT_SUCCESS : EXIT_FAILURE;
}

#if defined(__cplusplus)
}
#endif
