// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Instructions/Relational/GreaterThanOrEqualTo.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TEST_INSTRUCTIONS_RELATIONAL_GREATERTHANOREQUALTO_H_INCLUDED)
#define RING2_TEST_INSTRUCTIONS_RELATIONAL_GREATERTHANOREQUALTO_H_INCLUDED

#include "Ring2/Test/Common.h"

void
Ring2_Test_Instructions_Relational_testGreaterThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

#endif // RING2_TEST_INSTRUCTIONS_RELATIONAL_GREATERTHANOREQUALTO_H_INCLUDED
