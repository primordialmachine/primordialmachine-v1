#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Object/ClassType.module.h"

bool Machine_ClassType_isSubTypeOf(Machine_ClassType const* self, Machine_ClassType const* other) {
  Machine_ClassType const* currentType = self;
  while (currentType != NULL) {
    if (currentType == other) {
      return true;
    }
    currentType = currentType->parent;
  }
  return false;
}

bool Machine_ClassType_isTrueSubTypeOf(Machine_ClassType const* self,
                                       Machine_ClassType const* other) {
  if (self == other) {
    return false;
  }
  Machine_ClassType const* currentType = self;
  while (currentType != NULL) {
    if (currentType == other) {
      return true;
    }
    currentType = currentType->parent;
  }
  return false;
}
