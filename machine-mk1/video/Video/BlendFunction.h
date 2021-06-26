/// @file Video/BlendFunctions.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_BLENDFUNCTION_H_INCLUDED)
#define MACHINE_VIDEO_BLENDFUNCTION_H_INCLUDED



#if !defined(MACHINE_VIDEO_PRIVATE)
#error("Do not include this file directly, include `_Video.h` instead.")
#endif

#include "_Runtime.h"



/// @brief Enumeration of blend functions.
/// @remarks
/// To blend together the incoming color <code>a</code> and the existing color <code>b</code> in a color buffer,
/// the formula <code>f(a) + g(b)</code> is used.
/// - <code>f</code> is the blend function for the incoming color <code>a</code>,
/// - <code>g</code>is the blend function for the existing color <code>b</code>.
/// This enumeration enumerates symbolic constants denoting the possible blend functions
/// for <code>f</code> and <code>g</code>, respectively.
/// @remark
/// - "transparency" disabled: incoming color blend mode is Machine_BlendMode_One and existing color blend mode is Machine_BlendMode_Zero.
/// - "transparency" enabled:  incoming color blend mode is Machine_BlendMode_IncomingAlpha and existing color blend mode is Machine_BlendMode_OneMinusIncomingAlpha
typedef enum Machine_BlendFunction Machine_BlendFunction;

enum Machine_BlendFunction {

  /// @brief The color is multiplied by the incoming alpha.
  Machine_BlendFunction_IncomingAlpha,
  
  /// @brief The color is multipled by one minus the incoming alpha.
  Machine_BlendFunction_OneMinusIncomingAlpha,

  /// @brief The color is multiplied by zero.
  Machine_BlendFunction_Zero,

  /// @brief The color is multiplied by one.
  Machine_BlendFunction_One,

};



#endif // MACHINE_VIDEO_BLENDFUNCTION_H_INCLUDED
