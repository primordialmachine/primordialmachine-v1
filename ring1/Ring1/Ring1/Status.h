// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Status.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_STATUS_H_INCLUDED)
#define RING1_STATUS_H_INCLUDED

#include "Ring1/Intrinsic/CheckReturn.h"

// https://preview.primordialmachine.com/ring1-library/status-library/Ring1_Status
typedef int Ring1_Status;

// https://preview.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_Success (0)

// https://preview.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_ArgumentOutOfRange (1)

// https://preview.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidArgument (2)

// https://preview.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_AllocationFailed (3)

// https://preview.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_CollectionFull (4)

// https://preview.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_CollectionEmpty (5)

// https://preview.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidOperation (6)

// https://preview.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_NotInitialized (7)

// https://preview.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_Initialized (8)

// https://preview.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_AlreadyExists (10)

// https://preview.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_NotExists (11)

// https://preview.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_DivisionByZero (12)

// https://preview.primordialmachine.com/ring1-library/status-library/status-codes
#define Ring1_Status_NumericOverflow (15)

// https://preview.primordialmachine.com/ring1-library/status-library/Ring1_Status_get
Ring1_CheckReturn() Ring1_Status
Ring1_Status_get
  (
  );

// https://preview.primordialmachine.com/ring1-library/status-library/Ring1_Status_set
void
Ring1_Status_set
  (
    Ring1_Status status
  );

#endif // RING1_STATUS_H_INCLUDED
