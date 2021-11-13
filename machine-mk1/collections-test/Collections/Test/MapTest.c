/// @file Collections/Test/MapTest.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Collections/Test/MapTest.h"



#include "_Atf.h"
#include "_Collections.h"



void Machine_Collections_Test_MapTest_test1() {
  Machine_Map* map = Machine_Map_create();
  Machine_Collection_getSize((Machine_Collection*)map);
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)map));
  Machine_Collection_clear((Machine_Collection*)map);
  MACHINE_ATF_ASSERT(0 == Machine_Collection_getSize((Machine_Collection*)map));
}
