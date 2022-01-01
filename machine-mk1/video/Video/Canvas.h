#if !defined(MACHINE_VIDEO_CANVAS_H_INCLUDED)
#define MACHINE_VIDEO_CANVAS_H_INCLUDED

#include "Video/_header.i"

/// @brief Abstract base of all canvas.
/// This engine only supports one main canvas.
/// The main canvas can be acquired using Machine_getCanvas().
MACHINE_DECLARE_CLASSTYPE(Machine_Video_Canvas);

struct Machine_Video_Canvas_Class {
  Machine_Object_Class parent__;
  void (*getFrameBuffersSize)(Machine_Video_Canvas* self, Machine_Integer* width,
                              Machine_Integer* height);
  void (*maximizeCanvas)(Machine_Video_Canvas* self);
  void (*swapFrameBuffers)(Machine_Video_Canvas* self);
  void (*setCanvasIcons)(Machine_Video_Canvas* self, Machine_List* images);
  void (*pollEvents)(Machine_Video_Canvas* self);
  Machine_Boolean (*getQuitRequested)(Machine_Video_Canvas* self);
};

struct Machine_Video_Canvas {
  Machine_Object parent__;
  Machine_Signals_Signal* signal;
};

void Machine_Video_Canvas_construct(Machine_Video_Canvas* self, size_t numberOfArguments,
                                    Machine_Value const* arguments);

/// @brief Get the size, in pixels, of the frame buffers.
/// @param self This canvas.
/// @param width A pointer to a Machine_Integer variable.
/// @param height A pointer to a Machine_Integer variable.
/// @success
/// - The width was assigned to *width.
/// - The height was assigned to *height.
void Machine_Video_Canvas_getFrameBuffersSize(Machine_Video_Canvas* self, Machine_Integer* width,
                                              Machine_Integer* height);

/// @brief Maximize this canvas.
/// @param self This canvas.
void Machine_Video_Canvas_maximizeCanvas(Machine_Video_Canvas* self);

/// @brief Swap the frame buffers of this canvas..
/// @param self This canvas.
void Machine_Video_Canvas_swapFrameBuffers(Machine_Video_Canvas* self);

/// @brief Set the icons of this canvas.
/// @param self This canvas.
/// @param images The icons.
void Machine_Video_Canvas_setCanvasIcons(Machine_Video_Canvas* self, Machine_List* images);

/// @brief Poll the events of this canvas.
/// @param self This canvas.
void Machine_Video_Canvas_pollEvents(Machine_Video_Canvas* self);

/// @brief Get if the application was requested to quit.
/// @param self This canvas.
/// @return @a true if quit was requested, @a false otherwise.
Machine_Boolean Machine_Video_Canvas_getQuitRequested(Machine_Video_Canvas* self);

/// @brief Subscribe to keyboard key pressed events.
/// @param self This canvas.
void Machine_Video_Canvas_subscribeKeyboardKeyPressedEvent(Machine_Video_Canvas* self,
                                                           Machine_Object* context,
                                                           Machine_ForeignProcedure* callback);

/// @brief Subscribe to keyboard key released events.
/// @param self This canvas.
void Machine_Video_Canvas_subscribeKeyboardKeyReleasedEvent(Machine_Video_Canvas* self,
                                                            Machine_Object* context,
                                                            Machine_ForeignProcedure* callback);

/// @brief Subscribe to the mouse button pressed events.
/// @param self This canvas.
void Machine_Video_Canvas_subscribeMouseButtonPressedEvent(Machine_Video_Canvas* self,
                                                           Machine_Object* context,
                                                           Machine_ForeignProcedure* callback);

/// @brief Subscribe to the mouse button released events.
/// @param self This canvas.
void Machine_Video_Canvas_subscribeMouseButtonReleasedEvent(Machine_Video_Canvas* self,
                                                            Machine_Object* context,
                                                            Machine_ForeignProcedure* callback);

/// @brief Subscribe to the mouse pointer moved event signals.
/// @param self This canvas.
void Machine_Video_Canvas_subscribeMousePointerMovedEvent(Machine_Video_Canvas* self,
                                                          Machine_Object* context,
                                                          Machine_ForeignProcedure* callback);

#endif // MACHINE_VIDEO_CANVAS_H_INCLUDED
