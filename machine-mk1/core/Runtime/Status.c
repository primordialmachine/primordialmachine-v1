#include "Runtime/Status.h"

static Machine_StatusValue g_status = Machine_Status_Success;

Machine_StatusValue Machine_getStatus() {
  return g_status;
}

void Machine_setStatus(Machine_StatusValue status) {
  g_status = status;
}
