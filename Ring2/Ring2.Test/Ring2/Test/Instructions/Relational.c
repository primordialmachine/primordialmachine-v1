// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Instructions/Relational.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Test/Instructions/Relational.h"

#include "Ring2/Test/Instructions/Relational/EqualTo.h"
#include "Ring2/Test/Instructions/Relational/NotEqualTo.h"
#include "Ring2/Test/Instructions/Relational/LowerThan.h"
#include "Ring2/Test/Instructions/Relational/LowerThanOrEqualTo.h"
#include "Ring2/Test/Instructions/Relational/GreaterThan.h"
#include "Ring2/Test/Instructions/Relational/GreaterThanOrEqualTo.h"

#include "Ring1/All/_Include.h"

void
Ring2_Test_Instructions_registerRelationalTests
  (
    Ring2_Tests* tests
  )
{
  Ring2_String* prefix = Ring2_String_create("Ring2.Test.Instructions.Relational.",
                                  crt_strlen("Ring2.Test.Instructions.Relational."));

  {
    Ring2_Tests_addTest(tests,
                        Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                 Ring2_String_create("equalTo",
                                                          crt_strlen("equalTo"))),
                        &Ring2_Test_Instructions_Relational_testEqualTo);
    Ring2_Tests_addTest(tests,
                        Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                 Ring2_String_create("notEqualTo",
                                                          crt_strlen("notEqualTo"))),
                        &Ring2_Test_Instructions_Relational_testNotEqualTo);
    Ring2_Tests_addTest(tests,
                        Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                 Ring2_String_create("lowerThan",
                                                          crt_strlen("lowerThan"))),
                        &Ring2_Test_Instructions_Relational_testLowerThan);
    Ring2_Tests_addTest(tests,
                        Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                 Ring2_String_create("lowerThanOrEqualTo",
                                                          crt_strlen("lowerThanOrEqualTo"))),
                        &Ring2_Test_Instructions_Relational_testLowerThanOrEqualTo);
    Ring2_Tests_addTest(tests,
                        Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                 Ring2_String_create("greaterThan",
                                                          crt_strlen("greaterThan"))),
                        &Ring2_Test_Instructions_Relational_testGreaterThan);
    Ring2_Tests_addTest(tests,
                        Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                 Ring2_String_create("greaterThanOrEqualTo",
                                                          crt_strlen("greaterThanOrEqualTo"))),
                        &Ring2_Test_Instructions_Relational_testGreaterThanOrEqualTo);
  }
}
