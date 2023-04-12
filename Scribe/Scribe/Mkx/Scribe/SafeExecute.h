#if !defined(MKX_SCRIBE_COMMON_MAIN_H_INCLUDED)
#define MKX_SCRIBE_COMMON_MAIN_H_INCLUDED

#include "Ring2/_Include.h"

Ring1_CheckReturn() int
Scribe_safeExecute
  (
    Ring2_Context* context,
    int numberOfArguments,
    const char** arguments
  );

#endif // MKX_SCRIBE_COMMON_MAIN_H_INCLUDED
