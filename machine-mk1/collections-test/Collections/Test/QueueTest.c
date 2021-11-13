/// @file Collections/Test/QueueTest.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Collections/Test/QueueTest.h"



#include "_Atf.h"
#include "_Collections.h"



void Machine_Collections_Test_QueueTest_test1() {
  Machine_String* NAME = Machine_String_create("Machine.Collections.Test.QueueTests.test1", c_strzt_length("Machine.Collections.Test.QueueTests.test1"));

  Machine_Queue* queue = Machine_Queue_create();
  Machine_Collection_getSize((Machine_Collection*)queue);
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)queue));
  Machine_Collection_clear((Machine_Collection*)queue);
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)queue));
}

void Machine_Collections_Test_QueueTest_test2() {
  Machine_String* NAME = Machine_String_create("Machine.Collections.Test.QueueTests.test2", c_strzt_length("Machine.Collections.Test.QueueTests.test2"));

  Machine_Queue* queue = Machine_Queue_create();
  Machine_Value value;

  static const size_t N = 3;

  for (size_t i = 0, n = N; i < n; ++i) {
    Machine_Value_setInteger(&value, i);
    Machine_Queue_pushFront(queue, value);
  }
  MACHINE_ATF_ASSERT(N == Machine_Collection_getSize((Machine_Collection*)queue));
  for (size_t i = 0, n = N; i < n; ++i) {
    Machine_Value received = Machine_Queue_popBack(queue);
    Machine_Value expected;
    Machine_Value_setInteger(&expected, i);
    MACHINE_ATF_ASSERT(Machine_Value_isEqualTo(&received, &expected));
  }
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)queue));
}

void Machine_Collections_Test_QueueTest_test3() {
  Machine_String* NAME = Machine_String_create("Machine.Collections.Test.QueueTests.test3", c_strzt_length("Machine.Collections.Test.QueueTests.test3"));
  Machine_Queue* queue = Machine_Queue_create();
  Machine_Value value;

  size_t k = 0;
  // Push 8 items.
  for (size_t i = 0, n = 8; i < n; ++i) {
    Machine_Value_setInteger(&value, k++);
    Machine_Queue_pushFront(queue, value);
  }
  MACHINE_ATF_ASSERT(8 == Machine_Collection_getSize((Machine_Collection*)queue));
  // Pop 5 items.
  for (size_t i = 0, n = 5; i < n; ++i) {
    static const Machine_Integer C[] = { 7, 6, 5, 4, 3 };
    Machine_Value received = Machine_Queue_popFront(queue);
    Machine_Value expected;
    Machine_Value_setInteger(&expected, C[i]);
    MACHINE_ATF_ASSERT(Machine_Value_isEqualTo(&received, &expected));
  }
  MACHINE_ATF_ASSERT(3 == Machine_Collection_getSize((Machine_Collection*)queue));
  // Push 5 items.
  for (size_t i = 0, n = 5; i < n; ++i) {
    Machine_Value_setInteger(&value, k++);
    Machine_Queue_pushFront(queue, value);
  }
  MACHINE_ATF_ASSERT(8 == Machine_Collection_getSize((Machine_Collection*)queue));
  // Pop 5 items.
  for (size_t i = 0, n = 5; i < n; ++i) {
    static const Machine_Integer C[] = { 12, 11, 10, 9, 8 };
    Machine_Value received = Machine_Queue_popFront(queue);
    Machine_Value expected;
    Machine_Value_setInteger(&expected, C[i]);
    MACHINE_ATF_ASSERT(Machine_Value_isEqualTo(&received, &expected));
  }
  MACHINE_ATF_ASSERT(3 == Machine_Collection_getSize((Machine_Collection*)queue));
  for (size_t i = 0, n = 3; i < n; ++i) {
    static const Machine_Integer C[] = { 2, 1, 0 };
    Machine_Value received = Machine_Queue_popFront(queue);
    Machine_Value expected;
    Machine_Value_setInteger(&expected, C[i]);
    MACHINE_ATF_ASSERT(Machine_Value_isEqualTo(&received, &expected));
  }
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)queue));
}
