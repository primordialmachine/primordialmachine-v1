/// @file Collections/Test/ListTest.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Collections/Test/ListTest.h"



#include "_Atf.h"
#include "_Collections.h"



void Machine_Collections_Test_ListTest_test1() {
  Machine_List* list = Machine_List_create();
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)list));
  Machine_Collection_clear((Machine_Collection*)list);
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)list));
}
