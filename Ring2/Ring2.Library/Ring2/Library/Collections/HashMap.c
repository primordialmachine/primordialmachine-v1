// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/HashMap.c
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/HashMap.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/CollectionUtilities.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE
#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"
#include <assert.h>
#include <float.h>
#include <math.h>


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

struct Ring2_Collections_HashMap_Class {
  Machine_Object_Class _parent;
};

struct Ring2_Collections_HashMap {
  Machine_Object _parent;
  Node **buckets;
  int64_t size, capacity;
};


/// @brief The minimal capacity.
static int64_t const MINIMAL_CAPACITY = 8;

/// @brief The maximal capacity.
static int64_t const MAXIMAL_CAPACITY = (INT64_MAX < SIZE_MAX ? INT64_MAX : SIZE_MAX) / sizeof(Node*);


static Ring2_Boolean
defaultEqual
  (
    Ring2_Value const* x,
    Ring2_Value const* y
  );

static void
maybeResize
  (
    Ring2_Collections_HashMap *self
  );

// Ring2.Collections.Collection
static void
clear
  (
    Ring2_Collections_HashMap* self
  );

// Ring2.Collections.Collection
static int64_t
getSize
  (
    Ring2_Collections_HashMap const* self
  );

// Ring2.Collections.Collection
static bool
isEmpty
  (
    Ring2_Collections_HashMap const* self
  );

// Ring2.Collections.Map
static Ring2_Value
get
  (
    Ring2_Collections_HashMap const* self,
    Ring2_Value key
  );

// Ring2.Collections.Map
static void
_remove
  (
    Ring2_Collections_HashMap* self,
    Ring2_Value key
  );

// Ring2.Collections.Map
static void
set
  (
    Ring2_Collections_HashMap* self,
    Ring2_Value key,
    Ring2_Value value
  );

static Ring2_Collections_List*
toList
  (
    Ring2_Collections_HashMap const* self
  );

static void
implement_Ring2_Collections_Collection
  (
    Ring2_Collections_Collection_Dispatch* self
  );

static void
implement_Ring2_Collections_Map
  (
    Ring2_Collections_Map_Dispatch* self
  );

static void
implementInterfaces
  (
    Machine_ClassType* self
  );

static void
Ring2_Collections_HashMap_destruct
  (
    Ring2_Collections_HashMap* self
  );

static void
Ring2_Collections_HashMap_visit
  (
    Ring2_Collections_HashMap* self
  );

MACHINE_DEFINE_CLASSTYPE(Ring2_Collections_HashMap /*type*/,
                         Machine_Object /*parentType*/,
                         &Ring2_Collections_HashMap_visit /*visit*/,
                         &Ring2_Collections_HashMap_construct /*construct*/,
                         &Ring2_Collections_HashMap_destruct /*destruct*/,
                         NULL /*constructClass*/,
                         &implementInterfaces /*implementInterfaces*/)

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

