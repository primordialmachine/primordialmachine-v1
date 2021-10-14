#if !defined(MACHINE_GL_VIDEOCONTEXT_H_INCLUDED)
#define MACHINE_GL_VIDEOCONTEXT_H_INCLUDED



#include "_Video.h"

typedef struct Machine_GL_VideoContext_ClipDistance {
  Machine_Boolean enabled;
} Machine_GL_VideoContext_ClipDistance;

typedef struct Machine_GL_VideoContext_ClipDistances {
  size_t n;
  Machine_GL_VideoContext_ClipDistance* a;
} Machine_GL_VideoContext_ClipDistances;

/// @brief Video context implementation for GLFW/GL.
/// @extends Machine.VideoContext
MACHINE_DECLARE_CLASSTYPE(Machine_GL_VideoContext)

struct Machine_GL_VideoContext_Class {
  Machine_VideoContext_Class __parent;

  void (*write)(Machine_GL_VideoContext const* self);
};

struct Machine_GL_VideoContext {
  Machine_VideoContext __parent;

  Machine_Real clearDepth; // Default is <code>1</code>.
  Machine_Real clearColor[4]; // Default is <code>(0,0,0,1)</code>.
  Machine_DepthTestFunction depthTestFunction; // Default is <code>always</code>.
  Machine_Boolean depthWriteEnabled; // Default is <code>false</code>.
  Machine_BlendFunction existingBlendFunction; // Default is <code>one minus incoming alpha</code>.
  Machine_BlendFunction incomingBlendFunction; // Default is <code>incoming alpha</code>.
  Machine_GL_VideoContext_ClipDistances* clipDistances; // Default is all clip distances disabled.
  // The viewport rectangle.
  // Initially (0,0,w,h) where w and h are the frame buffer width and height.
  // Specified in frame buffer coordinates where positive x-axis (positive y-axis) is pointing right (up) and the bottom left corner is at (0,0).
  Machine_Math_Rectangle2* viewportRectangle;
};

void Machine_GL_VideoContext_construct(Machine_GL_VideoContext* self, size_t numberOfArguments, Machine_Value const* arguments);

Machine_GL_VideoContext* Machine_GL_VideoContext_create();

void Machine_GL_VideoContext_write(Machine_GL_VideoContext const* self);

#endif // MACHINE_GL_VIDEOCONTEXT_H_INCLUDED
