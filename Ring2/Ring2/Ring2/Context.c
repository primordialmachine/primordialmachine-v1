// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Context.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Context.h"
#undef RING2_PRIVATE

#include "Ring1/All/_Include.h"
#include "Ring1/Log.h"
#include "Ring1/Status.h"

#define RING2_PRIVATE (1)
#include "Ring2/JumpTarget.h"
#include "Ring2/Log.h"
#include "Ring2/Operations.h"
#include "Ring2/Stack.h"
#include "Ring2/StaticVariables.h"
#include "Ring2/TypeSystem.h"
#undef RING2_PRIVATE

static Ring2_Context* g_context = NULL;

struct Ring2_Context {
  Ring1_Memory_ModuleHandle memoryModule;
};

Ring1_CheckReturn() Ring2_Context*
Ring2_Context_get
  (
  )
{
  return g_context;
}

Ring1_BeginDependencies()
  Ring1_Dependency(Ring1, All)
  //
  Ring1_Dependency(Ring2, LogModule)
  Ring1_Dependency(Ring2, GcModule)
  Ring1_Dependency(Ring2, JumpTargetModule)
  //
  Ring1_Dependency(Ring2, TypeSystemModule)
  //
  Ring1_Dependency(Ring2, TypesModule)
  Ring1_Dependency(Ring2, OperationsModule)
Ring1_EndDependencies()

static Ring2_StaticVariablesModule_ModuleHandle g_staticVariablesModuleHandle = Ring2_StaticVariablesModule_ModuleHandle_Invalid;
static Ring2_StackModule_ModuleHandle g_stackModuleHandle = Ring2_StackModule_ModuleHandle_Invalid;

Ring1_CheckReturn() Ring1_Result
Ring2_Context_startup
  (
  )
{
  if (!g_context) {
    if (startupDependencies()) {
      return Ring1_Result_Failure;
    }
    g_staticVariablesModuleHandle = Ring2_StaticVariablesModule_ModuleHandle_acquire();
    if (!g_staticVariablesModuleHandle) {
      shutdownDependencies();
      return Ring1_Result_Failure;
    }
    g_stackModuleHandle = Ring2_StackModule_ModuleHandle_acquire();
    if (!g_stackModuleHandle) {
      Ring2_notifyStaticVariablesUninitialize();

      Ring2_StaticVariablesModule_ModuleHandle_relinquish(g_staticVariablesModuleHandle);
      g_staticVariablesModuleHandle = Ring2_StaticVariablesModule_ModuleHandle_Invalid;

      shutdownDependencies();
      return Ring1_Result_Failure;
    }
    if (Ring1_Memory_allocate(&g_context, sizeof(Ring2_Context))) {
      Ring2_StackModule_ModuleHandle_relinquish(g_stackModuleHandle);
      g_stackModuleHandle = Ring2_StaticVariablesModule_ModuleHandle_Invalid;
      
      Ring2_StaticVariablesModule_ModuleHandle_relinquish(g_staticVariablesModuleHandle);
      g_staticVariablesModuleHandle = Ring2_StaticVariablesModule_ModuleHandle_Invalid;
      
      shutdownDependencies();
      return Ring1_Result_Failure;
    }
  }
  return Ring1_Result_Success;
}

static void
runGc
  (
    int64_t n
  )
{
  uint64_t i = 0;
  Ring2_Gc_RunStatistics oldStatistics;
  Ring2_Gc_run(Ring2_Gc_get(), &oldStatistics);
  do {
    Ring2_Gc_RunStatistics newStatistics;
    Ring2_Gc_run(Ring2_Gc_get(), &newStatistics);
    if (0 == newStatistics.sweep.live) {
      break;
    } else if (newStatistics.sweep.live == oldStatistics.sweep.live) {
      i++;
      if (i == n) {
        Ring1_Log_warning("%"PRIu64" live objects since %"PRIu64" iterations - retrying", newStatistics.sweep.live, i);
        break;
      } else {
        Ring1_Log_warning("%"PRIu64" live objects since %"PRIu64" iterations - aborting", newStatistics.sweep.live, i);
      }
    }
    oldStatistics = newStatistics;
  } while (true);
}

void
Ring2_Context_shutdown
  (
  )
{
  if (g_context) {
    // Clear the stack.
    // TODO: This should not be necessary once the call stack is implemented unless there is a stack corruption.
    Mkx_Interpreter_Stack_clear(g_context);
    // Iterate the GC until the number of live objects does not change anymore.
    runGc(4);
    // Iterate the GC until the number of live objects does not change anymore.
    runGc(4);
    //
    Ring2_StackModule_ModuleHandle_relinquish(g_stackModuleHandle);
    g_stackModuleHandle = Ring2_StackModule_ModuleHandle_Invalid;
    //
    Ring2_notifyStaticVariablesUninitialize();
    //
    Ring2_StaticVariablesModule_ModuleHandle_relinquish(g_staticVariablesModuleHandle);
    g_staticVariablesModuleHandle = Ring2_StaticVariablesModule_ModuleHandle_Invalid;
    // Iterate the GC until the number of live objects does not change anymore.
    runGc(4);
    //
    Ring1_Memory_deallocate(g_context);
    g_context = NULL;
    //
    shutdownDependencies();
  }
}
