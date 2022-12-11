// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Intrinsic/Test/Multiply.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_INTRINSIC_TEST_MULTIPLY_H_INCLUDED)
#define MKX_INTRINSIC_TEST_MULTIPLY_H_INCLUDED

#include "Ring1/Test.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_registerMultiplyTests
  (
    Ring1_Test_Context* ctx
  );

#endif // MKX_INTRINSIC_TEST_MULTIPLY_H_INCLUDED
