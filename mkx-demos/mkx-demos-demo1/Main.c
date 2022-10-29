/// @file Main.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if defined(__cplusplus)
extern "C" {
#endif

#include "Ring1/Intrinsic.h"
#include "Ring2/Library/_Include.h"
#include "_Launcher.h"
#include "_Fonts.h"
#include "_Images.h"
#include "_Scenes.h"
#include <stdio.h>
#include <stdlib.h>

static Scene* g_scene = NULL;

static void loadIcons() {
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
    Machine_Image* image = Machine_ImagesContext_createFromPath(
        Machines_DefaultImages_createContext(), Ring2_String_fromC(PATHS[i]));
    Ring2_Value val;
    Ring2_Value_setObject(&val, (Machine_Object*)image);
    Ring2_Collections_List_append(vals, val);
  }
  Machine_Video_Canvas_setCanvasIcons(Machine_getVideoCanvas(), vals);
}

static void run(Scene* self) {
  Ring2_Integer oldWidth, oldHeight;
  Machine_Video_Canvas_getFrameBuffersSize(Machine_getVideoCanvas(), &oldWidth, &oldHeight);

  while (!Machine_Video_Canvas_getQuitRequested(Machine_getVideoCanvas())) {
    Ring2_Integer newWidth, newHeight;
    Machine_Video_Canvas_getFrameBuffersSize(Machine_getVideoCanvas(), &newWidth, &newHeight);
    if (oldWidth != newWidth || oldHeight != newHeight) {
      Scene_onCanvasSizeChanged(self, Machine_CanvasSizeChangedEvent_create(
                                          (Ring2_Real32)newWidth, (Ring2_Real32)newHeight));
      oldWidth = newWidth;
      oldHeight = newHeight;
    }
    Scene_onUpdate(self, (Ring2_Real32)oldWidth, (Ring2_Real32)oldHeight);
    Ring2_Gc_run(Ring2_Gc_get(), NULL);
    Machine_Video_Canvas_swapFrameBuffers(Machine_getVideoCanvas());
    Machine_Video_Canvas_pollEvents(Machine_getVideoCanvas());
  }
}

static void onMousePointerEvent(Ring2_Context* context, Ring2_Value *result, size_t numberOfArguments, Ring2_Value const* arguments) {
  Scene* self = (Scene*)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 0,
                                                             Scene_getType());
  Machine_MousePointerEvent* event
      = (Machine_MousePointerEvent*)Machine_Extensions_getObjectArgument(
          numberOfArguments, arguments, 1, Machine_MousePointerEvent_getType());
  Scene_onMousePointerEvent(self, event);
  Ring2_Value_setVoid(result, Ring2_Void_Void);
}

static void onMouseButtonEvent(Ring2_Context* context, Ring2_Value *result, size_t numberOfArguments, Ring2_Value const* arguments) {
  Scene* self = (Scene*)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 0,
                                                             Scene_getType());
  Machine_MouseButtonEvent* event = (Machine_MouseButtonEvent*)Machine_Extensions_getObjectArgument(
      numberOfArguments, arguments, 1, Machine_MouseButtonEvent_getType());
  Scene_onMouseButtonEvent(self, event);
  Ring2_Value_setVoid(result, Ring2_Void_Void);
}

static void onKeyboardKeyEvent(Ring2_Context* context, Ring2_Value *result, size_t numberOfArguments, Ring2_Value const* arguments) {
  Scene* self = (Scene*)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 0,
                                                             Scene_getType());
  Machine_KeyboardKeyEvent* event = (Machine_KeyboardKeyEvent*)Machine_Extensions_getObjectArgument(
      numberOfArguments, arguments, 1, Machine_KeyboardKeyEvent_getType());
  Scene_onKeyboardKeyEvent(self, event);
  Ring2_Value_setVoid(result, Ring2_Void_Void);
}

void main0() {
  Machine_Video_Canvas_maximizeCanvas(Machine_getVideoCanvas());
  loadIcons();
  Ring2_JumpTarget jumpTarget1; // To shutdown input.
  Ring2_pushJumpTarget(&jumpTarget1);
  if (!setjmp(jumpTarget1.environment)) {
    g_scene = (Scene*)Scene5_create(Machine_getVideoContext());
    Machine_Video_Canvas_subscribeKeyboardKeyPressedEvent(
        Machine_getVideoCanvas(), (Machine_Object*)g_scene, &onKeyboardKeyEvent);
    Machine_Video_Canvas_subscribeKeyboardKeyReleasedEvent(
        Machine_getVideoCanvas(), (Machine_Object*)g_scene, &onKeyboardKeyEvent);
    Machine_Video_Canvas_subscribeMousePointerMovedEvent(
        Machine_getVideoCanvas(), (Machine_Object*)g_scene, &onMousePointerEvent);
    Machine_Video_Canvas_subscribeMouseButtonPressedEvent(
        Machine_getVideoCanvas(), (Machine_Object*)g_scene, &onMouseButtonEvent);
    Machine_Video_Canvas_subscribeMouseButtonReleasedEvent(
        Machine_getVideoCanvas(), (Machine_Object*)g_scene, &onMouseButtonEvent);
    Scene_onStartup(g_scene);

    Ring2_JumpTarget jumpTarget2; // To shutdown scene.
    Ring2_pushJumpTarget(&jumpTarget2);
    if (!setjmp(jumpTarget2.environment)) {
      Ring2_Gc_lock(g_scene);
      Ring2_Gc_run(Ring2_Gc_get(), NULL);

      Ring2_Integer width, height;
      Machine_Video_Canvas_getFrameBuffersSize(Machine_getVideoCanvas(), &width, &height);
      Scene_onCanvasSizeChanged(g_scene, Machine_CanvasSizeChangedEvent_create(
                                             (Ring2_Real32)width, (Ring2_Real32)height));

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

void main1() {
  Ring2_JumpTarget jumpTarget1;
  bool videoStartedUp = false;
  Ring2_pushJumpTarget(&jumpTarget1);
  if (!setjmp(jumpTarget1.environment)) {
    Machine_Video_startup();
    videoStartedUp = true;
    main0();
  }
  Ring2_popJumpTarget();
  if (videoStartedUp) {
    Machine_Video_shutdown();
    videoStartedUp = false;
  }
}

int main() {
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
