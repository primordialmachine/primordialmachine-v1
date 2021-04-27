#include "./../Text/LayoutLine.h"

Machine_Text_LayoutLine* Machine_Text_LayoutLine_create(int start, int length) {
  if (start < 0 || length < 0) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  Machine_Text_LayoutLine* self = Machine_allocate(sizeof(Machine_Text_LayoutLine), NULL, NULL);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->start = start;
  self->length = length;
  return self;
}
