#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Value.h"

#include "Runtime/Assertions.h"
#include "Runtime/Object/Object.h"
#include "Runtime/String.h"

void Machine_Value_visit(Machine_Value* self) {
  switch (self->tag) {
    case Machine_ValueFlag_Object:
      Machine_Gc_visit(self->objectValue);
      break;
    case Machine_ValueFlag_String:
      Machine_Gc_visit(self->stringValue);
      break;
  };
}

Ring2_Boolean Machine_Value_isEqualTo(Machine_Value const* x, Machine_Value const* y) {
  if (x->tag != y->tag) {
    return false;
  }
  switch (x->tag) {
    case Machine_ValueFlag_Object:
      return Machine_Object_isEqualTo(x->objectValue, y->objectValue);
    case Machine_ValueFlag_String:
      return Machine_String_isEqualTo(x->stringValue, y->stringValue);
    case Machine_ValueFlag_Void:
      return Ring2_Void_isEqualTo(Ring2_Context_get(), x->voidValue, y->voidValue);
    case Machine_ValueFlag_Real:
      return Ring2_Real32_isEqualTo(Ring2_Context_get(), x->realValue, y->realValue);
    case Machine_ValueFlag_Integer:
      return Ring2_Integer_isEqualTo(Ring2_Context_get(), x->integerValue, y->integerValue);
    case Machine_ValueFlag_Boolean:
      return Ring2_Boolean_isEqualTo(Ring2_Context_get(), x->booleanValue, y->booleanValue);
    case Machine_ValueFlag_ForeignProcedure:
      return Machine_ForeignProcedure_isEqualTo(x->foreignProcedureValue, y->foreignProcedureValue);
    default:
      MACHINE_ASSERT_UNREACHABLE();
  };
}

Ring2_Integer Machine_Value_getHashValue(Machine_Value const* self) {
  switch (self->tag) {
    case Machine_ValueFlag_Object:
      return Machine_Object_getHashValue(self->objectValue);
    case Machine_ValueFlag_String:
      return Machine_String_getHashValue(self->stringValue);
    case Machine_ValueFlag_Void:
      return Ring2_Void_getHashValue(Ring2_Context_get(),self->voidValue);
    case Machine_ValueFlag_Real:
      return Ring2_Real32_getHashValue(Ring2_Context_get(), self->realValue);
    case Machine_ValueFlag_Integer:
      return Ring2_Integer_getHashValue(Ring2_Context_get(), self->integerValue);
    case Machine_ValueFlag_Boolean:
      return Ring2_Boolean_getHashValue(Ring2_Context_get(), self->booleanValue);
    case Machine_ValueFlag_ForeignProcedure:
      return Machine_ForeignProcedure_getHashValue(self->foreignProcedureValue);
    default:
      MACHINE_ASSERT_UNREACHABLE();
  };
}

void Machine_Value_swap(Machine_Value* x, Machine_Value* y) {
  Machine_Value t = *x;
  *x = *y;
  *y = t;
}
