#include "Runtime/Map.h"

MACHINE_DEFINE_CLASSTYPE(Machine_Map)

Machine_ClassType* Machine_Map_getClassType() {
  if (!g_Machine_Map_ClassType) {
    g_Machine_Map_ClassType =
      Machine_createClassType
        (
          Machine_Collection_getClassType(),
          sizeof(Machine_Map),
          (Machine_ClassTypeRemovedCallback*)&Machine_Map_onTypeDestroyed,
          (Machine_ClassObjectVisitCallback*)NULL,
          (Machine_ClassObjectConstructCallback*)&Machine_Map_construct,
          (Machine_ClassObjectDestructCallback*)NULL
        );
  }
  return g_Machine_Map_ClassType;
}

void Machine_Map_construct(Machine_Map* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Collection_construct((Machine_Collection *)self, numberOfArguments, arguments);
  Machine_setClassType(self, Machine_Map_getClassType());
}

void Machine_Map_insert(Machine_Map* self, Machine_Value key, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  self->insert(self, key, value);
}
