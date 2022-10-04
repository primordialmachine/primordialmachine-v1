/// @file Collections/Test/ListTest.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(MACHINE_COLLECTIONS_TEST_ARRAYLISTTEST_H_INCLUDED)
#define MACHINE_COLLECTIONS_TEST_ARRAYLISTTEST_H_INCLUDED


#include "Ring1/Test.h"
#include "Ring2/_Include.h"


/// @brief Register the tests for the array list data structure with the test list.
/// @param tests The test list.
void
Ring2_Test_registerArrayListTests
  (
    Ring2_Tests *tests
  );


#endif // MACHINE_COLLECTIONS_TEST_ARRAYLISTTEST_H_INCLUDED
