#define RING1_AP_PRIVATE (1)
#include "Ring1/Ap/_Include.h"
#undef RING1_AP_PRIVATE

static Ring1_NoDiscardReturn() Ring1_Result
initialize
  (
  );

static void
uninitialize
  (
  );

Ring1_Module_Define(Ring1, Ap, initialize, uninitialize)

static Ring1_NoDiscardReturn() Ring1_Result
initialize
  (
  )
{ return Ring1_Result_Success; }

static void
uninitialize
  (
  )
{}
