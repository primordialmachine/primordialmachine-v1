// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Value.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Types/Value.h"
#include "Ring2/_Include.h"

void Ring2_Value_visit(Ring2_Gc *gc, Ring2_Value* self) {
  switch (self->tag) {
    case Ring2_Value_Tag_Object:
      Ring2_Gc_visit(Ring2_Gc_get(), self->objectValue);
      break;
    case Ring2_Value_Tag_String:
      Ring2_Gc_visit(Ring2_Gc_get(), self->stringValue);
      break;
  };
}

Ring2_Boolean Ring2_Value_isEqualTo(Ring2_Context *context, Ring2_Value const* x, Ring2_Value const* y) {
  if (x->tag != y->tag) {
    return false;
  }
  switch (x->tag) {
    case Ring2_Value_Tag_Object:
      return Machine_Object_isEqualTo(context, x->objectValue, y);
    case Ring2_Value_Tag_String:
      return Ring2_String_isEqualTo(context, x->stringValue, y->stringValue);
    case Ring2_Value_Tag_Void:
      return Ring2_Void_isEqualTo(context, x->voidValue, y->voidValue);
    case Ring2_Value_Tag_Real32:
      return Ring2_Real32_isEqualTo(context, x->real32Value, y->real32Value);
    case Ring2_Value_Tag_Integer:
      return Ring2_Integer_isEqualTo(context, x->integerValue, y->integerValue);
    case Ring2_Value_Tag_Boolean:
      return Ring2_Boolean_isEqualTo(context, x->booleanValue, y->booleanValue);
    case Ring2_Value_Tag_ForeignProcedure:
      return Ring2_ForeignProcedure_isEqualTo(context, x->foreignProcedureValue, y->foreignProcedureValue);
    default:
      Ring2_unreachable();
  };
}

Ring2_Integer Ring2_Value_getHashValue(Ring2_Context *context, Ring2_Value const* self) {
  switch (self->tag) {
    case Ring2_Value_Tag_Object:
      return Machine_Object_getHashValue(context, self->objectValue);
    case Ring2_Value_Tag_String:
      return Ring2_String_getHashValue(context, self->stringValue);
    case Ring2_Value_Tag_Void:
      return Ring2_Void_getHashValue(context,self->voidValue);
    case Ring2_Value_Tag_Real32:
      return Ring2_Real32_getHashValue(context, self->real32Value);
    case Ring2_Value_Tag_Integer:
      return Ring2_Integer_getHashValue(context, self->integerValue);
    case Ring2_Value_Tag_Boolean:
      return Ring2_Boolean_getHashValue(context, self->booleanValue);
    case Ring2_Value_Tag_ForeignProcedure:
      return Ring2_ForeignProcedure_getHashValue(context, self->foreignProcedureValue);
    default:
      Ring2_unreachable();
  };
}

void Ring2_Value_swap(Ring2_Value* x, Ring2_Value* y) {
  Ring2_Value t = *x;
  *x = *y;
  *y = t;
}
