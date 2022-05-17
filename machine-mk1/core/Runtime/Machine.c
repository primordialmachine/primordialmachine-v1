#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Machine.h"

#include "Runtime/Gc/Gc.h"
#include "Ring2/JumpTargetModule.h"
#include "Runtime/LogModule.h"
#include "Runtime/StackModule.h"
#include "Runtime/StaticVariablesModule.h"
#include "Ring1/Time.h"
#include <stdio.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const struct {
  Machine_StatusValue (*initialize)();
  void (*uninitialize)();
} MODULES[] = {
  { &Machine_initializeLogModule, &Machine_uninitializeLogModule },
  { &Ring2_JumpTargetModule_startup, &Ring2_JumpTargetModule_shutdown },
  { &Machine_initializeGcModule, &Machine_uninitializeGcModule },
  { &Machine_initializeStackModule, &Machine_uninitializeStackModule },
  { &Machine_initializeStaticVariablesModule, &Machine_uninitializeStaticVariablesModule },
};
static size_t const NUMBER_OF_MODULES = 5;

static Machine_StatusValue startupModules() {
  for (size_t i = 0, n = NUMBER_OF_MODULES; i < n; ++i) {
    Machine_StatusValue status = MODULES[i].initialize();
    if (status) {
      while (i > 0) {
        MODULES[i - 1].uninitialize();
        i--;
      }
      return status;
    }
  }
  return Machine_Status_Success;
}

static void shutdownModules() {
  for (size_t i = NUMBER_OF_MODULES; i > 0; --i) {
    MODULES[i - 1].uninitialize();
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Ring1_Time_ModuleHandle g_timeModuleHandle = Ring1_Time_ModuleHandle_Invalid;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Machine_StatusValue Machine_startup() {
  g_timeModuleHandle = Ring1_Time_ModuleHandle_acquire();
  if (!g_timeModuleHandle) {
    return Machine_Status_EnvironmentFailed;
  }
  Machine_StatusValue status = startupModules();
  if (status) {
    return status;
  }
  return Machine_Status_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_update() {
  Machine_Gc_run(NULL);
}

void Machine_shutdown() {
  static const size_t MAX_RUN = 8;
  Ring2_Gc_RunStatistics statistics = { .sweep.dead = 0, .sweep.live = 0 };
  size_t run = 0;

  do {
    Ring2_Gc_RunStatistics newStatistics;
    Machine_Gc_run(&newStatistics);
    if (newStatistics.sweep.live > 0 && newStatistics.sweep.dead == 0) {
      fprintf(stderr, "gc not making progress\n");
      break;
    }
    statistics = newStatistics;
    run++;
  } while (statistics.sweep.live > 0 && run < MAX_RUN);

  Machine_notifyStaticVariablesUninitialize();

  do {
    Ring2_Gc_RunStatistics newStatistics;
    Machine_Gc_run(&newStatistics);
    if (newStatistics.sweep.live > 0 && newStatistics.sweep.dead == 0) {
      fprintf(stderr, "gc not making progress\n");
      break;
    }
    statistics = newStatistics;
    run++;
  } while (statistics.sweep.live > 0 && run < MAX_RUN);

  if (statistics.sweep.live > 0) {
    fprintf(stderr, "warning %" PRId64 " live objects remaining\n", statistics.sweep.live);
  }

  shutdownModules();

  Ring1_Time_ModuleHandle_relinquish(g_timeModuleHandle);
  g_timeModuleHandle = Ring1_Time_ModuleHandle_Invalid;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
