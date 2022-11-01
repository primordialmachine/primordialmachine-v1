// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Context.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Context.h"
#undef RING2_PRIVATE


#include <stdio.h>
#include "Ring1/Memory.h"
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
  Ring1_Dependency(Ring1, Memory)
  //
  Ring1_Dependency(Ring2, LogModule)
  Ring1_Dependency(Ring2, GcModule)
  Ring1_Dependency(Ring2, JumpTargetModule)
  //
  Ring1_Dependency(Ring2, TypeSystemModule)
  //
  Ring1_Dependency(Ring2, TypesModule)
  Ring1_Dependency(Ring2, OperationsModule)
  //
  Ring1_Dependency(Ring2, StaticVariablesModule)
  //
  Ring1_Dependency(Ring2, StackModule)
Ring1_EndDependencies()

Ring1_CheckReturn() Ring1_Result
Ring2_Context_startup
  (
  )
{
  if (!g_context) {
    if (startupDependencies()) {
      return Ring1_Result_Failure;
    }
    if (Ring1_Memory_allocate(&g_context, sizeof(Ring2_Context))) {
      shutdownDependencies();
      return Ring1_Result_Failure;
    }
  }
  return Ring1_Result_Success;
}

static void
runGc
  (
    Ring2_Context* context,
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
        fprintf(stdout, "%"PRIu64" live objects since %"PRIu64" iterations - retrying", newStatistics.sweep.live, i);
      } else {
        fprintf(stdout, "%"PRIu64" live objects since %"PRIu64" iterations - aborting", newStatistics.sweep.live, i);
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
    runGc(g_context, 4);
    // Iterate the GC until the number of live objects does not change anymore.
    runGc(g_context, 4);
    //
    Ring1_Memory_deallocate(g_context);
    g_context = NULL;
    //
    shutdownDependencies();
  }
}
