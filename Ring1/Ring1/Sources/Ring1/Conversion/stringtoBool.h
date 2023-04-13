// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Conversion/stringToBool.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CONVERSION_STRINGTOBOOL_H_INCLUDED)
#define RING1_CONVERSION_STRINGTOBOOL_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include <stdbool.h>

/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @success <code>*result</code> was assigned the <code>bool</code> value.
/// @failure <code>result</code> was not dereferenced.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Conversion_stringToBool
  (
    bool *result,
    char const* start,
    char const* end
  );

#endif // RING1_CONVERSION_STRINGTOBOOL_H_INCLUDED