static void
maybeResize
  ( 
    Ring2_Collections_HashMap *self
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
    if (Ring1_Memory_allocateArray((void **) & newBuckets, (size_t)newCapacity, sizeof(Node *))) {
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

// Ring2.Collections.Collection
static void
clear
  (
    Ring2_Collections_HashMap* self
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

// Ring2.Collections.Collection
static int64_t
getSize
  (
    Ring2_Collections_HashMap const* self
  )
{ return self->size; }

// Ring2.Collections.Collection
static bool
isEmpty
  (
    Ring2_Collections_HashMap const* self
  )
{ return 0 == self->size; }

// Ring2.Collections.Map
static Ring2_Value
get
  (
    Ring2_Collections_HashMap const* self,
    Ring2_Value key
  )
{
  if (Ring2_Value_isVoid(&key)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  } else if (Ring2_Value_isReal32(&key)) {
    if (isnan(Ring2_Value_getReal32(&key))) {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();   
    }
  } else if (Ring2_Value_isReal64(&key)) {
    if (isnan(Ring2_Value_getReal64(&key))) {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();  
    }
  }

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

// Ring2.Collections.Map
static void
_remove
  (
    Ring2_Collections_HashMap* self,
    Ring2_Value key
  )
{
  if (Ring2_Value_isVoid(&key)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  } else if (Ring2_Value_isReal32(&key)) {
    if (isnan(Ring2_Value_getReal32(&key))) {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();   
    }
  } else if (Ring2_Value_isReal64(&key)) {
    if (isnan(Ring2_Value_getReal64(&key))) {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();  
    }
  }

  int64_t hashValue = Ring2_Value_getHashValue(Ring2_Context_get(), &key);
  int64_t hashIndex = hashValue % self->capacity;
  Node** previous = &self->buckets[hashIndex];
  Node* current = self->buckets[hashIndex];
  while (current != NULL) {
    if (current->hashValue == hashValue &&
        Ring2_Value_isEqualTo(Ring2_Context_get(), &key, &current->key)) {
      *previous = current->next;
      Ring1_Memory_deallocate(current);
      self->size--;
      maybeResize(self);
      break;
    }
  }
}

// Ring2.Collections.Map
static void
set
  (
    Ring2_Collections_HashMap* self,
    Ring2_Value key,
    Ring2_Value value
  )
{
  if (Ring2_Value_isVoid(&value)) {
    _remove(self, key);
    return;
  }

  if (Ring2_Value_isVoid(&key)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  } else if (Ring2_Value_isReal32(&key)) {
    if (isnan(Ring2_Value_getReal32(&key))) {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();   
    }
  } else if (Ring2_Value_isReal64(&key)) {
    if (isnan(Ring2_Value_getReal64(&key))) {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();  
    }
  }
  
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
      Ring1_Log_error("unable to allocate node");
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

static Ring2_Collections_List*
toList
  (
    Ring2_Collections_HashMap const* self
  )
{ 
  Ring2_Collections_List* list = (Ring2_Collections_List*)Ring2_Collections_ArrayList_create();
  for (int64_t i = 0, n = self->capacity; i < n; ++i) {
    for (Node* node = self->buckets[i]; NULL != node; node = node->next) {
      Ring2_Collections_Pair* pair = Ring2_Collections_Pair_create(node->key, node->value);
      Ring2_Value temporary;
      Ring2_Value_setObject(&temporary, (Machine_Object *)pair);
      Ring2_Collections_List_append(list, temporary);
    }
  }
  return list;
}

static void
implement_Ring2_Collections_Collection
  (
    Ring2_Collections_Collection_Dispatch* self
  )
{
  self->clear = (void (*)(Ring2_Collections_Collection*)) & clear;
  self->getSize = (int64_t(*)(Ring2_Collections_Collection const*)) & getSize;
  self->isEmpty = (bool (*)(Ring2_Collections_Collection const*)) & isEmpty;
}

static void
implement_Ring2_Collections_Map
  (
    Ring2_Collections_Map_Dispatch* self
  )
{
  self->get = (Ring2_Value (*)(Ring2_Collections_Map const*, Ring2_Value)) & get;
  self->remove = (void (*)(Ring2_Collections_Map*, Ring2_Value)) & _remove;
  self->set = (void (*)(Ring2_Collections_Map*, Ring2_Value, Ring2_Value)) & set;
  self->toList = (Ring2_Collections_List * (*)(Ring2_Collections_Map const*)) & toList;
}

static void
implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement(self, Ring2_Collections_Collection_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Ring2_Collections_Collection);
  Machine_ClassType_implement(self, Ring2_Collections_Map_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Ring2_Collections_Map);
}

static void
Ring2_Collections_HashMap_destruct
  (
    Ring2_Collections_HashMap* self
  )
{
  clear(self);
  if (self->buckets) {
    Ring1_Memory_deallocate(self->buckets);
    self->buckets = NULL;
  }
}

static void
Ring2_Collections_HashMap_visit
  (
    Ring2_Collections_HashMap* self
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
Ring2_Collections_HashMap_construct
  (
    Ring2_Collections_HashMap *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->size = 0;
  self->capacity = 8;
  self->buckets = NULL;
  if (Ring1_Memory_allocateArray((void **)&self->buckets, (size_t)self->capacity, sizeof(Node*))) {
    Ring1_Log_error("unable to allocate buckets");
    Ring2_jump();
  }
  Ring1_Memory_zeroFillArray(self->buckets, (size_t)self->capacity, sizeof(Node*));
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring2_Collections_HashMap_getType());
}

Ring2_Collections_HashMap *
Ring2_Collections_HashMap_create
  (
  )
{
  Machine_Type* ty = Ring2_Collections_HashMap_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Collections_HashMap* self = Ring1_cast(Ring2_Collections_HashMap*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray

Ring2_Array*
Ring2_Collections_HashMap_getPairs
  (
    Ring2_Collections_HashMap *self
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
