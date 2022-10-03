// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Map.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_MAP_H_INCLUDED)
#define RING2_LIBRARY_MAP_H_INCLUDED


#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/Map.h` directly, include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"
typedef struct Machine_List Machine_List;


/// @extends Machine.ICollection.
MACHINE_DECLARE_INTERFACETYPE(Machine_Map)

struct Machine_Map_Dispatch {
  Machine_InterfaceDispatch parent;

  void (*set)(Machine_Map* self, Ring2_Value key, Ring2_Value value);
  Ring2_Value (*get)(Machine_Map const* self, Ring2_Value key);
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
/// 
/// @remark
/// If the specified entry's value is the void value,
/// then the call
/// Machine_Map_set(c, a, k, v)
/// is effectively equivalent to the call
/// Machine_Map_remove(c, a, k).
void Machine_Map_set(Machine_Map* self, Ring2_Value key, Ring2_Value value);

/// @brief Get the value for a key.
/// @param self This map.
/// @param key The key.
/// @return The value for the key if any.
/// If no value for that key exists, the void value is returned.
Ring2_Value Machine_Map_get(Machine_Map const* self, Ring2_Value key);

/// @brief Convert the specified map to a list of key value pairs.
/// @param self This map.
/// @return A Machine_List of Machine_Pair values.
Machine_List* Machine_Map_toList(Machine_Map const* self);


#endif // RING2_LIBRARY_MAP_H_INCLUDED
