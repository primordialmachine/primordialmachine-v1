#if !defined(RING1_AP_APNAT_PRIVATE_H_INCLUDED)
#define RING1_AP_APNAT_PRIVATE_H_INCLUDED


#if !defined(RING1_AP_PRIVATE) || 1 != RING1_AP_PRIVATE
#error("Do not include `Ring1/Ap/ApNat.h` directly. Include `Ring1/_Include.h` instead.")
#endif


#include "Ring1/Ap/ApNat.h"
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include <inttypes.h>


/// @brief Set the number of digits of an ApNat.
/// @detail
/// If the number of digits increases to K >= N,
///  then K - N zeroes are appended to the emd.
/// If the number of digits decreases to K <= N,
///  then N - K numbers are trimmed from the end.
/// @param x The ApNat.
/// @param numberOfDigitsadditional The new number of digits. Must be greater than @a 0.
/// @return #Ring_Result_Success on success. #Ring_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
resize
  (
    Ring1_ApNat* x,
    size_t newNumberOfDigits
  );

/// @brief Increase the number of digits of an ApNat. 
/// @param x The ApNat.-
/// @param additional The additional number of digits.
/// @return #Ring_Result_Success on success. #Ring_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
grow
  (
    Ring1_ApNat* x,
    size_t additionalNumberOfDigits
  );


#endif // RING1_AP_APNAT_PRIVATE_H_INCLUDED
