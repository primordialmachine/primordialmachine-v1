#if !defined(RING1_AP_APBOOL_H_INCLUDED)
#define RING1_AP_APBOOL_H_INCLUDED


#if !defined(RING1_AP_PRIVATE) || 1 != RING1_AP_PRIVATE
#error("Do not include `Ring1/Ap/ApInt.h` directly. Include `Ring1/_Include.h` instead.")
#endif


#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include <stdbool.h>


typedef struct Ring1_ApBool {
  bool value;
} Ring1_ApBool;

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApBool_print
  (
    Ring1_ApBool *self
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApBool_initialize_bool
  (
    Ring1_ApBool* self,
    bool value
  );

Ring1_Result
Ring1_ApBool_uninitialize
  (
    Ring1_ApBool *self
  );

/// @brief Assign the values of another ApBool to this ApBool.
/// @param self This ApBool.
/// @param other The other ApBool.
/// @return #Ring_Result_Success on success. #Ring_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApBool_assign
  (
    Ring1_ApBool* self,
    Ring1_ApBool* other
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApBool_toBool
  (
    bool *result,
    Ring1_ApBool* self
  );


#endif // RING1_AP_APBOOL_H_INCLUDED
