// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Module.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Module.h"

void
Ring1_Module_lock
  (
    Ring1_Module *module
  )
{ Ring1_ReadWriteLock_acquireWriteLock(&module->lock); }

void
Ring1_Module_unlock
  (
    Ring1_Module *module
  )
{ Ring1_ReadWriteLock_relinquishWriteLock(&module->lock); }

bool
Ring1_Module_isInitialized
  (
    Ring1_Module *module
  )
{ return Ring1_ReferenceCounter_get(&module->referenceCount) > 0; }

Ring1_ModuleHandle
Ring1_Module_acquireHandle
  (
    Ring1_Module *module
  )
{
   Ring1_Module_lock(module);
   if (!Ring1_Module_isInitialized(module))
   {
      if (module->initialize())
      {
        Ring1_Module_unlock(module);
        return Ring1_ModuleHandle_Invalid;
      }
    }
    Ring1_ReferenceCounter_increment(&module->referenceCount);
    Ring1_Module_unlock(module);
    return (Ring1_ModuleHandle)1;
}

void
Ring1_Module_relinquishHandle
  (
    Ring1_Module *module,
    Ring1_ModuleHandle module_handle
  )
{
  Ring1_Module_lock(module);
  if (!Ring1_ReferenceCounter_decrement(&module->referenceCount))
  {
    // TODO: We can use double checking locking here as
    // reference counter decrement shall prevent COMPILER and CPU from reordering the expressions.
    module->uninitialize();
  }
  Ring1_Module_unlock(module);
}
