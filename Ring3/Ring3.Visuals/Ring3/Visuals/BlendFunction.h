/// @file Ring3/Visuals/BlendFunctions.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_BLENDFUNCTION_H_INCLUDED)
#define RING3_VISUALS_BLENDFUNCTION_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/BlendFunction.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// @brief
/// Enumeration of blend functions.
/// @remarks
/// To blend together the incoming color <code>a</code> and the existing color <code>b</code> in a
/// color buffer, the formula <code>f(a) + g(b)</code> is used.
/// - <code>f</code> is the blend function for the incoming color <code>a</code>,
/// - <code>g</code>is the blend function for the existing color <code>b</code>.
/// This enumeration enumerates symbolic constants denoting the possible blend functions
/// for <code>f</code> and <code>g</code>, respectively.
/// @remark
/// - "transparency" disabled: incoming color blend mode is Machine_BlendMode_One and existing color
/// blend mode is Machine_BlendMode_Zero.
/// - "transparency" enabled:  incoming color blend mode is Machine_BlendMode_IncomingAlpha and
/// existing color blend mode is Machine_BlendMode_OneMinusIncomingAlpha
MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_BlendFunction)

enum Ring3_BlendFunction {

  /// @brief The color is multiplied by the incoming alpha.
  Ring3_BlendFunction_IncomingAlpha,

  /// @brief The color is multipled by one minus the incoming alpha.
  Ring3_BlendFunction_OneMinusIncomingAlpha,

  /// @brief The color is multiplied by zero.
  Ring3_BlendFunction_Zero,

  /// @brief The color is multiplied by one.
  Ring3_BlendFunction_One,

};

#endif // RING3_VISUALS_BLENDFUNCTION_H_INCLUDED
