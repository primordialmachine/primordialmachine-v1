/// @file Collections/HashMap.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/HashMap.h"

#include "Ring1/Status.h"
#include "Collections/ArrayList.h"
#include "Collections/Collection.h"
#include "Collections/List.h"
#include "Collections/Map.h"
#include "Collections/Pair.h"

typedef struct _MapNode _MapNode;
struct _MapNode {
  _MapNode* next;
  int64_t hashValue;
  Ring2_Value key;
  Ring2_Value value;
};

typedef struct _Map _Map;
struct _Map {
  int64_t size, capacity;
  _MapNode** buckets;
};

/// @brief The minimal capacity.
static size_t const MINIMAL_CAPACITY = 8;

/// @brief The maximal capacity.
static size_t const MAXIMAL_CAPACITY = SIZE_MAX / sizeof(_MapNode*);

#include <math.h>
#include <float.h>

static Ring2_Boolean defaultEqual(Ring2_Value const* x, Ring2_Value const* y) {
  if (x->tag != y->tag)
    return Ring2_Boolean_False;
  if (Ring2_Value_isReal32(x)) {
    // If only one value is NaN, then the values are not equal.
    // If both values are are NaN, then the values are equal.
    // If either value is NaN, normal IEEE754 comparison applies.
    if (isnan(Ring2_Value_getReal32(x)) || isnan(Ring2_Value_getReal32(y))) {
      return isnan(Ring2_Value_getReal32(x)) && isnan(Ring2_Value_getReal32(y));
    }
    return x == y;
  } else {
    return Ring2_Value_isEqualTo(Ring2_Context_get(), x, y);
  }
}

static void maybeResize(Machine_HashMap* self) {
  _Map* pimpl = (_Map*)self->pimpl;
  size_t oldCapacity = pimpl->capacity;
  size_t newCapacity = oldCapacity;

  // (1) Compute new capacity.
  if (pimpl->size >= oldCapacity / 2) {
    if (oldCapacity < MAXIMAL_CAPACITY / 2) {
      newCapacity = oldCapacity * 2;
    } else {
      newCapacity = MAXIMAL_CAPACITY;
    }
  }
  // (2) If new capacity != old capacity, resize.
  if (newCapacity != oldCapacity) {
    _MapNode** oldBuckets = pimpl->buckets;
    _MapNode** newBuckets = NULL;
    if (Ring1_Memory_allocateArray((void **) & newBuckets, newCapacity, sizeof(_MapNode*))) {
      Ring1_Status_set(Ring1_Status_Success);
      // Do *not* raise an exception.
      return;
    }
    for (size_t i = 0, n = newCapacity; i < n; ++i) {
      newBuckets[i] = NULL;
    }
    for (size_t i = 0, n = oldCapacity; i < n; ++i) {
      while (oldBuckets[i]) {
        _MapNode* node = oldBuckets[i];
        oldBuckets[i] = node->next;
        int64_t hashIndex = node->hashValue % newCapacity;
        node->next = newBuckets[hashIndex];
        newBuckets[hashIndex] = node;
      }
    }
    Ring1_Memory_deallocate(oldBuckets);
    pimpl->buckets = newBuckets;
    pimpl->capacity = newCapacity;
  }
}

#include <assert.h>

static void set(Machine_HashMap* self, Ring2_Value key, Ring2_Value value) {
  _Map* pimpl = (_Map*)self->pimpl;
  Ring2_Integer hashValue = Ring2_Value_getHashValue(Ring2_Context_get(), &key);
  int64_t hashIndex = hashValue % pimpl->capacity;
  assert(hashIndex >= 0);
  _MapNode* node;
  for (node = pimpl->buckets[hashIndex]; NULL != node; node = node->next) {
    if (node->hashValue == hashValue) {
      if (defaultEqual(&node->key, &key)) {
        node->key = key;
        node->value = value;
        return;
      }
    }
  }
  if (!node) {
    if (Ring1_Memory_allocate(&node, sizeof(_MapNode))) {
      Ring2_jump();
    }
  }
  node->key = key;
  node->value = value;
  node->hashValue = hashValue;
  node->next = pimpl->buckets[hashIndex];
  pimpl->buckets[hashIndex] = node;
  pimpl->size++;
  maybeResize(self);
}

