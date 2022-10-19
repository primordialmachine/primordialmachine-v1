/// @file Ring2/Library/Collections/Test/HashMapTest.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(RING2_LIBRARY_COLLECTIONS_TEST_HASHMAPTEST_H_INCLUDED)
#define RING2_LIBRARY_COLLECTIONS_TEST_HASHMAPTEST_H_INCLUDED


#include "Ring1/Test.h"
#include "Ring2/_Include.h"


/// @brief Register the tests for the hash map data structure with the test list.
/// @param tests The test list.
void
Ring2_Test_registerHashMapTests
  (
    Ring2_Tests *tests
  );


#endif // RING2_LIBRARY_COLLECTIONS_TEST_HASHMAPTEST_H_INCLUDED
