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


Machine_Boolean Machine_Value_isEqualTo(Machine_Value const* x, Machine_Value const* y) {
  if (x->tag != y->tag) {
    return false;
  }
  switch (x->tag) {
  case Machine_ValueFlag_Object:
    return Machine_Object_isEqualTo(x->objectValue, y->objectValue);
  case Machine_ValueFlag_String:
    return Machine_String_isEqualTo(x->stringValue, y->stringValue);
  case Machine_ValueFlag_Void:
    return Machine_Void_isEqualTo(x->voidValue, y->voidValue);
  case Machine_ValueFlag_Real:
    return Machine_Real_isEqualTo(x->realValue, y->realValue);
  case Machine_ValueFlag_Integer:
    return Machine_Integer_isEqualTo(x->integerValue, y->integerValue);
  case Machine_ValueFlag_Boolean:
    return Machine_Boolean_isEqualTo(x->booleanValue, y->booleanValue);
  case Machine_ValueFlag_ForeignProcedure:
    return Machine_ForeignProcedure_isEqualTo(x->foreignProcedureValue, y->foreignProcedureValue);
  default:
    MACHINE_ASSERT_UNREACHABLE();
  };
}

Machine_Integer Machine_Value_getHashValue(Machine_Value const* self) {
  switch (self->tag) {
  case Machine_ValueFlag_Object:
    return Machine_Object_getHashValue(self->objectValue);
  case Machine_ValueFlag_String:
    return Machine_String_getHashValue(self->stringValue);
  case Machine_ValueFlag_Void:
    return Machine_Void_getHashValue(self->voidValue);
  case Machine_ValueFlag_Real:
    return Machine_Real_getHashValue(self->realValue);
  case Machine_ValueFlag_Integer:
    return Machine_Integer_getHashValue(self->integerValue);
  case Machine_ValueFlag_Boolean:
    return Machine_Boolean_getHashValue(self->booleanValue);
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
