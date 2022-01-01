/// @file Video/BlendFunctions.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_DEPTHTESTFUNCTION_H_INCLUDED)
#define MACHINE_VIDEO_DEPTHTESTFUNCTION_H_INCLUDED

#if !defined(MACHINE_VIDEO_PRIVATE)
#error("Do not include this file directly, include `_Video.h` instead.")
#endif
#include "_Runtime.h"

/// @brief Enumeration of depth test functions.
/// @remark
/// A fragment is passed on in the pipeline if its depth test succeeds, otherwise it is discarded.
/// A fragment is passed /is discarded depends on three factors:
/// - the depth value of the fragment
/// - the depth value in the depth buffer
/// - the depth test function used to compare the depth values.
/// This enumeration enumerates symbolic constants denoting the possible depth test functions.
typedef enum Machine_DepthTestFunction Machine_DepthTestFunction;

enum Machine_DepthTestFunction {

  /// @brief Pass if incoming is less than or equal to existing.
  Machine_DepthTestFunction_LessThan,

  /// @brief Pass if incoming is less than or equal to existing.
  Machine_DepthTestFunction_LessThanOrEqualTo,

  /// @brief Pass if incoming is equal to existing.
  Machine_DepthTestFunction_EqualTo,

  /// @brief Pass if incoming is greater than existing.
  Machine_DepthTestFunction_GreaterThan,

  /// @brief Pass if incoming is greater than or equal to existing.
  Machine_DepthTestFunction_GreaterThanOrEqualTo,

  /// @brief Always pass.
  Machine_DepthTestFunction_Always,

  /// @brief Never pass.
  Machine_DepthTestFunction_Never,

};

#endif // MACHINE_VIDEO_DEPTHTESTFUNCTION_H_INCLUDED
