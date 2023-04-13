// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Value.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_VALUE_H_INCLUDED)
#define RING2_OPERATIONS_VALUE_H_INCLUDED

#include "Ring2/Types/Value.h"

Ring1_CheckReturn() Ring2_Boolean
Ring2_Value_isEqualTo
  (
    Ring2_Context* context,
    Ring2_Value const *x,
    Ring2_Value const *y
  );

Ring1_CheckReturn() Ring2_Boolean
Ring2_Value_isNotEqualTo
  (
    Ring2_Context* context,
    Ring2_Value const *x,
    Ring2_Value const *y
  );

/// Array x Array -> Boolean
/// Boolean x Boolean -> Boolean
/// Integer x Integer -> Boolean
/// Real x Real -> Boolean
/// Void x Void -> Boolean
/// Object x (Array U Object U PrimitiveType) ~> Boolean
/// PrimitiveType := Boolean U Integer U Real U Void
void
Ring2_Value_isLowerThan
  (
    Ring2_Context* context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  );

/// Array x Array -> Boolean
/// Boolean x Boolean -> Boolean
/// Integer x Integer -> Boolean
/// Real x Real -> Boolean
/// Void x Void -> Boolean
/// Object x (Array U Object U PrimitiveType) ~> Boolean
/// PrimitiveType := Boolean U Integer U Real U Void
void
Ring2_Value_isLowerThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  );

/// Array x Array -> Boolean
/// Boolean x Boolean -> Boolean
/// Integer x Integer -> Boolean
/// Real x Real -> Boolean
/// Void x Void -> Boolean
/// Object x (Array U Object U PrimitiveType) ~> Boolean
/// PrimitiveType := Boolean U Integer U Real U Void
void
Ring2_Value_isGreaterThan
  (
    Ring2_Context* context,
    Ring2_Value const *x,
    Ring2_Value const *y,
    Ring2_Value *z
  );

/// Array x Array -> Boolean
/// Boolean x Boolean -> Boolean
/// Integer x Integer -> Boolean
/// Real x Real -> Boolean
/// Void x Void -> Boolean
/// Object x (Array U Object U PrimitiveType) ~> Boolean
/// PrimitiveType := Boolean U Integer U Real U Void
void
Ring2_Value_isGreaterThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Value const *x,
    Ring2_Value const *y,
    Ring2_Value* z
  );

Ring1_CheckReturn() Ring2_Integer
Ring2_Value_getHashValue
  (
    Ring2_Context* context,
    Ring2_Value const *x
  );

void
Ring2_Value_toString
  (
    Ring2_Context *context,
    Ring2_Value const *x,
    Ring2_Value *y
  );

#endif // RING2_OPERATIONS_VALUE_H_INCLUDED
