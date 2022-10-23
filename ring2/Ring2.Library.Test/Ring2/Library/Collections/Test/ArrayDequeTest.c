/// @file Ring2/Library/Collections/Test/ArrayDequeTest.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Ring2/Library/Collections/Test/ArrayDequeTest.h"


#include "Ring2/_Include.h"
#include "Ring2/Library/_Include.h"


static void
test1
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

static void
test2
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

static void
test3
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

static void
test1
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Ring2_Collections_Deque* deque = (Ring2_Collections_Deque *)Ring2_Collections_ArrayDeque_create();
  Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)deque);
  RING2_TEST_ASSERT(0 == Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)deque));
  Ring2_Collections_Collection_clear((Ring2_Collections_Collection*)deque);
  RING2_TEST_ASSERT(0 == Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)deque));
}

static void
test2
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Ring2_Collections_Deque* deque = (Ring2_Collections_Deque *)Ring2_Collections_ArrayDeque_create();
  Ring2_Value value;

  static size_t const N = 3;

  for (size_t i = 0, n = N; i < n; ++i) {
    Ring2_Value_setInteger(&value, i);
    Ring2_Collections_Deque_pushFront(deque, value);
  }
  RING2_TEST_ASSERT(N == Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)deque));
  for (size_t i = 0, n = N; i < n; ++i) {
    Ring2_Value received = Ring2_Collections_Deque_popBack(deque);
    Ring2_Value expected;
    Ring2_Value_setInteger(&expected, i);
    RING2_TEST_ASSERT(Ring2_Value_isEqualTo(Ring2_Context_get(), &received, &expected));
  }
  RING2_TEST_ASSERT(0 == Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)deque));
}

static void
test3
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Ring2_Collections_Deque* deque = (Ring2_Collections_Deque *)Ring2_Collections_ArrayDeque_create();
  Ring2_Value value;

  size_t k = 0;
  // Push 8 items.
  for (size_t i = 0, n = 8; i < n; ++i) {
    Ring2_Value_setInteger(&value, k++);
    Ring2_Collections_Deque_pushFront(deque, value);
  }
  RING2_TEST_ASSERT(8 == Ring2_Collections_Collection_getSize((Ring2_Collections_Collection *)deque));
  // Pop 5 items.
  for (size_t i = 0, n = 5; i < n; ++i) {
    static const Ring2_Integer C[] = { 7, 6, 5, 4, 3 };
    Ring2_Value received = Ring2_Collections_Deque_popFront(deque);
    Ring2_Value expected;
    Ring2_Value_setInteger(&expected, C[i]);
    RING2_TEST_ASSERT(Ring2_Value_isEqualTo(Ring2_Context_get(), &received, &expected));
  }
  RING2_TEST_ASSERT(3 == Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)deque));
  // Push 5 items.
  for (size_t i = 0, n = 5; i < n; ++i) {
    Ring2_Value_setInteger(&value, k++);
    Ring2_Collections_Deque_pushFront(deque, value);
  }
  RING2_TEST_ASSERT(8 == Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)deque));
  // Pop 5 items.
  for (size_t i = 0, n = 5; i < n; ++i) {
    static const Ring2_Integer C[] = { 12, 11, 10, 9, 8 };
    Ring2_Value received = Ring2_Collections_Deque_popFront(deque);
    Ring2_Value expected;
    Ring2_Value_setInteger(&expected, C[i]);
    RING2_TEST_ASSERT(Ring2_Value_isEqualTo(Ring2_Context_get(), &received, &expected));
  }
  RING2_TEST_ASSERT(3 == Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)deque));
  for (size_t i = 0, n = 3; i < n; ++i) {
    static const Ring2_Integer C[] = { 2, 1, 0 };
    Ring2_Value received = Ring2_Collections_Deque_popFront(deque);
    Ring2_Value expected;
    Ring2_Value_setInteger(&expected, C[i]);
    RING2_TEST_ASSERT(Ring2_Value_isEqualTo(Ring2_Context_get(), &received, &expected));
  }
  RING2_TEST_ASSERT(0 == Ring2_Collections_Collection_getSize((Ring2_Collections_Collection *)deque));
}

void
Ring2_Test_registerArrayDequeTests
  (
    Ring2_Tests *tests
  )
{
  Ring2_String* prefix = Ring2_String_create(Ring2_Context_get(), "Ring2.Library.Collections.Test.ArrayDequeTest",
                                                       crt_strlen("Ring2.Library.Collections.Test.ArrayDequeTest"));
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create(Ring2_Context_get(), "1",
                                                                                                  crt_strlen("1"))),
                      &test1);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create(Ring2_Context_get(), "2",
                                                                                                  crt_strlen("2"))),
                      &test2);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create(Ring2_Context_get(), "3",
                                                                                                  crt_strlen("3"))),
                      &test3);
}
