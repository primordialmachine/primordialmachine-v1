#include "Runtime/Collection.h"

MACHINE_DEFINE_CLASSTYPE(Machine_Collection)

Machine_ClassType* Machine_Collection_getClassType() {
  if (!g_Machine_Collection_ClassType) {
    g_Machine_Collection_ClassType =
      Machine_createClassType
        (
          NULL,
          sizeof(Machine_Collection),
          (Machine_ClassTypeRemovedCallback*)&Machine_Collection_onTypeDestroyed,
          (Machine_ClassObjectVisitCallback*)NULL,
          (Machine_ClassObjectConstructCallback*)&Machine_Collection_construct,
          (Machine_ClassObjectDestructCallback*)NULL
        );
  }
  return g_Machine_Collection_ClassType;
}

void Machine_Collection_construct(Machine_Collection* self, size_t numberOfArguments, const Machine_Value* arguments) {
  MACHINE_ASSERT_NOTNULL(self);
  Machine_setClassType(self, Machine_Collection_getClassType());
}

void Machine_Collection_clear(Machine_Collection* self) {
  MACHINE_ASSERT_NOTNULL(self);
  self->clear(self);
}

size_t Machine_Collection_getSize(const Machine_Collection* self) {
  MACHINE_ASSERT_NOTNULL(self);
  return self->getSize(self);
}
