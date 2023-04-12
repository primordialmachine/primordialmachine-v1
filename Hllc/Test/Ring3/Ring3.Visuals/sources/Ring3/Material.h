/// @file Ring3/Material.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(RING3_MATERIAL_H_INCLUDED)
#define RING3_MATERIAL_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "Ring2/_Include.h"
#include "Ring2/Library/_Include.h"
#include "Ring3/DepthTestFunction.h"
#include "Ring3/BlendFunction.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Material)

struct Ring3_Material
{
  Machine_Object parent;
};

struct Ring3_Material_class
{
  Machine_Object_class parent;
  Ring3_DepthTestFunction (*getDepthTestFunction)
    (
      Ring3_Material* self
    );
  Ring3_BlendFunction (*getExistingBlendFunction)
    (
      Ring3_Material* self
    );
  Ring3_BlendFunction (*getIncomingBlendFunction)
    (
      Ring3_Material* self
    );
  Ring2_Boolean (*getDepthTestEnabled)
    (
      Ring3_Material* self
    );
};

Ring3_DepthTestFunction
Ring3_Material_getDepthTestFunction
  (
    Ring3_Material* self
  );

Ring3_BlendFunction
Ring3_Material_getExistingBlendFunction
  (
    Ring3_Material* self
  );

Ring3_BlendFunction
Ring3_Material_getIncomingBlendFunction
  (
    Ring3_Material* self
  );

Ring2_Boolean
Ring3_Material_getDepthTestEnabled
  (
    Ring3_Material* self
  );

#ifdef __cplusplus
}
#endif

#endif // RING3_MATERIAL_H_INCLUDED
