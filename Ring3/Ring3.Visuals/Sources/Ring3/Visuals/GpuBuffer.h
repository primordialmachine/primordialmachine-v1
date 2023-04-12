/// @file Video/GpuVideoBuffer.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(RING3_VISUALS_GPUBUFFER_H_INCLUDED)
#define RING3_VISUALS_GPUBUFFER_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/GpuBuffer.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_GpuBuffer)

struct Ring3_GpuBuffer_Class {
  Machine_Object_Class parent;

  void (*setData)(Ring3_GpuBuffer* self, size_t n, void const* p);
  void const* (*getData)(Ring3_GpuBuffer const* self);
  size_t (*getSize)(Ring3_GpuBuffer const* self);
  void const* (*getId)(Ring3_GpuBuffer const* self);
};

struct Ring3_GpuBuffer {
  Machine_Object parent;
};

/// @brief Construct this video buffer.
/// @params self, numberOfArguments, arguments The constructor parameters.
/// @remark
/// The HLL signature of this constructor is
/// @code
/// Ring3.Visuals.GpuBuffer()
/// @endcode
void
Ring3_GpuBuffer_construct
  (
    Ring3_GpuBuffer* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Set the Bytes of this video buffer.
/// @param self This video buffer.
/// @param n The number of Bytes.
/// @param p A pointer to the Bytes.
void
Ring3_GpuBuffer_setData
  (
    Ring3_GpuBuffer* self,
    size_t n,
    void const* p
  );

/// @brief Get the Bytes of this video buffer.
/// @param self This video buffer.
/// @return A pointer to the Bytes.
void const*
Ring3_GpuBuffer_getData
  (
    Ring3_GpuBuffer const* self
  );

/// @brief Get the number of Bytes of this video buffer.
/// @param self This video buffer.
/// @return The number of Bytes.
size_t
Ring3_GpuBuffer_getSize
  (
    Ring3_GpuBuffer const* self
  );

/// @brief Get the backend-specific data of this video buffer.
/// @param self This video buffer.
/// @return A pointer to the backend-specific data of this video buffer.
/// @remark For an OpenGL backend this is a pointer to a GLuint read-only variable.
void const*
Ring3_GpuBuffer_getId
  (
    Ring3_GpuBuffer const* self
  );

#endif // RING3_VISUALS_GPUBUFFER_H_INCLUDED
