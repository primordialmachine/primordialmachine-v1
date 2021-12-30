#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Machine.h"






#include "Runtime/Gc/Gc.h"
#include "Runtime/JumpTargetModule.h"
#include "Runtime/LogModule.h"
#include "Runtime/StackModule.h"
#include "Runtime/StaticVariablesModule.h"
#include <stdio.h>



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



static const struct {
  Machine_StatusValue(*initialize)();
  void (*uninitialize)();
} MODULES[] = {
  { &Machine_initializeLogModule, &Machine_uninitializeLogModule },
  { &Machine_initializeJumpTargetModule, &Machine_uninitializeJumpTargetModule },
  { &Machine_initializeGcModule, &Machine_uninitializeGcModule },
  { &Machine_initializeStackModule, &Machine_uninitializeStackModule },
  { &Machine_initializeStaticVariablesModule, &Machine_uninitializeStaticVariablesModule },
};
static const size_t NUMBER_OF_MODULES = 4;

Machine_StatusValue Machine_startup() {
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_update() {
  size_t live, dead;
  Machine_Gc_run(&live, &dead);
}

void Machine_shutdown() {
  size_t MAX_RUN = 8;
  size_t live = 0, dead = 0, run = 0;
  
  do {
    size_t newLive, newDead;
    Machine_Gc_run(&newLive, &newDead);
    if (newLive > 0 && newDead == 0) {
      fprintf(stderr, "gc not making progress\n");
      break;
    }
    dead = newDead;
    live = newLive;
    run++;
  } while (live > 0 && run < MAX_RUN);

  Machine_notifyStaticVariablesUninitialize();

  do {
    size_t newLive, newDead;
    Machine_Gc_run(&newLive, &newDead);
    if (newLive > 0 && newDead == 0) {
      fprintf(stderr, "gc not making progress\n");
      break;
    }
    dead = newDead;
    live = newLive;
    run++;
  } while (live > 0 && run < MAX_RUN);

  if (live > 0) {
    fprintf(stderr, "warning %zu live objects remaining\n", live);
  }

  for (size_t i = NUMBER_OF_MODULES; i > 0; --i) {
    MODULES[i-1].uninitialize();
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
