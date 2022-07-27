/// @file Collections/Test/ArrayDequeTest.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Collections/Test/ArrayDequeTest.h"

#include "_Atf.h"
#include "_Collections.h"

void Machine_Collections_Test_ArrayDequeTest_test1() {
  Ring2_String* NAME
      = Machine_String_create("Machine.Collections.Test.ArrayDequeTest.test1",
                              crt_strlen("Machine.Collections.Test.ArrayDequeTest.test1"));

  Machine_Deque* deque = (Machine_Deque *)Machine_ArrayDeque_create();
  Machine_Collection_getSize((Machine_Collection*)deque);
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)deque));
  Machine_Collection_clear((Machine_Collection*)deque);
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)deque));
}

void Machine_Collections_Test_ArrayDequeTest_test2() {
  Ring2_String* NAME
      = Machine_String_create("Machine.Collections.Test.ArrayDequeTest.test2",
                              crt_strlen("Machine.Collections.Test.ArrayDequeTest.test2"));

  Machine_Deque* deque = (Machine_Deque *)Machine_ArrayDeque_create();
  Machine_Value value;

  static size_t const N = 3;

  for (size_t i = 0, n = N; i < n; ++i) {
    Machine_Value_setInteger(&value, i);
    Machine_Deque_pushFront(deque, value);
  }
  MACHINE_ATF_ASSERT(N == Machine_Collection_getSize((Machine_Collection*)deque));
  for (size_t i = 0, n = N; i < n; ++i) {
    Machine_Value received = Machine_Deque_popBack(deque);
    Machine_Value expected;
    Machine_Value_setInteger(&expected, i);
    MACHINE_ATF_ASSERT(Machine_Value_isEqualTo(&received, &expected));
  }
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)deque));
}

void Machine_Collections_Test_ArrayDequeTest_test3() {
  Ring2_String* NAME
      = Machine_String_create("Machine.Collections.Test.ArrayDequeTest.test3",
                              crt_strlen("Machine.Collections.Test.ArrayDequeTest.test3"));
  Machine_Deque* deque = (Machine_Deque *)Machine_ArrayDeque_create();
  Machine_Value value;

  size_t k = 0;
  // Push 8 items.
  for (size_t i = 0, n = 8; i < n; ++i) {
    Machine_Value_setInteger(&value, k++);
    Machine_Deque_pushFront(deque, value);
  }
  MACHINE_ATF_ASSERT(8 == Machine_Collection_getSize((Machine_Collection*)deque));
  // Pop 5 items.
  for (size_t i = 0, n = 5; i < n; ++i) {
    static const Ring2_Integer C[] = { 7, 6, 5, 4, 3 };
    Machine_Value received = Machine_Deque_popFront(deque);
    Machine_Value expected;
    Machine_Value_setInteger(&expected, C[i]);
    MACHINE_ATF_ASSERT(Machine_Value_isEqualTo(&received, &expected));
  }
  MACHINE_ATF_ASSERT(3 == Machine_Collection_getSize((Machine_Collection*)deque));
  // Push 5 items.
  for (size_t i = 0, n = 5; i < n; ++i) {
    Machine_Value_setInteger(&value, k++);
    Machine_Deque_pushFront(deque, value);
  }
  MACHINE_ATF_ASSERT(8 == Machine_Collection_getSize((Machine_Collection*)deque));
  // Pop 5 items.
  for (size_t i = 0, n = 5; i < n; ++i) {
    static const Ring2_Integer C[] = { 12, 11, 10, 9, 8 };
    Machine_Value received = Machine_Deque_popFront(deque);
    Machine_Value expected;
    Machine_Value_setInteger(&expected, C[i]);
    MACHINE_ATF_ASSERT(Machine_Value_isEqualTo(&received, &expected));
  }
  MACHINE_ATF_ASSERT(3 == Machine_Collection_getSize((Machine_Collection*)deque));
  for (size_t i = 0, n = 3; i < n; ++i) {
    static const Ring2_Integer C[] = { 2, 1, 0 };
    Machine_Value received = Machine_Deque_popFront(deque);
    Machine_Value expected;
    Machine_Value_setInteger(&expected, C[i]);
    MACHINE_ATF_ASSERT(Machine_Value_isEqualTo(&received, &expected));
  }
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)deque));
}
