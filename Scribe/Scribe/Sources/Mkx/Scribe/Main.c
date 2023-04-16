#include "Mkx/Scribe/SafeExecute.h"
#include <stdlib.h>

int
main
  (
    int argc,
    char** argv
  )
{
  Ring1_Result result;
  if (result = Ring2_Context_startup()) {
    return EXIT_FAILURE;
  }
  if (Scribe_safeExecute(Ring2_Context_get(), argc, argv)) { 
    Ring2_Context_shutdown();
    return EXIT_FAILURE;
  }
  Ring2_Context_shutdown();
  return EXIT_SUCCESS;
}
