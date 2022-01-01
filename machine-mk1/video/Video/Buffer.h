/// @file Video/Buffer.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_BUFFER_H_INCLUDED)
#define MACHINE_VIDEO_BUFFER_H_INCLUDED

#include "Video/_header.i"

MACHINE_DECLARE_CLASSTYPE(Machine_VideoBuffer)

struct Machine_VideoBuffer_Class {
  Machine_Object_Class parent;

  void (*setData)(Machine_VideoBuffer* self, size_t n, const void* p);
  const void* (*getData)(const Machine_VideoBuffer* self);
  size_t (*getSize)(const Machine_VideoBuffer* self);
  const void* (*getId)(const Machine_VideoBuffer* self);
};

struct Machine_VideoBuffer {
  Machine_Object parent;

  size_t n;
  void* p;
};

void Machine_VideoBuffer_construct(Machine_VideoBuffer* self, size_t numberOfArguments,
                                   const Machine_Value* arguments);

/// @brief Set the Bytes of this video buffer.
/// @param self This video buffer.
/// @param n The number of Bytes.
/// @param p A pointer to the Bytes.
void Machine_VideoBuffer_setData(Machine_VideoBuffer* self, size_t n, void const* p);

/// @brief Get the Bytes of this video buffer.
/// @param self This video buffer.
/// @return A pointer to the Bytes.
const void* Machine_VideoBuffer_getData(const Machine_VideoBuffer* self);

/// @brief Get the number of Bytes of this video buffer.
/// @param self This video buffer.
/// @return The number of Bytes.
size_t Machine_VideoBuffer_getSize(const Machine_VideoBuffer* self);

/// @brief Get the backend-specific data of this video buffer.
/// @param self This video buffer.
/// @return A pointer to the backend-specific data of this video buffer.
/// @remark For an OpenGL backend this is a pointer to a GLuint read-only variable.
const void* Machine_VideoBuffer_getId(const Machine_VideoBuffer* self);

#endif // MACHINE_VIDEO_BUFFER_H_INCLUDED
