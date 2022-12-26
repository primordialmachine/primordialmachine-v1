/// @file Ring3/Visuals/Material.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_MATERIAL_H_INCLUDED)
#define RING3_VISUALS_MATERIAL_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/Material.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"
#include "Ring3/Visuals/BlendFunction.h"
#include "Ring3/Visuals/DepthTestFunction.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Material)

struct Ring3_Material_Class {
  Machine_Object_Class parent;
};

struct Ring3_Material {
  Machine_Object parent;
  Ring3_BlendFunction existingBlendFunction;
  Ring3_BlendFunction incomingBlendFunction;
  Ring2_Boolean depthWriteEnabled;
  Ring3_DepthTestFunction depthTestFunction;
  Ring2_Integer hashValue;
};

/// @brief Get the blend function for the existing color.
/// @param self This material.
/// @return The blend function for the existing color.
Ring1_CheckReturn() Ring3_BlendFunction
Ring3_Material_getExistingBlendFunction
  (
    Ring3_Material const* self
  );

/// @brief Get the blend function for the incoming color.
/// @param self This material.
/// @return The blend function for the incoming color.
Ring1_CheckReturn() Ring3_BlendFunction
Ring3_Material_getIncomingBlendFunction
  (
    Ring3_Material const* self
  );

/// @brief Get the depth test function.
/// @param self This material.
/// @return The depth test function.
Ring1_CheckReturn() Ring3_DepthTestFunction
Ring3_Material_getDepthTestFunction
  (
    Ring3_Material const* self
  );

/// @brief Get if depth write is enabled/disabled.
/// @param self This material.
/// @return @a true if depth write is enabled, @a false if depth write is disabled.
Ring1_CheckReturn() Ring2_Boolean
Ring3_Material_getDepthWriteEnabled
  (
    Ring3_Material const* self
  );

#endif // RING3_VISUALS_MATERIAL_H_INCLUDED
