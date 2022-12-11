#if !defined(RING1_TYPENAME__INCLUDE_H_INCLUDED)
#define RING1_TYPENAME__INCLUDE_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include "Ring1/Module.h"

Ring1_Module_Declare(Ring1, TypeName)

/// @brief The opaque representatino of a type name,
typedef struct Ring1_TypeName Ring1_TypeName;

void
Ring1_TypeName_ref
  (
    Ring1_TypeName* typeName
  );

void
Ring1_TypeName_unref
  (
    Ring1_TypeName *typeName
  );

/// @brief Get or create an array type.
/// @param result A pointer to a <code>Ring1_Type *</code> variable.
/// @param underlaying A pointer to the underlaying type.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @success
/// <code>*result</code> was assigned a pointer to Ring1_TypeName object representing the type name.
/// @error #Ring1_Status_TooLong the name of the type would be too long.
/// @error #Ring1_Status_InvalidArgument the dimensionality is smaller than or equal to 0.
/// @error #Ring1_Status_InvalidArgument the dimensionality is too big.
/// @error #Ring1_Status_AllocationFailed an allocation failed.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_TypeName_getOrCreateArray
  (
    Ring1_TypeName **result,
    int64_t dimensionality,
    Ring1_TypeName *underlaying
  );

/// @brief Get or create a scalar type.
/// @param result A pointer to a <code>Ring1_Type *</code> variable.
/// @param name A pointer to the name.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @success
/// <code>*result</code> was assigned a pointer to Ring1_TypeName object representing the type name.
/// @error #Ring1_Status_TooLong the name of the type would be too long.
/// @error #Ring1_Status_InvalidArgument the dimensionality is smaller than or equal to 0.
/// @error #Ring1_Status_InvalidArgument the dimensionality is too big.
/// @error #Ring1_Status_AllocationFailed an allocation failed.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_TypeName_getOrCreateScalar
  (
    Ring1_TypeName **result,
    const char *name
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_TypeName_toString
  (
    char **result,
    Ring1_TypeName *typeName
  );

#endif // RING1_TYPENAME__INCLUDE_H_INCLUDED
