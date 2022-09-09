/// @file Collections/Test/PairTest.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Collections/Test/PairTest.h"



#include "_Collections.h"
#include "_Atf.h"
#include <string.h>



void Machine_Collections_Test_PairTest_test1() {
  Ring2_Value first = { Ring2_Value_Tag_Void, Ring2_Void_Void },
              second = { Ring2_Value_Tag_Void, Ring2_Void_Void };
  Ring2_Value_setVoid(&first, Ring2_Void_Void);
  Ring2_Value_setVoid(&first, Ring2_Void_Void);
  Machine_Pair* pair = Machine_Pair_create(first, second);
}
