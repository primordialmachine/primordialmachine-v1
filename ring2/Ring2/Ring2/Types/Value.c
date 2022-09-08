// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Value.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Types/Value.h"
#include "Ring2/_Include.h"

void Ring2_Value_visit(Ring2_Value* self) {
  switch (self->tag) {
    case Ring2_Value_Tag_Object:
      Ring2_Gc_visit(Ring2_Gc_get(), self->objectValue);
      break;
    case Ring2_Value_Tag_String:
      Ring2_Gc_visit(Ring2_Gc_get(), self->stringValue);
      break;
  };
}

Ring2_Boolean Ring2_Value_isEqualTo(Ring2_Value const* x, Ring2_Value const* y) {
  if (x->tag != y->tag) {
    return false;
  }
  switch (x->tag) {
    case Ring2_Value_Tag_Object:
      return Machine_Object_isEqualTo(Ring2_Context_get(), x->objectValue, y);
    case Ring2_Value_Tag_String:
      return Ring2_String_isEqualTo(Ring2_Context_get(), x->stringValue, y->stringValue);
    case Ring2_Value_Tag_Void:
      return Ring2_Void_isEqualTo(Ring2_Context_get(), x->voidValue, y->voidValue);
    case Ring2_Value_Tag_Real32:
      return Ring2_Real32_isEqualTo(Ring2_Context_get(), x->real32Value, y->real32Value);
    case Ring2_Value_Tag_Integer:
      return Ring2_Integer_isEqualTo(Ring2_Context_get(), x->integerValue, y->integerValue);
    case Ring2_Value_Tag_Boolean:
      return Ring2_Boolean_isEqualTo(Ring2_Context_get(), x->booleanValue, y->booleanValue);
    case Ring2_Value_Tag_ForeignProcedure:
      return Ring2_ForeignProcedure_isEqualTo(Ring2_Context_get(), x->foreignProcedureValue, y->foreignProcedureValue);
    default:
      Ring2_unreachable();
  };
}

Ring2_Integer Ring2_Value_getHashValue(Ring2_Value const* self) {
  switch (self->tag) {
    case Ring2_Value_Tag_Object:
      return Machine_Object_getHashValue(Ring2_Context_get(), self->objectValue);
    case Ring2_Value_Tag_String:
      return Ring2_String_getHashValue(Ring2_Context_get(), self->stringValue);
    case Ring2_Value_Tag_Void:
      return Ring2_Void_getHashValue(Ring2_Context_get(),self->voidValue);
    case Ring2_Value_Tag_Real32:
      return Ring2_Real32_getHashValue(Ring2_Context_get(), self->real32Value);
    case Ring2_Value_Tag_Integer:
      return Ring2_Integer_getHashValue(Ring2_Context_get(), self->integerValue);
    case Ring2_Value_Tag_Boolean:
      return Ring2_Boolean_getHashValue(Ring2_Context_get(), self->booleanValue);
    case Ring2_Value_Tag_ForeignProcedure:
      return Ring2_ForeignProcedure_getHashValue(Ring2_Context_get(), self->foreignProcedureValue);
    default:
      Ring2_unreachable();
  };
}

void Ring2_Value_swap(Ring2_Value* x, Ring2_Value* y) {
  Ring2_Value t = *x;
  *x = *y;
  *y = t;
}
