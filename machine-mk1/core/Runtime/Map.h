#if !defined(MACHINE_RUNTIME_MAP_H_INCLUDED)
#define MACHINE_RUNTIME_MAP_H_INCLUDED

#include "./Runtime/Collection.h"

/// @brief A map.
MACHINE_DECLARE_CLASSTYPE(Machine_Map)

struct Machine_Map {
  Machine_Collection parent;
  void (*insert)(Machine_Map* self, Machine_Value key, Machine_Value value);
};

/// @brief Construct this map.
/// @param self This map.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void Machine_Map_construct(Machine_Map* self, size_t numberOfArguments, const Machine_Value* arguments);

/// @brief Insert this map.
/// @param self This map.
/// @param key The key.
/// @param value The value.
void Machine_Map_insert(Machine_Map* self, Machine_Value key, Machine_Value value);

#endif // MACHINE_RUNTIME_MAP_H_INCLUDED
