/// @file Collections/Map.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/Map.h"

#include "_Runtime.h"
#include "Collections/List.h"
#include "Collections/Pair.h"
#include <memory.h>


typedef struct Node Node;
struct Node {
  Node* next;
  size_t hashValue;
  Machine_Value key;
  Machine_Value value;
};

typedef struct Map Map;
struct Map {
  size_t size, capacity;
  Node** buckets;
};

static const size_t MINIMAL_CAPACITY = 8;
static const size_t MAXIMAL_CAPACITY = SIZE_MAX / sizeof(Node*);

static void maybeResize(Machine_Map* self) {
  Map* pimpl = self->pimpl;
  size_t oldCapacity = pimpl->capacity;
  size_t newCapacity = oldCapacity;

  // (1) Compute new capacity.
  if (pimpl->size >= oldCapacity / 2) {
    if (oldCapacity < MAXIMAL_CAPACITY / 2) {
      newCapacity = oldCapacity * 2;
    }
    else {
      newCapacity = MAXIMAL_CAPACITY;
    }
  }
  // (2) If new capacity != old capacity, resize.
  if (newCapacity != oldCapacity) {
    Node** oldBuckets = pimpl->buckets;
    Node** newBuckets = c_alloc_a(sizeof(Node*), newCapacity);
    if (!newBuckets) {
      /*
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
      */
      // Do *not* raise an exception.
      return;
    }
    for (size_t i = 0, n = newCapacity; i < n; ++i) {
      newBuckets[i] = NULL;
    }
    for (size_t i = 0, n = oldCapacity; i < n; ++i) {
      while (oldBuckets[i]) {
        Node* node = oldBuckets[i]; oldBuckets[i] = node->next;
        size_t hashIndex = node->hashValue % newCapacity;
        node->next = newBuckets[hashIndex];
        newBuckets[hashIndex] = node;
      }
    }
    c_dealloc(oldBuckets);
    pimpl->buckets = newBuckets;
    pimpl->capacity = newCapacity;
  }
}

static void set(Machine_Map* self, Machine_Value key, Machine_Value value) {
  Map* pimpl = (Map*)self->pimpl;
  size_t hashValue = Machine_Value_getHashValue(&key);
  size_t hashIndex = hashValue % pimpl->capacity;
  Node* node;
  for (node = pimpl->buckets[hashIndex]; NULL != node; node = node->next) {
    if (node->hashValue == hashValue) {
      if (Machine_Value_isEqualTo(&node->key, &key)) {
        node->key = key;
        node->value = value;
        return;
      }
    }
  }
  if (!node) {
    node = c_alloc(sizeof(Node));
    if (!node) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
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

static Machine_Value get(const Machine_Map* self, Machine_Value key) {
  const Map* pimpl = (const Map*)self->pimpl;
  size_t hashValue = Machine_Value_getHashValue(&key);
  size_t hashIndex = hashValue % pimpl->capacity;
  for (Node* node = pimpl->buckets[hashIndex]; NULL != node; node = node->next) {
    if (node->hashValue == hashValue) {
      if (Machine_Value_isEqualTo(&node->key, &key)) {
        return node->value;
      }
    }
  }
  Machine_Value value;
  Machine_Value_setVoid(&value, Machine_Void_Void);
  return value;
}

static size_t getSize(const Machine_Map* self) {
  Map* pimpl = (Map*)self->pimpl;
  return pimpl->size;
}

static void clear(Machine_Map* self) {
  Map* pimpl = (Map*)self->pimpl;
  for (size_t i = 0, n = pimpl->capacity; i < n; ++i) {
    while (pimpl->buckets[i]) {
      Node* node = pimpl->buckets[i];
      pimpl->buckets[i] = node->next;
      c_dealloc(node);
      pimpl->size--;
    }
  }
}

static void Machine_Map_constructClass(Machine_Map_Class* self);

MACHINE_DEFINE_CLASSTYPE(Machine_Map, Machine_Collection, NULL, &Machine_Map_construct, NULL, &Machine_Map_constructClass)

static void Machine_Map_constructClass(Machine_Map_Class* self) {
  self->get = &get;
  self->set = &set;
  ((Machine_Collection_Class*)self)->clear = (void (*)(Machine_Collection*)) & clear;
  ((Machine_Collection_Class*)self)->getSize = (size_t(*)(const Machine_Collection*)) & getSize;
}

void Machine_Map_construct(Machine_Map* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Collection_construct((Machine_Collection*)self, numberOfArguments, arguments);
  Map* pimpl = c_alloc(sizeof(Map));
  if (!pimpl) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  pimpl->size = 0;
  pimpl->capacity = MINIMAL_CAPACITY;
  pimpl->buckets = c_alloc_a(sizeof(Node*), pimpl->capacity);
  if (!pimpl->buckets) {
    c_dealloc(pimpl);
    pimpl = NULL;
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  for (size_t i = 0, n = pimpl->capacity; i < n; ++i) {
    pimpl->buckets[i] = NULL;
  }
  self->pimpl = pimpl;
  Machine_setClassType((Machine_Object*)self, Machine_Map_getClassType());
}

Machine_Map* Machine_Map_create() {
  Machine_ClassType* ty = Machine_Map_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Map* self = (Machine_Map*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_Map_set(Machine_Map* self, Machine_Value key, Machine_Value value) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Map, set, key, value);
}

Machine_Value Machine_Map_get(const Machine_Map* self, Machine_Value key) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_Map, get, key);
}

Machine_List* Machine_Map_toList(const Machine_Map* self) {
  Map* map = (Map*)self->pimpl;
  Machine_List* list = Machine_List_create();
  for (size_t i = 0, n = map->capacity; i < n; ++i) {
    for (Node* node = map->buckets[i]; NULL != node; node = node->next) {
      Machine_Pair *pair = Machine_Pair_create(node->key, node->value);
      Machine_Value temporary;
      Machine_Value_setObject(&temporary, (Machine_Object*)pair);
      Machine_List_append(list, temporary);
    }
  }
  return list;
}
