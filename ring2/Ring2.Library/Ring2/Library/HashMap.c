// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/HashMap.c
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/HashMap.h"
#undef RING2_LIBRARY_PRIVATE

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Collection.h"
#include "Ring2/Library/List.h"
#include "Ring2/Library/Map.h"
#include "Ring2/Library/Pair.h"
#include "Ring2/Library/ArrayList.h"
#undef RING2_LIBRARY_PRIVATE


#include "Ring1/Memory.h"
#include <assert.h>
#include <stdio.h>


#include "Ring1/Status.h"
#include "Ring2/Library/_Include.h"


#include <math.h>
#include <float.h>


static Ring2_Boolean
defaultEqual
  (
    Ring2_Value const* x,
    Ring2_Value const* y
  )
{
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
  } else if (Ring2_Value_isReal64(x)) {
    // If only one value is NaN, then the values are not equal.
    // If both values are are NaN, then the values are equal.
    // If either value is NaN, normal IEEE754 comparison applies.
    if (isnan(Ring2_Value_getReal64(x)) || isnan(Ring2_Value_getReal64(y))) {
      return isnan(Ring2_Value_getReal64(x)) && isnan(Ring2_Value_getReal64(y));
    }
    return x == y;
  } else {
    return Ring2_Value_isEqualTo(Ring2_Context_get(), x, y);
  }
}

typedef struct Node {
  /// @brief The node which was moved out of place because of this node.
  struct Node* next;
  /// @brief The key.
  Ring2_Value key;
  /// @brief The value.
  Ring2_Value value;
  /// @brief The hash value. Cached from Mkx_Interpreter_Value_hashValue(context, &key).
  int64_t hashValue;
} Node;

struct Machine_HashMap_Class {
  Machine_Object_Class _parent;
};

struct Machine_HashMap {
  Machine_Object _parent;
  Node **buckets;
  int64_t size, capacity;
};


/// @brief The minimal capacity.
static int64_t const MINIMAL_CAPACITY = 8;

/// @brief The maximal capacity.
static int64_t const MAXIMAL_CAPACITY = (INT64_MAX < SIZE_MAX ? INT64_MAX : SIZE_MAX) / sizeof(Node*);


static void
clear
  (
    Machine_HashMap* self
  );

static Ring2_Value
get
  (
    Machine_HashMap const* self,
    Ring2_Value key
  );

static int64_t
getSize
  (
    Machine_HashMap const* self
  );

static void
maybeResize
  (
    Machine_HashMap *self
  );

static void
set
  (
    Machine_HashMap* self,
    Ring2_Value key,
    Ring2_Value value
  );

static Machine_List*
toList
  (
    Machine_HashMap const* self
  );

static void
implement_Machine_Collection
  (
    Machine_Collection_Dispatch* self
  );

static void
implement_Machine_Map
  (
    Machine_Map_Dispatch* self
  );

static void
implementInterfaces
  (
    Machine_ClassType* self
  );

static void
Machine_HashMap_destruct
  (
    Machine_HashMap* self
  );

static void
Machine_HashMap_visit
  (
    Machine_HashMap* self
  );

MACHINE_DEFINE_CLASSTYPE(Machine_HashMap /*type*/,
                         Machine_Object /*parentType*/,
                         &Machine_HashMap_visit /*visit*/,
                         &Machine_HashMap_construct /*construct*/,
                         &Machine_HashMap_destruct /*destruct*/,
                         NULL /*constructClass*/,
                         &implementInterfaces)

static void
clear
  (
    Machine_HashMap* self
  )
{
  if (self->buckets) {
    for (int64_t i = 0, n = self->capacity; i < n; ++i) {
      Node** bucket = &(self->buckets[i]);
      while (*bucket) {
        Node* node = *bucket;
        *bucket = node->next;
        Ring1_Memory_deallocate(node);
        self->size--;
      }
    }
  }
}

static Ring2_Value
get
  (
    Machine_HashMap const* self,
    Ring2_Value key
  )
{
  int64_t hashValue = Ring2_Value_getHashValue(Ring2_Context_get(), &key);
  int64_t hashIndex = hashValue % self->capacity;
  for (Node* node = self->buckets[hashIndex]; NULL != node; node = node->next) {
    if (node->hashValue == hashValue && Ring2_Value_isEqualTo(Ring2_Context_get(), &key, &node->key))
    { return node->value; }
  }
  Ring2_Value result;
  Ring2_Value_setVoid(&result, Ring2_Void_Void);
  return result;
}

static int64_t
getSize
  (
    Machine_HashMap const* self
  )
{ return self->size; }

static void
maybeResize
  ( 
    Machine_HashMap *self
  )
{
  int64_t oldCapacity = self->capacity;
  int64_t newCapacity = oldCapacity;

  // (1) Compute new capacity.
  if (self->size >= oldCapacity / 2) {
    if (oldCapacity < MAXIMAL_CAPACITY / 2) {
      newCapacity = oldCapacity * 2;
    } else {
      newCapacity = MAXIMAL_CAPACITY;
    }
  }
  // (2) If new capacity != old capacity, resize.
  if (newCapacity != oldCapacity) {
    Node** oldBuckets = self->buckets;
    Node** newBuckets = NULL;
    if (Ring1_Memory_allocateArray((void **) & newBuckets, newCapacity, sizeof(Node *))) {
      Ring1_Status_set(Ring1_Status_Success);
      // Do *not* raise an exception.
      return;
    }
    for (int64_t i = 0, n = newCapacity; i < n; ++i) {
      newBuckets[i] = NULL;
    }
    for (int64_t i = 0, n = oldCapacity; i < n; ++i) {
      while (oldBuckets[i]) {
        Node* node = oldBuckets[i];
        oldBuckets[i] = node->next;
        int64_t hashIndex = node->hashValue % newCapacity;
        node->next = newBuckets[hashIndex];
        newBuckets[hashIndex] = node;
      }
    }
    Ring1_Memory_deallocate(oldBuckets);
    self->buckets = newBuckets;
    self->capacity = newCapacity;
  }
}

