// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Conversion/stringToVoid.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CONVERSION_STRINGTOFLOAT_H_INCLUDED)
#define RING1_CONVERSION_STRINGTOFLOAT_H_INCLUDED

#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring1/Result.h"

/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @success <code>*result</code> was assigned the <code>float</code> value.
/// @failure <code>result</code> was not dereferenced.
Ring1_Intrinsic_CheckReturn() Ring1_Result
Ring1_Conversion_stringToFloat
  (
    float *result,
    char const* start,
    char const* end
  );

/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @success <code>*result</code> was assigned the <code>double</code> value.
/// @failure <code>result</code> was not dereferenced.
Ring1_Intrinsic_CheckReturn() Ring1_Result
Ring1_Conversion_stringToDouble
  (
    double *result,
    char const* start,
    char const* end
  );

#endif // RING1_CONVERSION_STRINGTOFLOAT_H_INCLUDED
