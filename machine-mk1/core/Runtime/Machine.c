#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Machine.h"

#include "Runtime/Gc/Gc.h"
#include "Ring2/_Include.h"
#include "Runtime/LogModule.h"
#include "Runtime/StackModule.h"
#include "Runtime/StaticVariablesModule.h"
#include "Ring1/Time.h"
#include "Ring1/Status.h"
#include <stdio.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Ring2_Gc_PreMarkCallbackId stringModulePreMarkCallbackId = Ring2_Gc_PreMarkCallbackId_Invalid;
static Ring2_Gc_SweepCallbackId stringModuleSweepCallbackId = Ring2_Gc_SweepCallbackId_Invalid;

static Ring1_Result registerStringModule() {
  stringModulePreMarkCallbackId = Ring2_Gc_addPreMarkCallback(Ring2_Gc_get(), NULL, &Ring2_StringModule_preMarkCallback);
  if (stringModulePreMarkCallbackId == Ring2_Gc_PreMarkCallbackId_Invalid) {
    return Ring1_Result_Failure;
  }
  stringModuleSweepCallbackId = Ring2_Gc_addSweepCallback(Ring2_Gc_get(), NULL, &Ring2_StringModule_sweepCallback);
  if (stringModuleSweepCallbackId == Ring2_Gc_SweepCallbackId_Invalid) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

static void unregisterStringModule() {
  Ring2_Gc_removeSweepCallback(Ring2_Gc_get(), stringModuleSweepCallbackId);
  stringModuleSweepCallbackId = Ring2_Gc_SweepCallbackId_Invalid;
  Ring2_Gc_removePreMarkCallback(Ring2_Gc_get(), stringModulePreMarkCallbackId);
  stringModulePreMarkCallbackId = Ring2_Gc_PreMarkCallbackId_Invalid;
}

static const struct {
  Ring1_Result (*initialize)();
  void (*uninitialize)();
} MODULES[] = {
  { &Machine_initializeLogModule, &Machine_uninitializeLogModule },
  { &Ring2_Context_startup, &Ring2_Context_shutdown },
  { &Machine_Gc_startup, &Machine_Gc_shutdown },
  { &Ring2_StringModule_startup, &Ring2_StringModule_shutdown },
  { &registerStringModule, &unregisterStringModule },
  { &Machine_initializeStackModule, &Machine_uninitializeStackModule },
  { &Machine_initializeStaticVariablesModule, &Machine_uninitializeStaticVariablesModule },
};
static size_t const NUMBER_OF_MODULES = 7;

static Ring1_Result startupModules() {
  for (size_t i = 0, n = NUMBER_OF_MODULES; i < n; ++i) {
    if (MODULES[i].initialize()) {
      while (i > 0) {
        MODULES[i - 1].uninitialize();
        i--;
      }
      return Ring1_Result_Failure;
    }
  }
  return Ring1_Result_Success;
}

static void shutdownModules() {
  for (size_t i = NUMBER_OF_MODULES; i > 0; --i) {
    MODULES[i - 1].uninitialize();
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Ring1_Time_ModuleHandle g_timeModuleHandle = Ring1_Time_ModuleHandle_Invalid;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_Result Machine_startup() {
  g_timeModuleHandle = Ring1_Time_ModuleHandle_acquire();
  if (!g_timeModuleHandle) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  if (startupModules()) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
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
