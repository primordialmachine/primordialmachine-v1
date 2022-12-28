// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring3/Math/ColorRgbaU8Extensions.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/ColorRgbaU8Extensions.h"
#undef RING3_MATH_PRIVATE


#include "Ring1/All/_Include.h"


void
Ring3_Math_ColorRgbaU8_packRgb
  (
    Ring3_Math_ColorRgbaU8* self,
    char* target
  )
{
  uint8_t temporary[3] = {
    Ring3_Math_ColorRgbaU8_getRed(self),
    Ring3_Math_ColorRgbaU8_getGreen(self),
    Ring3_Math_ColorRgbaU8_getBlue(self),
  };
  switch (Ring1_getByteOrder()) {
  case Ring1_ByteOrder_BigEndian: {
    // We actually write RGB.
    target[0] = temporary[0];
    target[1] = temporary[1];
    target[2] = temporary[2];
  } break;
  case Ring1_ByteOrder_LittleEndian: {
    // We actually write BGR.
    target[0] = temporary[2];
    target[1] = temporary[1];
    target[2] = temporary[0];
  } break;
  default: {
    Ring1_Status_set(Ring1_Status_UnreachableProgramPointReached);
    Ring2_jump();
  }
  };
}

void
Ring3_Math_ColorRgbaU8_packRgba
  (
    Ring3_Math_ColorRgbaU8* self,
    char* target
  )
{
  uint8_t temporary[4] = {
    Ring3_Math_ColorRgbaU8_getRed(self),
    Ring3_Math_ColorRgbaU8_getGreen(self),
    Ring3_Math_ColorRgbaU8_getBlue(self),
    Ring3_Math_ColorRgbaU8_getAlpha(self)
  };
  switch (Ring1_getByteOrder()) {
  case Ring1_ByteOrder_BigEndian:{
    // We actually write RGBA.
    target[0] = temporary[0];
    target[1] = temporary[1];
    target[2] = temporary[2];
    target[3] = temporary[3];
  } break;
  case Ring1_ByteOrder_LittleEndian: {
    // We actually write ABGR.
    target[0] = temporary[3];
    target[1] = temporary[2];
    target[2] = temporary[1];
    target[3] = temporary[0];
  } break;
  default: {
    Ring1_Status_set(Ring1_Status_UnreachableProgramPointReached);
    Ring2_jump();
  }
  };
}

void
Ring3_Math_ColorRgbaU8_packArgb
  (
    Ring3_Math_ColorRgbaU8* self,
    char* target
  )
{
  uint8_t temporary[4] = {
    Ring3_Math_ColorRgbaU8_getRed(self),
    Ring3_Math_ColorRgbaU8_getGreen(self),
    Ring3_Math_ColorRgbaU8_getBlue(self),
    Ring3_Math_ColorRgbaU8_getAlpha(self),
  };
  switch (Ring1_getByteOrder()) {
  case Ring1_ByteOrder_BigEndian: {
    // We actually write ARGB.
    target[0] = temporary[3];
    target[1] = temporary[0];
    target[2] = temporary[1];
    target[3] = temporary[2];
  } break;
  case Ring1_ByteOrder_LittleEndian: {
    // We actually write BGRA.
    target[0] = temporary[2];
    target[1] = temporary[1];
    target[2] = temporary[0];
    target[3] = temporary[3];
  } break;
  default: {
    Ring1_Status_set(Ring1_Status_UnreachableProgramPointReached);
    Ring2_jump();
  }
  };
}
