// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Gc/Implementation/Gc1.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
/// @brief A precise, non-incremental, mark-and-sweep GC.

#define RING2_PRIVATE (1)
#include "Ring2/Gc/Implementation/Gc1.h"
#undef RING2_PRIVATE

#include "Ring2/Gc/Tag.h"
#include "Ring1/Memory.h"
#include <assert.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct PreMarkCallbackNode PreMarkCallbackNode;
struct PreMarkCallbackNode
{
  PreMarkCallbackNode* next;
  void* object;
  Ring2_Gc_PreMarkCallback* callback;
};


typedef struct SweepCallbackNode SweepCallbackNode;
struct SweepCallbackNode
{
  SweepCallbackNode *next;
  void* object;
  Ring2_Gc_SweepCallback *callback;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct Ring2_Gc_Implementation_Gc1
{
  Ring1_Memory_ModuleHandle memoryModuleHandle;
  Ring2_Gc_Tag* objectList;
  Ring2_Gc_Tag* grayList;
  SweepCallbackNode *sweepCallbacks;
  PreMarkCallbackNode* preMarkCallbacks;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring2_Gc_SweepCallbackId
Ring2_Gc_Implementation_Gc1_addPreMarkCallback
  (
    Ring2_Gc_Implementation_Gc1* gc,
    void* object,
    Ring2_Gc_PreMarkCallback* callback
  )
{
  PreMarkCallbackNode* node;
  if (Ring1_Memory_allocate(&node, sizeof(PreMarkCallbackNode))) return Ring2_Gc_PreMarkCallbackId_Invalid;
  node->object = object;
  node->callback = callback;
  node->next = gc->preMarkCallbacks;
  gc->preMarkCallbacks = node;
  return (uintptr_t)node;
}

void
Ring2_Gc_Implementation_Gc1_removePreMarkCallback
  (
    Ring2_Gc_Implementation_Gc1* gc,
    Ring2_Gc_PreMarkCallbackId id
  )
{
  PreMarkCallbackNode** previous = &gc->preMarkCallbacks, * current = gc->preMarkCallbacks;
  while (current)
  {
    if ((uintptr_t)current == id)
    {
      *previous = current->next;
      Ring1_Memory_deallocate(current);
      break;
    }
    else
    {
      previous = &current->next;
      current = current->next;
    }
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring2_Gc_SweepCallbackId
Ring2_Gc_Implementation_Gc1_addSweepCallback
  (
    Ring2_Gc_Implementation_Gc1* gc,
    void* object,
    Ring2_Gc_SweepCallback* callback
  )
{
  SweepCallbackNode* node;
  if (Ring1_Memory_allocate(&node, sizeof(SweepCallbackNode))) {
    return Ring2_Gc_SweepCallbackId_Invalid;
  }
  node->object = object;
  node->callback = callback;
  node->next = gc->sweepCallbacks;
  gc->sweepCallbacks = node;
  return (uintptr_t)node;
}

void
Ring2_Gc_Implementation_Gc1_removeSweepCallback
  (
    Ring2_Gc_Implementation_Gc1* gc,
    Ring2_Gc_SweepCallbackId id
  )
{
  SweepCallbackNode **previous = &gc->sweepCallbacks, *current = gc->sweepCallbacks;
  while (current)
  {
    if ((uintptr_t)current == id)
    {
      *previous = current->next;
      Ring1_Memory_deallocate(current);
      break;
    }
    else
    {
      previous = &current->next;
      current = current->next;
    }
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring2_Gc_Implementation_Gc1 *
Ring2_Gc_Implementation_Gc1_create
  (
  )
{
  Ring1_Memory_ModuleHandle handle = Ring1_Memory_ModuleHandle_acquire();
  if (!handle)
  {
    return NULL;
  }
  Ring2_Gc_Implementation_Gc1* gc;
  if (Ring1_Memory_allocate(&gc, sizeof(Ring2_Gc_Implementation_Gc1)))
  {
    Ring1_Memory_ModuleHandle_relinquish(handle);
    return NULL;
  }
  gc->memoryModuleHandle = handle;
  gc->sweepCallbacks = NULL;
  gc->preMarkCallbacks = NULL;
  gc->objectList = NULL;
  gc->grayList = NULL;
  return gc;
}

void
Ring2_Gc_Implementation_Gc1_destroy
  (
    Ring2_Gc_Implementation_Gc1 *gc
  )
{
  while (gc->preMarkCallbacks)
  {
    PreMarkCallbackNode* node = gc->preMarkCallbacks;
    gc->preMarkCallbacks = node->next;
    Ring1_Memory_deallocate(node);
  }
  while (gc->sweepCallbacks)
  {
    SweepCallbackNode *node = gc->sweepCallbacks;
    gc->sweepCallbacks = node->next;
    Ring1_Memory_deallocate(node);
  }
  Ring1_Memory_ModuleHandle handle = gc->memoryModuleHandle;
  Ring1_Memory_deallocate(gc);
  Ring1_Memory_ModuleHandle_relinquish(handle);
}

void*
Ring2_Gc_Implementation_Gc1_allocate
  (
    Ring2_Gc_Implementation_Gc1* gc,
    size_t size,
    Ring2_Gc_Type const* type,
    Ring2_Gc_Tag **objectList
  )
{
  if (!type)
  {
    return NULL;
  }
  if (Ring2_Gc_MaximumAllocatableSize < size)
  {
    return NULL;
  }
  Ring2_Gc_Tag* object;
  if (Ring1_Memory_allocate(&object, sizeof(Ring2_Gc_Tag) + size))
  {
    return NULL;
  }
  Ring1_Memory_zeroFill(object, sizeof(Ring2_Gc_Tag) + size);
  Ring2_Gc_Tag_setWhite(object);
  object->type = type;
  object->objectNext = *objectList;
  *objectList = object;
  return (void *)(object + 1);
}

void
Ring2_Gc_Implementation_Gc1_run
  (
    Ring2_Gc_Implementation_Gc1* gc,
    Ring2_Gc_RunStatistics *statistics
  )
{
  // PreMark phase.
  for (PreMarkCallbackNode* node = gc->preMarkCallbacks; NULL != node; node = node->next)
  {
    node->callback(gc, node->object);
  }
  // Mark phase.
  while (gc->grayList) {
    assert(gc->grayList != NULL);
    // Pop the object from the stack.
    Ring2_Gc_Tag* tag = gc->grayList;
    gc->grayList = tag->grayNext;

    if (Ring2_Gc_Tag_isGray(tag)) {
      // We invoke the "mark" function (if any).
      // The "mark" function invokes "Ring2_Gc_visit" on objects referred to by the marked object.
      if (tag->type) {
        if (tag->type->visit) {
          tag->type->visit(gc, Ring2_Gc_toAddress(tag));
        }
      }
      Ring2_Gc_Tag_setBlack(tag);
    }
  }
  // Sweep phase.
  if (statistics)
  {
    statistics->sweep.dead = 0;
    statistics->sweep.live = 0;
  }
  for (SweepCallbackNode* node = gc->sweepCallbacks; NULL != node; node = node->next)
  {
    Ring2_Gc_SweepStatistics localStatistics;
    node->callback(gc, node->object, &localStatistics);
    if (statistics)
    {
      statistics->sweep.dead += localStatistics.dead;
      statistics->sweep.live += localStatistics.live;
    }
  }
}

Ring2_Gc_Tag*
Ring2_Gc_Implementation_Gc1_toTag
  (
    void* x
  )
{
  return ((Ring2_Gc_Tag*)x) - 1;
}

void*
Ring2_Gc_Implementation_Gc1_toAddress
  (
    Ring2_Gc_Tag* x
  )
{
  return (void *)(x + 1);
}

void
Ring2_Gc_Implementation_Gc1_visit
  (
    Ring2_Gc_Implementation_Gc1* gc,
    void* address
  )
{
  if (!address) {
    return;
  }
  Ring2_Gc_Tag* tag = Ring2_Gc_toTag(address);
  if (Ring2_Gc_Tag_isWhite(tag)) {
    Ring2_Gc_Tag_setGray(tag);
    tag->grayNext = gc->grayList;
    gc->grayList = tag;
  }
}