static void
set
  (
    Machine_HashMap* self,
    Ring2_Value key,
    Ring2_Value value
  )
{
  int64_t hashValue = Ring2_Value_getHashValue(Ring2_Context_get(), &key);
  int64_t hashIndex = hashValue % self->capacity;
  Node* node;
  for (node = self->buckets[hashIndex]; NULL != node; node = node->next) {
    if (node->hashValue == hashValue && Ring2_Value_isEqualTo(Ring2_Context_get(), &key, &node->key)) {
      break;
    }
  }
  if (!node) {
    if (Ring1_Memory_allocate(&node, sizeof(Node))) {
      fprintf(stderr, "unable to allocate node");
      Ring2_jump();
    }
    node->next = self->buckets[hashIndex]; self->buckets[hashIndex] = node;
    self->size++;
  }
  node->key = key;
  node->value = value;
  node->hashValue = hashValue;
  maybeResize(self);
}

static Machine_List*
toList
  (
    Machine_HashMap const* self
  )
{ 
  Machine_List* list = (Machine_List*)Machine_ArrayList_create();
  for (int64_t i = 0, n = self->capacity; i < n; ++i) {
    for (Node* node = self->buckets[i]; NULL != node; node = node->next) {
      Machine_Pair* pair = Machine_Pair_create(node->key, node->value);
      Ring2_Value temporary;
      Ring2_Value_setObject(&temporary, (Machine_Object *)pair);
      Machine_List_append(list, temporary);
    }
  }
  return list;
}


static void
implement_Machine_Collection
  (
    Machine_Collection_Dispatch* self
  )
{
  self->clear = (void (*)(Machine_Collection*)) & clear;
  self->getSize = (int64_t(*)(Machine_Collection const*)) & getSize;
}

static void
implement_Machine_Map
  (
    Machine_Map_Dispatch* self
  )
{
  self->get = (Ring2_Value (*)(Machine_Map const*, Ring2_Value)) & get;
  self->set = (void (*)(Machine_Map*, Ring2_Value, Ring2_Value)) & set;
  self->toList = (Machine_List * (*)(Machine_Map const*)) & toList;
}

static void
implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement(self, Machine_Collection_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Machine_Collection);
  Machine_ClassType_implement(self, Machine_Map_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Machine_Map);
}

static void
Machine_HashMap_destruct
  (
    Machine_HashMap* self
  )
{
  clear(self);
  if (self->buckets) {
    Ring1_Memory_deallocate(self->buckets);
    self->buckets = NULL;
  }
}

static void
Machine_HashMap_visit
  (
    Machine_HashMap* self
  )
{
  if (self->buckets) {
    Ring2_Gc* gc = Ring2_Gc_get();
    // Remove nodes with values of type void.
    // Visit key and value of all other nodes.
    int64_t allNodes = 0, deadNodes = 0, liveNodes = 0;
    for (int64_t i = 0, n = self->capacity; i < n; ++i) {
      Node** previous = &(self->buckets[i]);
      Node* current = self->buckets[i];
      while (current) {
        if (Ring2_Value_isVoid(&current->value)) {
          Node* node = current;
          *previous = current->next;
          current = current->next;
          Ring1_Memory_deallocate(node);
          deadNodes++;
          self->size--;
        } else {
          Ring2_Value_visit(gc, &current->key);
          Ring2_Value_visit(gc, &current->value);
          liveNodes++;
          previous = &current->next;
          current = current->next;
        }
        allNodes++;
      }
    }
  }
}

void
Machine_HashMap_construct
  (
    Machine_HashMap *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->size = 0;
  self->capacity = 8;
  self->buckets = NULL;
  if (Ring1_Memory_allocateArray((void **)&self->buckets, (size_t)self->capacity, sizeof(Node*))) {
    fprintf(stderr, "unable to allocate buckets");
    Ring2_jump();
  }
  Ring1_Memory_zeroFillArray(self->buckets, (size_t)self->capacity, sizeof(Node*));
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Machine_HashMap_getType());
}

Machine_HashMap *
Machine_HashMap_create
  (
  )
{
  Machine_ClassType* ty = Machine_HashMap_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  Ring2_Value ARGUMENTS[1] = { Ring2_Value_StaticInitializerVoid() };
  Machine_HashMap* self = (Machine_HashMap *)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void
Machine_HashMap_remove
  (
    Machine_HashMap* self,
    Ring2_Value key
  )
{
  Ring2_Value value;
  Ring2_Value_setVoid(&value, Ring2_Void_Void);
  set(self, key, value);
}

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
Ring2_Array*
Machine_HashMap_getPairs
  (
    Machine_HashMap *self
  )
{
  Ring2_Array* a = Ring2_ArrayHeap_createArray(Ring2_Context_get(), self->size);
  int64_t j = 0;
  for (int64_t i = 0, n = self->capacity; i < n; ++i) {
    for (Node* node = self->buckets[i]; NULL != node; node = node->next) {
      Ring2_Array* e = Ring2_ArrayHeap_createArray(Ring2_Context_get(), 2);
      Ring2_Array_setElement(Ring2_Context_get(), e, 0, node->key);
      Ring2_Array_setElement(Ring2_Context_get(), e, 1, node->value);
      Ring2_Value v;
      Ring2_Value_setArray(&v, e);
      Ring2_Array_setElement(Ring2_Context_get(), a, j++, v);
    }
  }
  return a;
}
#endif
