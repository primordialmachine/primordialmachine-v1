// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Module.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_MODULE_H_INCLUDED)
#define RING1_MODULE_H_INCLUDED

#include "Ring1/Module/Configuration.h"
#include <stdbool.h>
#include "Ring1/ReferenceCounter.h"
#include "Ring1/Intrinsic/Concurrency/ReadWriteLock.h"
#include "Ring1/Result.h"

typedef struct Ring1_Module
{
  Ring1_ReferenceCounter referenceCount;
  Ring1_ReadWriteLock lock;
  Ring1_Result (*initialize)();
  void (*uninitialize)();
} Ring1_Module;

typedef int Ring1_ModuleHandle;

enum
{
  Ring1_ModuleHandle_Invalid = 0
};

void
Ring1_Module_lock(Ring1_Module* module);

void
Ring1_Module_unlock(Ring1_Module* module);

bool
Ring1_Module_isInitialized(Ring1_Module* module);

Ring1_ModuleHandle
Ring1_Module_acquireHandle(Ring1_Module* module);

void
Ring1_Module_relinquishHandle(Ring1_Module* module,
                              Ring1_ModuleHandle moduleHandle);

#define Ring1_Module_Declare(MODULE)                                           \
  typedef Ring1_ModuleHandle Ring1_##MODULE##_ModuleHandle;                    \
                                                                               \
  enum                                                                         \
  {                                                                            \
    Ring1_##MODULE##_ModuleHandle_Invalid                                      \
  };                                                                           \
                                                                               \
  Ring1_##MODULE##_ModuleHandle Ring1_##MODULE##_ModuleHandle_acquire();       \
                                                                               \
  void Ring1_##MODULE##_ModuleHandle_relinquish(                               \
    Ring1_##MODULE##_ModuleHandle moduleHandle);                               \
                                                                               \
  void Ring1_##MODULE##_Module_lock();                                         \
                                                                               \
  void Ring1_##MODULE##_Module_unlock();                                       \
                                                                               \
  bool Ring1_##MODULE##_Module_isInitialized();

/// @brief Macro which defines a module.
/// @param MODULE The name of the module.
/// @param INITIALIZE The name of the initialize function of the module.
/// @param UNINITIALIZE The name of the uninitialize function of the module.
#define Ring1_Module_Define(MODULE, INITIALIZE, UNINITIALIZE)                  \
  static Ring1_Module g_module = {                                             \
    .referenceCount = 0,                                                       \
    .lock = Ring1_ReadWriteLock_Initializer,                                   \
    .initialize = &INITIALIZE,                                                 \
    .uninitialize = &UNINITIALIZE,                                             \
  };                                                                           \
                                                                               \
  Ring1_##MODULE##_ModuleHandle Ring1_##MODULE##_ModuleHandle_acquire()        \
  {                                                                            \
    return Ring1_Module_acquireHandle(&g_module);                              \
  }                                                                            \
                                                                               \
  void Ring1_##MODULE##_ModuleHandle_relinquish(                               \
    Ring1_##MODULE##_ModuleHandle moduleHandle)                                \
  {                                                                            \
    Ring1_Module_relinquishHandle(&g_module, moduleHandle);                    \
  }                                                                            \
                                                                               \
  void Ring1_##MODULE##_Module_lock() { Ring1_Module_lock(&g_module); }        \
                                                                               \
  void Ring1_##MODULE##_Module_unlock() { Ring1_Module_unlock(&g_module); }    \
                                                                               \
  bool Ring1_##MODULE##_Module_isInitialized()                                 \
  {                                                                            \
    return Ring1_Module_isInitialized(&g_module);                              \
  }

#endif // RING1_MODULE_H_INCLUDED
