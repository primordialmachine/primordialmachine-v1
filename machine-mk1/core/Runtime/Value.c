#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Value.h"

#include "Runtime/Assertions.h"
#include "Runtime/Object/Object.h"
#include "Ring2/_Include.h"

void Machine_Value_visit(Machine_Value* self) {
  switch (self->tag) {
    case Ring2_Value_Tag_Object:
      Machine_Gc_visit(self->objectValue);
      break;
    case Ring2_Value_Tag_String:
      Machine_Gc_visit(self->stringValue);
      break;
  };
}

Ring2_Boolean Machine_Value_isEqualTo(Machine_Value const* x, Machine_Value const* y) {
  if (x->tag != y->tag) {
    return false;
  }
  switch (x->tag) {
    case Ring2_Value_Tag_Object:
      return Machine_Object_isEqualTo(x->objectValue, y->objectValue);
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
    case Ring2_Value_Tag_ForeignFunction:
      return Machine_ForeignProcedure_isEqualTo(Ring2_Context_get(), x->foreignProcedureValue, y->foreignProcedureValue);
    default:
      MACHINE_ASSERT_UNREACHABLE();
  };
}

Ring2_Integer Machine_Value_getHashValue(Machine_Value const* self) {
  switch (self->tag) {
    case Ring2_Value_Tag_Object:
      return Machine_Object_getHashValue(self->objectValue);
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
    case Ring2_Value_Tag_ForeignFunction:
      return Machine_ForeignProcedure_getHashValue(Ring2_Context_get(), self->foreignProcedureValue);
    default:
      MACHINE_ASSERT_UNREACHABLE();
  };
}

void Machine_Value_swap(Machine_Value* x, Machine_Value* y) {
  Machine_Value t = *x;
  *x = *y;
  *y = t;
}
