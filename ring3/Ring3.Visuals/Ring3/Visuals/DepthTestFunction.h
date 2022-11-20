/// @file Ring3/Visuals/BlendFunctions.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_DEPTHTESTFUNCTION_H_INCLUDED)
#define RING3_VISUALS_DEPTHTESTFUNCTION_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/DepthTestFunctions.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// @brief
/// Enumeration of depth test functions.
/// @remark
/// A fragment is passed on in the pipeline if its depth test succeeds, otherwise it is discarded.
/// A fragment is passed /is discarded depends on three factors:
/// - the depth value of the fragment
/// - the depth value in the depth buffer
/// - the depth test function used to compare the depth values.
/// This enumeration enumerates symbolic constants denoting the possible depth test functions.
MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_DepthTestFunction)

enum Ring3_DepthTestFunction {

  /// @brief Pass if incoming is less than or equal to existing.
  Ring3_DepthTestFunction_LessThan,

  /// @brief Pass if incoming is less than or equal to existing.
  Ring3_DepthTestFunction_LessThanOrEqualTo,

  /// @brief Pass if incoming is equal to existing.
  Ring3_DepthTestFunction_EqualTo,

  /// @brief Pass if incoming is greater than existing.
  Ring3_DepthTestFunction_GreaterThan,

  /// @brief Pass if incoming is greater than or equal to existing.
  Ring3_DepthTestFunction_GreaterThanOrEqualTo,

  /// @brief Always pass.
  Ring3_DepthTestFunction_Always,

  /// @brief Never pass.
  Ring3_DepthTestFunction_Never,

};

#endif // RING3_VISUALS_DEPTHTESTFUNCTION_H_INCLUDED
