// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/HashSet.c
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/HashSet.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/CollectionUtilities.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE
#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"
#include <assert.h>
#include <float.h>
#include <math.h>


typedef struct Node Node;
struct Node {
  /// @brief The node which was moved out of place because of this node.
  Node* next;
  /// @brief The value.
  Ring2_Value value;
  /// @brief The hash value. Cached from Mkx_Interpreter_Value_hashValue(context, &key).
  int64_t hashValue;
};

struct Ring2_Collections_HashSet_Class {
  Machine_Object_Class _parent;
};

struct Ring2_Collections_HashSet {
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

// Ring2.Collections.Collection
static void
clear
  (
    Ring2_Collections_HashSet* self
  );

// Ring2.Collections.Collection
static int64_t
getSize
  (
    Ring2_Collections_HashSet const* self
  );

// Ring2.Collections.Collection
static bool
isEmpty
  (
    Ring2_Collections_HashSet const* self
  );

// Ring2.Collections.Set
static void
add
  (
    Ring2_Collections_HashSet* self,
    Ring2_Value value
  );

// Ring2.Collections.Set
static bool
contains
  (
    Ring2_Collections_HashSet const* self,
    Ring2_Value value
  );

// Ring2.Collections.Set
static void
_remove
  (
    Ring2_Collections_HashSet* self,
    Ring2_Value value
  );

// Ring2.Collections.Set
static Ring2_Collections_List*
toList
  (
    Ring2_Collections_HashSet const* self
  );

static void
implement_Ring2_Collections_Collection
  (
    Ring2_Collections_Collection_Dispatch* self
  );

static void
implement_Ring2_Collections_Set
  (
    Ring2_Collections_Set_Dispatch* self
  );

static void
implementInterfaces
  (
    Machine_ClassType* self
  );

static void
Ring2_Collections_HashSet_destruct
  (
    Ring2_Collections_HashSet* self
  );

static void
Ring2_Collections_HashSet_visit
  (
    Ring2_Collections_HashSet* self
  );

MACHINE_DEFINE_CLASSTYPE(Ring2_Collections_HashSet /*type*/,
                         Machine_Object /*parentType*/,
                         &Ring2_Collections_HashSet_visit /*visit*/,
                         &Ring2_Collections_HashSet_construct /*construct*/,
                         &Ring2_Collections_HashSet_destruct /*destruct*/,
                         NULL /*constructClass*/,
                         &implementInterfaces /*implementInterfaces*/)

// Ring2.Collections.Collection
static void
clear
  (
    Ring2_Collections_HashSet* self
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
    Ring2_Collections_HashSet const* self
  )
{ return self->size; }

// Ring2.Collections.Collection
static bool
isEmpty
  (
    Ring2_Collections_HashSet const* self
  )
{ return 0 == self->size; }

// Ring2.Collections.Set
static void
add
  (
    Ring2_Collections_HashSet* self,
    Ring2_Value value
  )
{
  if (Ring2_Value_isVoid(&value))
  { return; }
  int64_t hashValue = Ring2_Value_getHashValue(Ring2_Context_get(), &value);
  int64_t hashIndex = hashValue % self->capacity;
  Node* node;
  for (node = self->buckets[hashIndex]; NULL != node; node = node->next) {
    if (node->hashValue == hashValue && Ring2_Value_isEqualTo(Ring2_Context_get(), &value, &node->value)) {
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
  node->value = value;
  node->hashValue = hashValue;
}

// Ring2.Collections.Set
static bool
contains
  (
    Ring2_Collections_HashSet const* self,
    Ring2_Value value
  )
{
  int64_t hashValue = Ring2_Value_getHashValue(Ring2_Context_get(), &value);
  int64_t hashIndex = hashValue % self->capacity;
  for (Node* node = self->buckets[hashIndex]; NULL != node; node = node->next) {
    if (node->hashValue == hashValue && Ring2_Value_isEqualTo(Ring2_Context_get(), &value, &node->value))
    { return true; }
  }
  return false;
}

// Ring2.Collections.Set
static void
_remove
  (
    Ring2_Collections_HashSet* self,
    Ring2_Value value
  )
{
  if (Ring2_Value_isVoid(&value))
  { return; }
  Ring2_Integer hashValue = Ring2_Value_getHashValue(Ring2_Context_get(), &value);
  Ring2_Integer hashIndex = hashValue % self->capacity;
  Node** previous = &self->buckets[hashIndex], *current = self->buckets[hashIndex];
  while (current) {
    if (current->hashValue == hashValue && Ring2_Value_isEqualTo(Ring2_Context_get(), &value, &current->value)) {
      Node* node = current;
      *previous = current->next;
      current = current->next;
      Ring1_Memory_deallocate(node);
      self->size--;
      break;
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
}

// Ring2.Collections.Set
static Ring2_Collections_List*
toList
  (
    Ring2_Collections_HashSet const* self
  )
{ 
  Ring2_Collections_List* list = (Ring2_Collections_List*)Ring2_Collections_ArrayList_create();
  for (int64_t i = 0, n = self->capacity; i < n; ++i) {
    for (Node* node = self->buckets[i]; NULL != node; node = node->next) {
      Ring2_Collections_List_append(list, node->value);
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
implement_Ring2_Collections_Set
  (
    Ring2_Collections_Set_Dispatch* self
  )
{ 
  self->add = (void (*)(Ring2_Collections_Set*, Ring2_Value)) & add;
  self->contains = (bool (*)(Ring2_Collections_Set const*, Ring2_Value)) & contains;
  self->remove = (void (*)(Ring2_Collections_Set*, Ring2_Value)) & _remove;
  self->toList = (Ring2_Collections_List *(*)(Ring2_Collections_Set const*)) & toList;
}

static void
implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement(self, Ring2_Collections_Collection_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Ring2_Collections_Collection);
  Machine_ClassType_implement(self, Ring2_Collections_Set_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Ring2_Collections_Set);
}

static void
Ring2_Collections_HashSet_destruct
  (
    Ring2_Collections_HashSet* self
  )
{
  clear(self);
  if (self->buckets) {
    Ring1_Memory_deallocate(self->buckets);
    self->buckets = NULL;
  }
}

static void
Ring2_Collections_HashSet_visit
  (
    Ring2_Collections_HashSet* self
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
Ring2_Collections_HashSet_construct
  (
    Ring2_Collections_HashSet *self,
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
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring2_Collections_HashSet_getType());
}

Ring2_Collections_HashSet *
Ring2_Collections_HashSet_create
  (
  )
{
  Machine_Type* ty = Ring2_Collections_HashSet_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Collections_HashSet* self = Ring1_cast(Ring2_Collections_HashSet*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}

void
Ring2_Collections_HashSet_remove
  (
    Ring2_Collections_HashSet* self,
    Ring2_Value value
  )
{
  if (Ring2_Value_isVoid(&value))
  { return; }
  Ring2_Integer hashValue = Ring2_Value_getHashValue(Ring2_Context_get(), &value);
  Ring2_Integer hashIndex = hashValue % self->capacity;
  Node** previous = &self->buckets[hashIndex], *current = self->buckets[hashIndex];
  while (current) {
    if (current->hashValue == hashValue && Ring2_Value_isEqualTo(Ring2_Context_get(), &value, &current->value)) {
      Node* node = current;
      *previous = current->next;
      current = current->next;
      Ring1_Memory_deallocate(node);
      self->size--;
      break;
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
}
