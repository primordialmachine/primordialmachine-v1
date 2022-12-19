// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Status.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_STATUS_H_INCLUDED)
#define RING1_STATUS_H_INCLUDED

#include "Ring1/Annotations/_Include.h"

// https://primordialmachine.com/api/ring1-library/status-library/Ring1_Status
typedef int Ring1_Status;

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_Success (0)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_ArgumentOutOfRange (1)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidArgument (2)
#define Ring1_Status_InvalidOutput (1002)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_AllocationFailed (3)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_CollectionFull (4)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_CollectionEmpty (5)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidOperation (6)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_NotInitialized (7)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_Initialized (8)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_AlreadyExists (10)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_NotExists (11)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_DivisionByZero (12)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_NumericOverflow (13)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_EnvironmentFailed (14)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidLexics (15)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidSyntactics (16)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidSemantics (17)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidEnvironment (18)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_ConversionFailed (19)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidNumberOfArguments (20)

#define Ring1_Status_InvalidNumberOfOutputs (21)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_InvalidArgumentType (22)

#define Ring1_Status_InvalidOutputType (23)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_IndexOutOfBounds (24)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_IsEmpty (25)

// https://primordialmachine.com/api/ring1-library/status-library/status-codes
#define Ring1_Status_TestFailed (26)

/// @brief Symbolic constant for a status variable value.
/// That value indicates that something is not yet implemented.
#define Ring1_Status_NotYetImplemented (27)

/// @brief Symbolic constant for a status variable value.
/// That value indicates something is too long.
#define Ring1_Status_TooLong (28)

/// @brief Symbolic constant for a status variable value.
/// That value indicates something is too short.
#define Ring1_Status_TooShort (29)

/// @brief Symbolic constant for a status variable value.
/// The value indicates a program point was reached which should not be reached.
#define Ring1_Status_UnreachableProgramPointReached (30)

#define Ring1_Status_StackCorruption (31)

#define Ring1_Status_InternalError (32)

#define Ring1_Status_FileNotFound (33)

// https://primordialmachine.com/api/ring1-library/status-library/Ring1_Status_get
Ring1_NoDiscardReturn() Ring1_Status
Ring1_Status_get
  (
  );

// https://primordialmachine.com/api/ring1-library/status-library/Ring1_Status_set
void
Ring1_Status_set
  (
    Ring1_Status status
  );

#endif // RING1_STATUS_H_INCLUDED
