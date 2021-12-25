/// @file Collections/Map.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_COLLECTIONS_MAP_H_INCLUDED)
#define MACHINE_COLLECTIONS_MAP_H_INCLUDED

#include "Collections/_header.i"

/// @extends Machine.ICollection.
MACHINE_DECLARE_INTERFACETYPE(Machine_Map)

struct Machine_Map_Dispatch {
  Machine_InterfaceDispatch parent;

  void (*set)(Machine_Map* self, Machine_Value key, Machine_Value value);
  Machine_Value (*get)(Machine_Map const* self, Machine_Value key);
  Machine_List* (*toList)(Machine_Map const* self);
};

/// @brief Insert this map.
/// Performs <code>o[k] = v</code> where <code>o</code> is this map, <code>k</code> is the key, and
/// <code>v</code> is the value. If v = nil, then o[k] = nil.
/// @param self This map.
/// @param key The key.
/// @param value The value.
/// - If a pair with an equivalent key exists in this map, that existing pair is removed.
/// - The specified pair is added to this map.
/// - A pair with a value <code>void</code> is not considered as part of the map.
void Machine_Map_set(Machine_Map* self, Machine_Value key, Machine_Value value);

/// @brief Get the value for a key.
/// @param self This map.
/// @param key The key.
/// @return The value for the key if any.
/// If no value for that key exists, the void value is returned.
Machine_Value Machine_Map_get(Machine_Map const* self, Machine_Value key);

/// @brief Convert the specified map to a list of key value pairs.
/// @param self This map.
/// @return A Machine_List of Machine_Pair values.
Machine_List* Machine_Map_toList(Machine_Map const* self);

#endif // MACHINE_COLLECTIONS_MAP_H_INCLUDED
