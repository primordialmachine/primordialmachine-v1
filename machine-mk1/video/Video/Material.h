/// @file Video/Material.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_MATERIAL_H_INCLUDED)
#define MACHINE_VIDEO_MATERIAL_H_INCLUDED



#if !defined(MACHINE_VIDEO_PRIVATE)
#error("Do not include this file directly, include `_Video.h` instead.")
#endif

#include "./../Video/BlendFunction.h"
#include "./../Video/DepthTestFunction.h"
#include "_Math.h"



MACHINE_DECLARE_CLASSTYPE(Machine_Material)


struct Machine_Material {
  Machine_Object parent;

  Machine_BlendFunction existingBlendFunction;
  Machine_BlendFunction incomingBlendFunction;

  Machine_Boolean depthWriteEnabled;
  Machine_DepthTestFunction depthTestFunction;
};


void Machine_Material_construct(Machine_Material* self, size_t numberOfArguments, const Machine_Value* arguments);

Machine_Material* Machine_Material_create();

void Machine_Material_assign(Machine_Material* self, Machine_Material const* other);

/// @brief Set the blend function for the existing color.
/// @param self This material.
/// @param existingBlendFunction The blend function for the existing color.
void Machine_Material_setExistingBlendFunction(Machine_Material* self, Machine_BlendFunction existingBlendFunction);

/// @brief Get the blend function for the existing color.
/// @param self This material.
/// @return The blend function for the existing color.
Machine_BlendFunction Machine_Material_getExistingBlendFunction(Machine_Material const* self);


/// @brief Set the blend function for the incoming color.
/// @param self This material.
/// @param incomingBlendFunction The blend function for the incoming color.
void Machine_Material_setIncomingBlendFunction(Machine_Material* self, Machine_BlendFunction incomingBlendFunction);

/// @brief Get the blend function for the incoming color.
/// @param self This material.
/// @return The blend function for the incoming color.
Machine_BlendFunction Machine_Material_getIncomingBlendFunction(Machine_Material const* self);


/// @brief Set the depth test function.
/// @param self This material.
/// @param depthTestFunction The depth test function.
void Machine_Material_setDepthTestFunction(Machine_Material* self, Machine_DepthTestFunction depthTestFunction);

/// @brief Get the depth test function.
/// @param self This material.
/// @return The depth test function.
Machine_DepthTestFunction Machine_Material_getDepthTestFunction(Machine_Material const* self);


/// @brief Set if depth write is enabled/disabled.
/// @param self This material.
/// @param depthWriteEnabled @a true enables depth write, @a false disables depth write.
void Machine_Material_setDepthWriteEnabled(Machine_Material* self, Machine_Boolean depthWriteEnabled);

/// @brief Get if depth write is enabled/disabled.
/// @param self This material.
/// @return @a true if depth write is enabled, @a false if depth write is disabled.
Machine_Boolean Machine_Material_getDepthWriteEnabled(Machine_Material const* self);


#endif // MACHINE_VIDEO_MATERIAL_H_INCLUDED
