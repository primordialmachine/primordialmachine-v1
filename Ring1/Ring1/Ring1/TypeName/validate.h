#if !defined(RING1_TYPENAME_VALIDATE_H_INCLUDED)
#define RING1_TYPENAME_VALIDATE_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include "Ring1/Module.h"

/// @brief Assert a specified string denotes a valid scalar type name.
/// @param p A pointer to the string.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @remark This function sets the by-thread status variable on failure.
/// @error #Ring1_Status_InvalidSyntactics the string does not represent a valid scalar type name.
Ring1_CheckReturn() Ring1_Result
isScalarTypeName
  (
    const char *p
  );

#endif // RING1_TYPENAME_VALIDATE_H_INCLUDED
