// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Conversion/stringToInt.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CONVERSION_STRINGTOINT_H_INCLUDED)
#define RING1_CONVERSION_STRINGTOINT_H_INCLUDED

#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring1/Result.h"
#include <inttypes.h>

/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @success <code>*result</code> was assigned the <code>int64_t</code> value.
/// @failure <code>result</code> was not dereferenced.
Ring1_Intrinsic_CheckReturn() Ring1_Result
Ring1_Conversion_stringToInt64
  (
    int64_t *result,
    char const* start,
    char const* end
  );
 
/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @success <code>*result</code> was assigned the <code>int32_t</code> value.
/// @failure <code>result</code> was not dereferenced. 
Ring1_Intrinsic_CheckReturn() Ring1_Result
Ring1_Conversion_stringToInt32
  (
    int32_t *result,
    char const* start,
    char const* end
  );

/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @success <code>*result</code> was assigned the <code>int16_t</code> value.
/// @failure <code>result</code> was not dereferenced.
Ring1_Intrinsic_CheckReturn() Ring1_Result
Ring1_Conversion_stringToInt16
  (
    int16_t *result,
    char const* start,
    char const* end
  );

/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @success <code>*result</code> was assigned the <code>int8_t</code> value.
/// @failure <code>result</code> was not dereferenced.
Ring1_Intrinsic_CheckReturn() Ring1_Result
Ring1_Conversion_stringToInt8
  (
    int8_t *result,
    char const* start,
    char const* end
  );

#endif // RING1_CONVERSION_STRINGTOINT_H_INCLUDED
