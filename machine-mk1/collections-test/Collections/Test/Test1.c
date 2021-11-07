#include "./../../Collections/Test/Test1.h"
#include "_Collections.h"
#include "_Atf.h"
#include <string.h>



static void test_1_1() {
  Machine_List* list = Machine_List_create();
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)list));
  Machine_Collection_clear((Machine_Collection*)list);
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)list));
}

static void test_1_2() {
  Machine_Map* map = Machine_Map_create();
  Machine_Collection_getSize((Machine_Collection*)map);
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)map));
  Machine_Collection_clear((Machine_Collection*)map);
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)map));
}

static void test_1_3() {
  Machine_Value first = { Machine_ValueFlag_Void, Machine_Void_Void }, 
                second = { Machine_ValueFlag_Void, Machine_Void_Void };
  Machine_Value_setVoid(&first, Machine_Void_Void);
  Machine_Value_setVoid(&first, Machine_Void_Void);
  Machine_Pair* pair = Machine_Pair_create(first, second);
}

void Machine_Collections_test1() {
  test_1_1();
  test_1_2();
  test_1_3();
}
