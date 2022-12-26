/// @file Video/Buffer.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_BUFFER_H_INCLUDED)
#define MACHINE_VIDEO_BUFFER_H_INCLUDED

#include "Video/_header.i"

MACHINE_DECLARE_CLASSTYPE(Machine_VideoBuffer)

struct Machine_VideoBuffer_Class {
  Machine_Object_Class parent;

  void (*setData)(Machine_VideoBuffer* self, size_t n, void const* p);
  void const* (*getData)(Machine_VideoBuffer const* self);
  size_t (*getSize)(Machine_VideoBuffer const* self);
  void const* (*getId)(Machine_VideoBuffer const* self);
};

struct Machine_VideoBuffer {
  Machine_Object parent;

  size_t n;
  void* p;
};

void Machine_VideoBuffer_construct(Machine_VideoBuffer* self, size_t numberOfArguments,
                                   Ring2_Value const* arguments);

/// @brief Set the Bytes of this video buffer.
/// @param self This video buffer.
/// @param n The number of Bytes.
/// @param p A pointer to the Bytes.
void Machine_VideoBuffer_setData(Machine_VideoBuffer* self, size_t n, void const* p);

/// @brief Get the Bytes of this video buffer.
/// @param self This video buffer.
/// @return A pointer to the Bytes.
void const* Machine_VideoBuffer_getData(Machine_VideoBuffer const* self);

/// @brief Get the number of Bytes of this video buffer.
/// @param self This video buffer.
/// @return The number of Bytes.
size_t Machine_VideoBuffer_getSize(Machine_VideoBuffer const* self);

/// @brief Get the backend-specific data of this video buffer.
/// @param self This video buffer.
/// @return A pointer to the backend-specific data of this video buffer.
/// @remark For an OpenGL backend this is a pointer to a GLuint read-only variable.
void const* Machine_VideoBuffer_getId(Machine_VideoBuffer const* self);

#endif // MACHINE_VIDEO_BUFFER_H_INCLUDED
