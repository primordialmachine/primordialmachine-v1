// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring3/Math/ColorRgbU8Extensions.c
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring3/Math/ColorRgbU8Extensions.h"

#include "Ring1/All/_Include.h"

void
Ring3_Math_ColorRgbU8_packRgb
  (
    Ring3_Math_ColorRgbU8* self,
    char* target
  )
{
  uint8_t temporary[3] = {
    Ring3_Math_ColorRgbU8_getRed(self),
    Ring3_Math_ColorRgbU8_getGreen(self),
    Ring3_Math_ColorRgbU8_getBlue(self),
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
Ring3_Math_ColorRgbU8_packBgr
  (
    Ring3_Math_ColorRgbU8* self,
    char* target
  )
{
  uint8_t temporary[3] = {
    Ring3_Math_ColorRgbU8_getRed(self),
    Ring3_Math_ColorRgbU8_getGreen(self),
    Ring3_Math_ColorRgbU8_getBlue(self),
  };
  switch (Ring1_getByteOrder()) {
  case Ring1_ByteOrder_BigEndian: {
    // We actually write BGR.
    target[0] = temporary[2];
    target[1] = temporary[1];
    target[2] = temporary[0];
  } break;
  case Ring1_ByteOrder_LittleEndian: {
    // We actually write RGB.
    target[0] = temporary[0];
    target[1] = temporary[1];
    target[2] = temporary[2];
  } break;
  default: {
    Ring1_Status_set(Ring1_Status_UnreachableProgramPointReached);
    Ring2_jump();
  }
  };
}
