#if !defined(RING2_OPERATIONS__BUFFER_H_INCLUDED)
#define RING2_OPERATIONS__BUFFER_H_INCLUDED


#include "Ring2/_header.h.i"
#include <stddef.h>


/// @private
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @remarks
/// Never fails.
/// @warning
/// Undefined if the "Ring2.Operations._Buffer" module is not yet initialized.
Ring1_Result
Ring2_Operations__Buffer_shutdown
  (
  );

/// @private
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @warning
/// Undefined if the "Ring2.Operations._Buffer" module is already initialized.
Ring1_CheckReturn() Ring1_Result
Ring2_Operations__Buffer_startup
  (
  );

/// @private
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @warning
/// Undefined if the "Ring2.Operations._Buffer" module is not yet initialized.
Ring1_CheckReturn() Ring1_Result
Ring2_Operations__Buffer_get
  (
    char **result,
    size_t requiredSize
  );

#endif // RING2_OPERATIONS__BUFFER_H_INCLUDED
