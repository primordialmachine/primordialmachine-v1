// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring3/Math/ColorRgbaF64Extensions.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/ColorRgbaF64Extensions.h"
#undef RING3_MATH_PRIVATE


#include "Ring1/All/_Include.h"


void
Ring3_Math_ColorRgbaF64_packRgb
  (
    Ring3_Math_ColorRgbaF64* self,
    char* target
  )
{
  double temporary[3] = {
    Ring3_Math_ColorRgbaF64_getRed(self),
    Ring3_Math_ColorRgbaF64_getGreen(self),
    Ring3_Math_ColorRgbaF64_getBlue(self),
  };
  switch (Ring1_getByteOrder()) {
  case Ring1_ByteOrder_BigEndian:
  {
    // We actually write RGB.
    target[0] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[0], 0., 255.);
    target[1] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[1], 0., 255.);
    target[2] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[2], 0., 255.);
  } break;
  case Ring1_ByteOrder_LittleEndian:
  {
    // We actually write BGR.
    target[0] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[2], 0., 255.);
    target[1] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[1], 0., 255.);
    target[2] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[0], 0., 255.);
  } break;
  default: {
    Ring1_Status_set(Ring1_Status_UnreachableProgramPointReached);
    Ring2_jump();
  }
  };
}

void
Ring3_Math_ColorRgbaF64_packRgba
  (
    Ring3_Math_ColorRgbaF64* self,
    char* target
  )
{
  double temporary[4] = {
    Ring3_Math_ColorRgbaF64_getRed(self),
    Ring3_Math_ColorRgbaF64_getGreen(self),
    Ring3_Math_ColorRgbaF64_getBlue(self),
    Ring3_Math_ColorRgbaF64_getAlpha(self),
  };
  switch (Ring1_getByteOrder()) {
  case Ring1_ByteOrder_BigEndian: {
    // We actually write RGBA.
    target[0] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[0], 0., 255.);
    target[1] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[1], 0., 255.);
    target[2] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[2], 0., 255.);
    target[3] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[3], 0., 255.);
  } break;
  case Ring1_ByteOrder_LittleEndian: {
    // We actually write ABGR.
    target[0] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[3], 0., 255.);
    target[1] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[2], 0., 255.);
    target[2] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[1], 0., 255.);
    target[3] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[0], 0., 255.);
  } break;
  default: {
    Ring1_Status_set(Ring1_Status_UnreachableProgramPointReached);
    Ring2_jump();
  }
  };
}

void
Ring3_Math_ColorRgbaF64_packArgb
  (
    Ring3_Math_ColorRgbaF64* self,
    char* target
  )
{
  double temporary[4] = {
    Ring3_Math_ColorRgbaF64_getRed(self),
    Ring3_Math_ColorRgbaF64_getGreen(self),
    Ring3_Math_ColorRgbaF64_getBlue(self),
    Ring3_Math_ColorRgbaF64_getAlpha(self),
  };
  switch (Ring1_getByteOrder()) {
  case Ring1_ByteOrder_BigEndian: {
    // We actually write ARGB.
    target[0] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[3], 0., 255.);
    target[1] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[0], 0., 255.);
    target[2] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[1], 0., 255.);
    target[3] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[2], 0., 255.);
  } break;
  case Ring1_ByteOrder_LittleEndian: {
    // We actually write BGRA.
    target[0] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[2], 0., 255.);
    target[1] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[1], 0., 255.);
    target[2] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[0], 0., 255.);
    target[3] = (uint8_t)Mkx_Intrinsic_lerp_f64(temporary[3], 0., 255.);
  } break;
  default: {
    Ring1_Status_set(Ring1_Status_UnreachableProgramPointReached);
    Ring2_jump();
  }
  };
}
