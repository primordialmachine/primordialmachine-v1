// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Conversion/stringToUint.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CONVERSION_STRINGTOUINT_H_INCLUDED)
#define RING1_CONVERSION_STRINGTOUINT_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include <inttypes.h>

/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @success <code>*result</code> was assigned the <code>int64_t</code> value.
/// @failure <code>result</code> was not dereferenced.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Conversion_stringToUint64
  (
    uint64_t *result,
    char const* start,
    char const* end
  );
 
/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @success <code>*result</code> was assigned the <code>int32_t</code> value.
/// @failure <code>result</code> was not dereferenced. 
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Conversion_stringToUint32
  (
    uint32_t *result,
    char const* start,
    char const* end
  );

/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @success <code>*result</code> was assigned the <code>int16_t</code> value.
/// @failure <code>result</code> was not dereferenced.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Conversion_stringToUint16
  (
    uint16_t *result,
    char const* start,
    char const* end
  );

/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @success <code>*result</code> was assigned the <code>int8_t</code> value.
/// @failure <code>result</code> was not dereferenced.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Conversion_stringToUint8
  (
    uint8_t *result,
    char const* start,
    char const* end
  );

#endif // RING1_CONVERSION_STRINGTOUINT_H_INCLUDED
