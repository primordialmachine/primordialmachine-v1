/// @file Ring3/Visuals/Material.protected.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(RING3_VISUALS_MATERIAL_PROTECTED_H_INCLUDED)
#define RING3_VISUALS_MATERIAL_PROTECTED_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/Material.protected.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring3/Visuals/Material.h"

/*PROTECTED*/ void
Ring3_Material_construct
  (
    Ring3_Material* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/*PROTECTED*/ Ring1_CheckReturn() Ring3_Material*
Ring3_Material_create
  (
    Ring3_BlendFunction existingBlendFunction,
    Ring3_DepthTestFunction depthTestFunction,
    Ring2_Boolean depthWriteEnabled,
    Ring3_BlendFunction incomingBlendFunction
  );

/// @brief Set the blend function for the existing color.
/// @param self This material.
/// @param existingBlendFunction The blend function for the existing color.
/*PROTECTED*/ void
Ring3_Material_setExistingBlendFunction
  (
    Ring3_Material* self,
    Ring3_BlendFunction existingBlendFunction
  );

/// @brief Set the blend function for the incoming color.
/// @param self This material.
/// @param incomingBlendFunction The blend function for the incoming color.
/*PROTECTED*/ void
Ring3_Material_setIncomingBlendFunction
  (
    Ring3_Material* self,
    Ring3_BlendFunction incomingBlendFunction
  );

/// @brief Set the depth test function.
/// @param self This material.
/// @param depthTestFunction The depth test function.
/*PROTECTED*/ void
Ring3_Material_setDepthTestFunction
  (
    Ring3_Material* self,
    Ring3_DepthTestFunction depthTestFunction
  );

/// @brief Set if depth write is enabled/disabled.
/// @param self This material.
/// @param depthWriteEnabled @a true enables depth write, @a false disables depth write.
/*PROTECTED*/ void
Ring3_Material_setDepthWriteEnabled
  (
    Ring3_Material* self,
    Ring2_Boolean depthWriteEnabled
  );

#endif // RING3_VISUALS_MATERIAL_PROTECTED_H_INCLUDED
