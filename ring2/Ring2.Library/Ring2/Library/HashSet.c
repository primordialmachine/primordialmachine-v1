// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/HashSet.c
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/HashSet.h"
#undef RING2_LIBRARY_PRIVATE


#include "Ring1/Memory.h"
#include <assert.h>
#include <stdio.h>


typedef struct Node Node;
struct Node {
  /// @brief The node which was moved out of place because of this node.
  Node* next;
  /// @brief The value.
  Ring2_Value value;
  /// @brief The hash value. Cached from Mkx_Interpreter_Value_hashValue(context, &key).
  int64_t hashValue;
};

struct Machine_HashSet_Class {
  Machine_Object_Class _parent;
};

struct Machine_HashSet {
  Machine_Object _parent;
  Node **buckets;
  int64_t size, capacity;
};

static void
Machine_HashSet_destruct
  (
    Machine_HashSet* self
  );

static void
Machine_HashSet_visit
  (
    Machine_HashSet* self
  );

MACHINE_DEFINE_CLASSTYPE(Machine_HashSet /*type*/,
                         Machine_Object /*parentType*/,
                         &Machine_HashSet_visit /*visit*/,
                         &Machine_HashSet_construct /*construct*/,
                         &Machine_HashSet_destruct /*destruct*/,
                         NULL /*constructClass*/,
                         NULL)

static void
clear
  (
    Machine_HashSet* self
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

static void
Machine_HashSet_destruct
  (
    Machine_HashSet* self
  )
{
  clear(self);
  if (self->buckets) {
    Ring1_Memory_deallocate(self->buckets);
    self->buckets = NULL;
  }
}

static void
Machine_HashSet_visit
  (
    Machine_HashSet* self
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
Machine_HashSet_construct
  (
    Machine_HashSet *self,
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
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Machine_HashSet_getType());
}

Machine_HashSet *
Machine_HashSet_create
  (
  )
{
  Machine_ClassType* ty = Machine_HashSet_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  Ring2_Value ARGUMENTS[1] = { Ring2_Value_StaticInitializerVoid() };
  Machine_HashSet* self = (Machine_HashSet*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void
Machine_HashSet_add
  (
    Machine_HashSet* self,
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
      fprintf(stderr, "unable to allocate node");
      Ring2_jump();
    }
    node->next = self->buckets[hashIndex]; self->buckets[hashIndex] = node;
    self->size++;
  }
  node->value = value;
  node->hashValue = hashValue;
}

Ring2_Value
Machine_HashSet_get
  (
    Machine_HashSet* self,
    Ring2_Value value
  )
{
  int64_t hashValue = Ring2_Value_getHashValue(Ring2_Context_get(), &value);
  int64_t hashIndex = hashValue % self->capacity;
  for (Node* node = self->buckets[hashIndex]; NULL != node; node = node->next) {
    if (node->hashValue == hashValue && Ring2_Value_isEqualTo(Ring2_Context_get(), &value, &node->value))
    { return node->value; }
  }
  Ring2_Value result;
  Ring2_Value_setVoid(&result, Ring2_Void_Void);
  return result;
}

void
Machine_HashSet_remove
  (
    Machine_HashSet* self,
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

void
Machine_HashSet_clear
  (
    Machine_HashSet* self
  )
{ clear(self); }

int64_t
Machine_HashSet_getSize
  (
    Machine_HashSet* self
  )
{ return self->size; }

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
Ring2_Array*
Machine__HashSet_getEntries
  (
    Machine_HashSet* self
  )
{ 
  Ring2_Array* a = Ring2_ArrayHeap_createArray(Ring2_Context_get(), self->size);
  for (int64_t i = 0, j = 0, n = self->capacity; i < n; ++i) {
    Node* node = self->buckets[i];
    while (node) {
      Ring2_Array_setElement(Ring2_Context_get(), a, j, node->value);
      node = node->next;
      ++j;
    }
  }
  return a;
}
#endif
