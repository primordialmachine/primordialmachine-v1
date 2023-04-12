// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Closure.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Closure.h"


#include "Ring1/Memory/_Include.h"
#include "Ring1/ReferenceCounter.h"
#include "Ring1/Status.h"

Ring1_BeginDependencies()
  Ring1_Dependency(Ring1, Memory)
Ring1_EndDependencies()

static Ring1_Result
initializeModule
  (
  )
{ return startupDependencies(); }

static void
uninitializeModule
  (
  )
{ shutdownDependencies(); }

Ring1_Module_Define(Ring1, Closure, initializeModule, uninitializeModule)

struct Mkx_Closure {
  Ring1_ReferenceCounter referenceCount;
  Mkx_Closure_Context* context;
  Mkx_Closure_Callback* callback;
  Mkx_Closure_Notify* notify;
};

static Mkx_Closure *
allocate
  (
  )
{
  Mkx_Closure* p;
  if (Ring1_Memory_allocate(&p, sizeof(Mkx_Closure))) {
    return NULL;
  }
  return p;
}

static void
deallocate
  (
    Mkx_Closure* closure
  )
{ Ring1_Memory_deallocate(closure); }

Ring1_CheckReturn() int
Mkx_Closure_create
  (
    Mkx_Closure** result,
    Mkx_Closure_Context* context,
    Mkx_Closure_Callback* callback,
    Mkx_Closure_Notify* notify
  )
{
  if (Ring1_Unlikely(!result || !callback)) return Ring1_Status_InvalidArgument;
  Mkx_Closure* closure = allocate();
  if (Ring1_Unlikely(!closure)) return Ring1_Status_AllocationFailed;
  closure->referenceCount = 1;
  closure->context = context;
  closure->callback = callback;
  closure->notify = notify;
  *result = closure;
  return Ring1_Status_Success;
}

Ring1_CheckReturn() int
Mkx_Closure_invoke
  (
    Mkx_Closure* closure,
    Mkx_Closure_Argument* argument
  )
{
  if (Ring1_Unlikely(!closure)) return Ring1_Status_InvalidArgument;
  return closure->callback(closure->context, argument);
}

void
Mkx_Closure_reference
  (
    Mkx_Closure* self
  )
{ Ring1_ReferenceCounter_increment(&self->referenceCount); }

void
Mkx_Closure_unreference
  ( 
    Mkx_Closure* self
  )
{
  if (!Ring1_ReferenceCounter_decrement(&self->referenceCount))
  {
    deallocate(self);
  }
}