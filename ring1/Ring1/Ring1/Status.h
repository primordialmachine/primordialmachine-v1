// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Status.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_STATUS_H_INCLUDED)
#define RING1_STATUS_H_INCLUDED

#include "Ring1/Intrinsic/CheckReturn.h"

// https://documentation.primordialmachine.com/ring1-library/status-library/Ring1_Status
typedef int Ring1_Status;

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_Success (0)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_ArgumentOutOfRange (1)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidArgument (2)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_AllocationFailed (3)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_CollectionFull (4)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_CollectionEmpty (5)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidOperation (6)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_NotInitialized (7)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_Initialized (8)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_AlreadyExists (10)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_NotExists (11)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_DivisionByZero (12)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_NumericOverflow (13)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_EnvironmentFailed (14)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidLexics (15)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidSyntactics (16)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidSemantics (17)

// https://documentation.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidEnvironment (18)

// https://documentation.primordialmachine.com/ring1-library/status-library/Ring1_Status_get
Ring1_CheckReturn() Ring1_Status
Ring1_Status_get
  (
  );

// https://documentation.primordialmachine.com/ring1-library/status-library/Ring1_Status_set
void
Ring1_Status_set
  (
    Ring1_Status status
  );

#endif // RING1_STATUS_H_INCLUDED
