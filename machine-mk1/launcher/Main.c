/// @file Main.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if defined(__cplusplus)
extern "C" {
#endif

#include "Video.h"
#include "_Collections.h"
#include "_Fonts.h"
#include "_Images.h"
#include "_Runtime.h"
#include "_Scenes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  Machine_List* vals = (Machine_List*)Machine_ArrayList_create();
  for (size_t i = 0, n = (sizeof(PATHS) / sizeof(const char*)); i < n; ++i) {
    Machine_Image* image = Machine_ImagesContext_createFromPath(
        Machines_DefaultImages_createContext(), Machine_String_create(PATHS[i], strlen(PATHS[i])));
    Machine_Value val;
    Machine_Value_setObject(&val, (Machine_Object*)image);
    Machine_List_append(vals, val);
  }
  Machine_Video_Canvas_setCanvasIcons(Machine_getVideoCanvas(), vals);
}

static void run(Scene* self) {
  Machine_Integer oldWidth, oldHeight;
  Machine_Video_Canvas_getFrameBuffersSize(Machine_getVideoCanvas(), &oldWidth, &oldHeight);

  while (!Machine_Video_Canvas_getQuitRequested(Machine_getVideoCanvas())) {
    Machine_Integer newWidth, newHeight;
    Machine_Video_Canvas_getFrameBuffersSize(Machine_getVideoCanvas(), &newWidth, &newHeight);
    if (oldWidth != newWidth || oldHeight != newHeight) {
      Scene_onCanvasSizeChanged(self, Machine_CanvasSizeChangedEvent_create(
                                          (Machine_Real)newWidth, (Machine_Real)newHeight));
      oldWidth = newWidth;
      oldHeight = newHeight;
    }
    Scene_onUpdate(self, (Machine_Real)oldWidth, (Machine_Real)oldHeight);
    Machine_update();
    Machine_Video_Canvas_swapFrameBuffers(Machine_getVideoCanvas());
    Machine_Video_Canvas_pollEvents(Machine_getVideoCanvas());
  }
}

static Machine_Value onMousePointerEvent(size_t numberOfArguments, Machine_Value const* arguments) {
  static Machine_Value const RESULT = { Machine_ValueFlag_Void, Machine_Void_Void };
  Scene* self = (Scene*)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 0,
                                                             Scene_getType());
  Machine_MousePointerEvent* event
      = (Machine_MousePointerEvent*)Machine_Extensions_getObjectArgument(
          numberOfArguments, arguments, 1, Machine_MousePointerEvent_getType());
  Scene_onMousePointerEvent(self, event);
  return RESULT;
}

static Machine_Value onMouseButtonEvent(size_t numberOfArguments, Machine_Value const* arguments) {
  static Machine_Value const RESULT = { Machine_ValueFlag_Void, Machine_Void_Void };
  Scene* self = (Scene*)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 0,
                                                             Scene_getType());
  Machine_MouseButtonEvent* event = (Machine_MouseButtonEvent*)Machine_Extensions_getObjectArgument(
      numberOfArguments, arguments, 1, Machine_MouseButtonEvent_getType());
  Scene_onMouseButtonEvent(self, event);
  return RESULT;
}

static Machine_Value onKeyboardKeyEvent(size_t numberOfArguments, Machine_Value const* arguments) {
  static Machine_Value const RESULT = { Machine_ValueFlag_Void, Machine_Void_Void };
  Scene* self = (Scene*)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 0,
                                                             Scene_getType());
  Machine_KeyboardKeyEvent* event = (Machine_KeyboardKeyEvent*)Machine_Extensions_getObjectArgument(
      numberOfArguments, arguments, 1, Machine_KeyboardKeyEvent_getType());
  Scene_onKeyboardKeyEvent(self, event);
  return RESULT;
}

void main0() {
  Machine_Video_Canvas_maximizeCanvas(Machine_getVideoCanvas());
  loadIcons();
  Machine_JumpTarget jumpTarget1; // To shutdown input.
  Machine_pushJumpTarget(&jumpTarget1);
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

    Machine_JumpTarget jumpTarget2; // To shutdown scene.
    Machine_pushJumpTarget(&jumpTarget2);
    if (!setjmp(jumpTarget2.environment)) {
      Machine_Gc_setRoot(g_scene, true);
      Machine_update();

      Machine_Integer width, height;
      Machine_Video_Canvas_getFrameBuffersSize(Machine_getVideoCanvas(), &width, &height);
      Scene_onCanvasSizeChanged(g_scene, Machine_CanvasSizeChangedEvent_create(
                                             (Machine_Real)width, (Machine_Real)height));

      run(g_scene);
      Machine_popJumpTarget();

      Machine_Gc_setRoot(g_scene, false);
      Scene* s = g_scene;
      g_scene = NULL;
      Scene_onShutdown(s);
    } else {
      Machine_Gc_setRoot(g_scene, false);
      Scene* s = g_scene;
      g_scene = NULL;
      Scene_onShutdown(s);
      Machine_popJumpTarget();
      Machine_jump();
    }
    Machine_popJumpTarget();
  } else {
    Machine_popJumpTarget();
    Machine_jump();
  }
}

int main1() {
  Machine_JumpTarget jumpTarget1;
  bool videoStartedUp = false;
  Machine_pushJumpTarget(&jumpTarget1);
  if (!setjmp(jumpTarget1.environment)) {
    Machine_Video_startup();
    videoStartedUp = true;
    main0();
  }
  Machine_popJumpTarget();
  if (videoStartedUp) {
    Machine_Video_shutdown();
    videoStartedUp = false;
  }
  return Machine_getStatus();
}

int main() {
  if (Machine_startup()) {
    fprintf(stderr, "%s:%d: Machine_startup() failed\n", __FILE__, __LINE__);
    return EXIT_FAILURE;
  }
  int status = main1();
  Machine_shutdown();
  return status == Machine_Status_Success ? EXIT_SUCCESS : EXIT_FAILURE;
}

#if defined(__cplusplus)
}
#endif
