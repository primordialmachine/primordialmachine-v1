#include "./../../Collections/Test/Test1.h"



#include "_Collections.h"
#include <string.h>



static void test_1_1() {
  Machine_List* list = Machine_List_create();
}

static void test_1_2() {
  Machine_Map* map = Machine_Map_create();
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
