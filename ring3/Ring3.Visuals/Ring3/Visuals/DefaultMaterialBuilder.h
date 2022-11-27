/// @file Ring3/Visuals/DefaultMaterialBuilder.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_DEFAULTMATERIALBUILDER_H_INCLUDED)
#define RING3_VISUALS_DEFAULTMATERIALBUILDER_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/DefaultMaterialBuilder.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"
#include "Ring3/Visuals/BlendFunction.h"
#include "Ring3/Visuals/DepthTestFunction.h"
typedef struct Ring3_Material Ring3_Material;

/// @brief
/// The default material builder.
/// @extends Machine.Object
/// @implements Ring3.MaterialBuilder
MACHINE_DECLARE_CLASSTYPE(Ring3_DefaultMaterialBuilder)

struct Ring3_DefaultMaterialBuilder_Class {
  Machine_Object_Class parent;
};

struct Ring3_DefaultMaterialBuilder {
  Machine_Object parent;

  Ring3_BlendFunction existingBlendFunction;
  Ring3_BlendFunction incomingBlendFunction;

  Ring2_Boolean depthWriteEnabled;
  Ring3_DepthTestFunction depthTestFunction;
};

void
Ring3_DefaultMaterialBuilder_construct
  (
    Ring3_DefaultMaterialBuilder* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  );

Ring1_CheckReturn() Ring3_DefaultMaterialBuilder*
Ring3_DefaultMaterialBuilder_create
  (
  );

#endif // RING3_VISUALS_DEFAULTMATERIALBUILDER_H_INCLUDED
