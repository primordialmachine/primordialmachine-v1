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
typedef struct Ring2_List Ring2_List;


/// @extends Ring2.Collection.
/// @brief
/// A map is a mapping from keys to values.
/// @details
/// A map is defined as a list of tuples (k1, v1), ..., (kn, vn) such that
/// - no (ki, vi), (kj, vj) exists where i != j exists with k ~ v.
/// - no (ki, vi) exists with a key of <code>void</code> or <code>notNumber</code>.
/// - no (ki, vi) exists with a value of <code>void</code>.
/// We call ki a "key" and vi a "value".
/// @remarks
/// A map supports the operations set, get, and remove.
/// 
/// set(k, v) given a key k and a value v, this adds a tuple (k,v) to the map.
/// - remove(k) is invoked
/// - Next, if v is not void, the pair (k,v) is added.
/// 
/// remove(k) given a key k, this removes a tuple (k',v') k'~k from the map.
///  - If k is <code>void</code> or <code>noNumber</code>, an error is raised.
///  - Otherwise a pair (k',v') is removed if it exists.
/// 
/// get(k) : v given a key k, this gets the v' of the tuple (k',v'), k~k' in the map.
//  - If k is <code>void</code> or <code>noNumber</code>, an error is raised.
/// - If <code>(k',v')</code> exists, then v' is returned. Otherwise void is returned.
/// 
/// set MAP x VALUE x VALUE -> MAP, set(map : Map, key : VALUE, value : VALUE) adds a key
MACHINE_DECLARE_INTERFACETYPE(Ring2_Map)

struct Ring2_Map_Dispatch {
  Machine_InterfaceDispatch parent;

  Ring2_Value (*get)(Ring2_Map const* self, Ring2_Value key);
  void (*remove)(Ring2_Map* self, Ring2_Value key);
  void (*set)(Ring2_Map* self, Ring2_Value key, Ring2_Value value);
  Ring2_List* (*toList)(Ring2_Map const* self);
};

/// @brief Get the value for a key.
/// @param self This map.
/// @param key The key.
/// @return The value for the key if any.
/// If no value for that key exists, the void value is returned.
Ring2_Value
Ring2_Map_get
  (
    Ring2_Map const* self,
    Ring2_Value key
  );

/// @brief Remove a value for a key.
/// @param self This map.
/// @param key The key.
void
Ring2_Map_remove
  (
    Ring2_Map* self,
    Ring2_Value key
  );

/// @brief Insert into this map.
/// 
/// @param self This map.
/// @param key The key.
/// @param value The value.
void
Ring2_Map_set
  (
    Ring2_Map* self,
    Ring2_Value key,
    Ring2_Value value
  );

/// @brief Convert the specified map to a list of key value pairs.
/// @param self This map.
/// @return A Ring2.List of Ring2.Pair values.
Ring2_List*
Ring2_Map_toList
  (
    Ring2_Map const* self
  );


#endif // RING2_LIBRARY_MAP_H_INCLUDED