static Ring2_Value get(Machine_HashMap const* self, Ring2_Value key) {
  _Map const* pimpl = (_Map const*)self->pimpl;
  Ring2_Integer hashValue = Ring2_Value_getHashValue(Ring2_Context_get(), &key);
  int64_t hashIndex = hashValue % pimpl->capacity;
  assert(hashIndex >= 0);
  for (_MapNode* node = pimpl->buckets[hashIndex]; NULL != node; node = node->next) {
    if (node->hashValue == hashValue) {
      if (defaultEqual(&node->key, &key)) {
        return node->value;
      }
    }
  }
  Ring2_Value value;
  Ring2_Value_setVoid(&value, Ring2_Void_Void);
  return value;
}

static size_t getSize(Machine_HashMap const* self) {
  _Map const* pimpl = (_Map const*)self->pimpl;
  return pimpl->size;
}

static void clear(Machine_HashMap* self) {
  _Map* pimpl = (_Map*)self->pimpl;
  for (size_t i = 0, n = pimpl->capacity; i < n; ++i) {
    while (pimpl->buckets[i]) {
      _MapNode* node = pimpl->buckets[i];
      pimpl->buckets[i] = node->next;
      Ring1_Memory_deallocate(node);
      pimpl->size--;
    }
  }
}

static Machine_List* toList(Machine_HashMap const* self) {
  _Map const* map = (_Map const*)self->pimpl;
  Machine_List* list = (Machine_List*)Machine_ArrayList_create();
  for (size_t i = 0, n = map->capacity; i < n; ++i) {
    for (_MapNode* node = map->buckets[i]; NULL != node; node = node->next) {
      Machine_Pair* pair = Machine_Pair_create(node->key, node->value);
      Ring2_Value temporary;
      Ring2_Value_setObject(&temporary, (Machine_Object*)pair);
      Machine_List_append(list, temporary);
    }
  }
  return list;
}

static void Machine_HashMap_constructClass(Machine_HashMap_Class* self);

static void Machine_HashMap_implement_Machine_Collection(Machine_Collection_Dispatch* self) {
  self->clear = (void (*)(Machine_Collection*)) & clear;
  self->getSize = (size_t(*)(Machine_Collection const*)) & getSize;
}

static void Machine_HashMap_implement_Machine_Map(Machine_Map_Dispatch* self) {
  self->get = (Ring2_Value(*)(Machine_Map const*, Ring2_Value)) & get;
  self->set = (void (*)(Machine_Map*, Ring2_Value, Ring2_Value)) & set;
  self->toList = (Machine_List * (*)(Machine_Map const*)) & toList;
}

static void Machine_HashMap_implementInterfaces(Machine_ClassType* self) {
  Machine_ClassType_implement(
      self, Machine_Collection_getType(),
      (Machine_InterfaceConstructCallback*)&Machine_HashMap_implement_Machine_Collection);
  Machine_ClassType_implement(
      self, Machine_Map_getType(),
      (Machine_InterfaceConstructCallback*)&Machine_HashMap_implement_Machine_Map);
}

MACHINE_DEFINE_CLASSTYPE(Machine_HashMap, Machine_Object, NULL, &Machine_HashMap_construct, NULL,
                         &Machine_HashMap_constructClass, &Machine_HashMap_implementInterfaces)

static void Machine_HashMap_constructClass(Machine_HashMap_Class* self) {
}

void Machine_HashMap_construct(Machine_HashMap* self, size_t numberOfArguments,
                               Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  _Map* pimpl = NULL;
  if (Ring1_Memory_allocate(&pimpl, sizeof(_Map))) {
    Ring2_jump();
  }
  pimpl->size = 0;
  pimpl->capacity = MINIMAL_CAPACITY;
  pimpl->buckets = NULL;
  if (Ring1_Memory_allocateArray((void **) & pimpl->buckets, pimpl->capacity, sizeof(_MapNode*))) {
    Ring1_Memory_deallocate(pimpl);
    pimpl = NULL;
    Ring2_jump();
  }
  for (size_t i = 0, n = pimpl->capacity; i < n; ++i) {
    pimpl->buckets[i] = NULL;
  }
  self->pimpl = pimpl;
  Machine_setClassType((Machine_Object*)self, Machine_HashMap_getType());
}

Machine_HashMap* Machine_HashMap_create() {
  Machine_ClassType* ty = Machine_HashMap_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_HashMap* self
      = (Machine_HashMap*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
