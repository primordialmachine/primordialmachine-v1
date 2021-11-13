/// @file Collections/Test/PairTest.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Collections/Test/PairTest.h"



#include "_Collections.h"
#include "_Atf.h"
#include <string.h>



void Machine_Collections_Test_PairTest_test1() {
  Machine_Value first = { Machine_ValueFlag_Void, Machine_Void_Void },
    second = { Machine_ValueFlag_Void, Machine_Void_Void };
  Machine_Value_setVoid(&first, Machine_Void_Void);
  Machine_Value_setVoid(&first, Machine_Void_Void);
  Machine_Pair* pair = Machine_Pair_create(first, second);
}
