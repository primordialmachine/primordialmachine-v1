/// @file Ring3/Visuals/MaterialBuilder.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_MATERIALBUILDER_H_INCLUDED)
#define RING3_VISUALS_MATERIALBUILDER_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/MaterialBuilder.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"
#include "Ring3/Visuals/BlendFunction.h"
#include "Ring3/Visuals/DepthTestFunction.h"
typedef struct Ring3_Material Ring3_Material;

/// @brief
/// The interface of a Ring3.MaterialBuilder.
MACHINE_DECLARE_INTERFACETYPE(Ring3_MaterialBuilder)

struct Ring3_MaterialBuilder_Dispatch {
  Machine_InterfaceDispatch parent;

  void
  (*setExistingBlendFunction)
    (
      Ring3_MaterialBuilder* self,
      Ring3_BlendFunction existingBlendFunction
    );
  
  Ring1_CheckReturn() Ring3_BlendFunction
  (*getExistingBlendFunction)
    (
      Ring3_MaterialBuilder const* self
    );

  void
  (*setIncomingBlendFunction)
    (
      Ring3_MaterialBuilder* self,
      Ring3_BlendFunction incomingBlendFunction
    );

  Ring1_CheckReturn() Ring3_BlendFunction
  (*getIncomingBlendFunction)
    (
      Ring3_MaterialBuilder const* self
    );

  void
  (*setDepthTestFunction)
    (
      Ring3_MaterialBuilder* self,
      Ring3_DepthTestFunction depthTestFunction
    );

  Ring1_CheckReturn() Ring3_DepthTestFunction
  (*getDepthTestFunction)
    (
      Ring3_MaterialBuilder const* self
    );

  void
  (*setDepthWriteEnabled)
    (
      Ring3_MaterialBuilder* self,
      Ring2_Boolean depthWriteEnabled
    );

  Ring1_CheckReturn() Ring2_Boolean
  (*getDepthWriteEnabled)
    (
      Ring3_MaterialBuilder const* self
    );

  Ring1_CheckReturn() Ring3_Material*
  (*build)
    (
      Ring3_MaterialBuilder const* self
    );

};

/// @brief Set the blend function for the existing color.
/// @param self This material.
/// @param existingBlendFunction The blend function for the existing color.
void Ring3_MaterialBuilder_setExistingBlendFunction
  (
    Ring3_MaterialBuilder* self,
    Ring3_BlendFunction existingBlendFunction
  );

/// @brief Get the blend function for the existing color.
/// @param self This material.
/// @return The blend function for the existing color.
Ring1_CheckReturn() Ring3_BlendFunction
Ring3_MaterialBuilder_getExistingBlendFunction
  (
    Ring3_MaterialBuilder const* self
  );

/// @brief Set the blend function for the incoming color.
/// @param self This material.
/// @param incomingBlendFunction The blend function for the incoming color.
void
Ring3_MaterialBuilder_setIncomingBlendFunction
  (
    Ring3_MaterialBuilder* self,
    Ring3_BlendFunction incomingBlendFunction
  );

/// @brief Get the blend function for the incoming color.
/// @param self This material builder.
/// @return The blend function for the incoming color.
Ring1_CheckReturn() Ring3_BlendFunction
Ring3_MaterialBuilder_getIncomingBlendFunction
  (
    Ring3_MaterialBuilder const* self
  );

/// @brief Set the depth test function.
/// @param self This material builder.
/// @param depthTestFunction The depth test function.
void
Ring3_MaterialBuilder_setDepthTestFunction
  (
    Ring3_MaterialBuilder* self,
    Ring3_DepthTestFunction depthTestFunction
  );

/// @brief Get the depth test function.
/// @param self This material builder.
/// @return The depth test function.
Ring1_CheckReturn() Ring3_DepthTestFunction
Ring3_MaterialBuilder_getDepthTestFunction
  (
    Ring3_MaterialBuilder const* self
  );

/// @brief Set if depth write is enabled/disabled.
/// @param self This material builder.
/// @param depthWriteEnabled @a true enables depth write, @a false disables depth write.
void
Ring3_MaterialBuilder_setDepthWriteEnabled
  (
    Ring3_MaterialBuilder* self,
    Ring2_Boolean depthWriteEnabled
  );

/// @brief Get if depth write is enabled/disabled.
/// @param self This material builder.
/// @return @a true if depth write is enabled, @a false if depth write is disabled.
Ring1_CheckReturn() Ring2_Boolean
Ring3_MaterialBuilder_getDepthWriteEnabled
  (
    Ring3_MaterialBuilder const* self
  );

/// @brief Build the material.
/// @param self This material builder.
/// @return The material.
Ring1_CheckReturn() Ring3_Material*
Ring3_MaterialBuilder_build
  (
    Ring3_MaterialBuilder const* self
  );

#endif // RING3_VISUALS_MATERIALBUILDER_H_INCLUDED
