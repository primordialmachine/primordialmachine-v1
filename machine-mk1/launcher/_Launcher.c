#include "_Launcher.h"

#include "Ring3/Fonts/FreeType2/_Include.h"
#include "Ring3/ImagesTranscoders/LibPng/_Include.h"
#include "Ring3/Visuals/Gl/_Include.h"

static Ring3_VisualsContext* g_visualsContext = NULL;
static Ring3_Canvas* g_videoCanvas = NULL;

static Ring3_ImagesContext* g_imagesContext = NULL;

static Ring3_FontsContext* g_fontsContext = NULL;

static void shutdownImages() {
  if (g_imagesContext) {
    Ring2_Gc_unlock(g_imagesContext);
    g_imagesContext = NULL;
  }
}

#include "Ring3/Visuals/_Include.h"

static void startupImages() {
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    g_imagesContext = Ring3_ImagesContext_create();
    {
      Ring3_ImagesDecoder* decoder = Ring1_cast(Ring3_ImagesDecoder*, Ring3_ImagesTranscoders_LibPng_ImagesDecoder_create());
      Ring3_ImagesContext_addDecoder(g_imagesContext, decoder);
    }
    Ring2_Gc_lock(g_imagesContext);
    Ring2_popJumpTarget();
  } else {
    Ring2_popJumpTarget();
    if (g_imagesContext) {
      Ring2_Gc_unlock(g_imagesContext);
      g_imagesContext = NULL;
    }
    Ring2_jump();
  }
}

static void startupCanvas() {
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    g_videoCanvas = (Ring3_Canvas*)Machine_Video_Gl_Canvas_create();
    Ring2_Gc_lock(g_videoCanvas);
    g_visualsContext = (Ring3_VisualsContext*)Machine_Gl_VideoContext_create();
    Ring2_Gc_lock(g_visualsContext);
    Ring2_popJumpTarget();
  } else {
    Ring2_popJumpTarget();
    if (g_visualsContext) {
      Ring2_Gc_unlock(g_visualsContext);
      g_visualsContext = NULL;
    }
    if (g_videoCanvas) {
      Ring2_Gc_unlock(g_videoCanvas);
      g_videoCanvas = NULL;
    }
    Ring2_jump();
  }
}

static void shutdownCanvas() {
  if (g_visualsContext) {
    Ring2_Gc_unlock(g_visualsContext);
    g_visualsContext = NULL;
  }
  if (g_videoCanvas) {
    Ring2_Gc_unlock(g_videoCanvas);
    g_videoCanvas = NULL;
  }
}

static void shutdownFonts() {
  if (g_fontsContext) {
    Ring2_Gc_unlock(g_fontsContext);
    g_fontsContext = NULL;
  }
}

static void startupFonts() {
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    g_fontsContext = (Ring3_FontsContext*)Machine_DefaultFonts_createContext(g_visualsContext, g_imagesContext);
    Ring2_Gc_lock(g_fontsContext);
    Ring2_popJumpTarget();
  } else {
    Ring2_popJumpTarget();
    if (g_fontsContext) {
      Ring2_Gc_unlock(g_fontsContext);
      g_fontsContext = NULL;
    }
    Ring2_jump();
  }
}

typedef struct ModuleInfo {
  void (*startup)();
  void (*shutdown)();
} ModuleInfo;

static ModuleInfo g_moduleInfos[] = {
  { .startup = &startupCanvas, .shutdown = &shutdownCanvas },
  { .startup = &startupImages, .shutdown = &shutdownImages },
  { .startup = &startupFonts,  .shutdown = &shutdownFonts },
};

void Machine_Launcher_startup() {
  size_t i = 0, n = 3;
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    for (; i < n; ++i) {
      g_moduleInfos[i].startup();
    }
    Ring2_popJumpTarget();
  } else {
    Ring2_popJumpTarget();
    while (i > 0) {
      g_moduleInfos[--i].shutdown();
    }
    Ring2_jump();
  }
}

void Machine_Launcher_shutdown() {
  size_t i = 3;
  while (i > 0) {
    g_moduleInfos[--i].shutdown();
  }
}

Ring1_NoDiscardReturn() Ring3_Canvas*
Machine_Launcher_getVideoCanvas
  (
  )
{ return g_videoCanvas; }

Ring1_NoDiscardReturn() Ring3_VisualsContext*
Machine_Launcher_getVisualsContext
  (
  )
{ return g_visualsContext; }

Ring1_NoDiscardReturn() Ring3_ImagesContext*
Machine_Launcher_getImagesContext
  (
  )
{ return g_imagesContext; }

Ring1_NoDiscardReturn() Ring3_FontsContext*
Machine_Launcher_getFontsContext
  (
  )
{ return g_fontsContext; }
