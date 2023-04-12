#if !defined(RING1_AP_APREAL_H_INCLUDED)
#define RING1_AP_APREAL_H_INCLUDED


#if !defined(RING1_AP_PRIVATE) || 1 != RING1_AP_PRIVATE
#error("Do not include `Ring1/Ap/ApReal.h` directly. Include `Ring1/_Include.h` instead.")
#endif


#include "Ring1/Ap/ApInt.h"


/// An ApNat represents a real number.
/// An ApNat consists of
/// - an ApInt <code>integer</code> and
/// - an integer value <code>exponent</code>
/// such that the real number is given by <code>integer * 2^exponent</code>.
typedef struct Ring1_ApReal {
  
  /// @brief An integer <code>significant</code>.
  Ring1_ApInt integer;
  
  /// @brief An exponent <code>2^exponent</code>.
  int64_t exponent;

} Ring1_ApReal;

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_print
  (
    Ring1_ApReal* self
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_u8
  (
    Ring1_ApReal* self,
    int64_t exponent,
    uint8_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_u16
  (
    Ring1_ApReal* self,
    int64_t exponent,
    uint16_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_u32
  (
    Ring1_ApReal* self,
    int64_t exponent,
    uint32_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_u64
  (
    Ring1_ApReal* self,
    int64_t exponent,
    uint64_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_s8
  (
    Ring1_ApReal* self,
    int64_t exponent,
    int8_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_s16
  (
    Ring1_ApReal* self,
    int64_t exponent,
    int16_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_s32
  (
    Ring1_ApReal* self,
    int64_t exponent,
    int32_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_s64
  (
    Ring1_ApReal* self,
    int64_t exponent,
    int64_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_f32
  (
    Ring1_ApReal* self,
    float value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_f64
  (
    Ring1_ApReal* self,
    double value
  );

Ring1_Result
Ring1_ApReal_uninitialize
  (
    Ring1_ApReal* self
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_set
  (
    Ring1_ApReal* self,
    Ring1_ApInt *integer,
    int64_t exponent
  );

#endif // RING1_AP_APREAL_H_INCLUDED
