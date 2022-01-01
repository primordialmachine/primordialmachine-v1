#if !defined(MACHINE_VIDEO_H_INCLUDED)
#define MACHINE_VIDEO_H_INCLUDED

#include "_Math.h"
#include "_Video.h"

/// @brief Increment the video module by @a 1.
/// FAILS if the reference count is INT_MAX.
/// @return @a 0 on success, a non-zero value on failure.
void Machine_Video_startup();

/// @brief Decrement the video module by @a 1.
/// UNDEFINED if the reference count is @a 0.
void Machine_Video_shutdown();

/// @brief Get the canvas.
/// @return The canvas.
Machine_Video_Canvas* Machine_getVideoCanvas();

/// @brief Get the video context of the video module.
/// @return The video context.
Machine_VideoContext* Machine_getVideoContext();

#endif // MACHINE_VIDEO_H_INCLUDED
