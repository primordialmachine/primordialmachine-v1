#if !defined(RING1_CONVERSION__BUFFER_H_INCLUDED)
#define RING1_CONVERSION__BUFFER_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include <stddef.h>

/// @private
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @remarks
/// Never fails.
/// @warning
/// Undefined if the "Conversion._Buffer" module is not yet initialized.
Ring1_Result
Ring1_Conversion__Buffer_shutdown
  (
  );

/// @private
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @warning
/// Undefined if the "Conversion._Buffer" module is already initialized.
Ring1_CheckReturn() Ring1_Result
Ring1_Conversion__Buffer_startup
  (
  );

/// @private
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @warning
/// Undefined if the "Conversion._Buffer" module is not yet initialized.
Ring1_CheckReturn() Ring1_Result
Ring1_Conversion__Buffer_get
  (
    char **result,
    size_t requiredSize
  );

#endif // RING1_CONVERSION__BUFFER_H_INCLUDED
