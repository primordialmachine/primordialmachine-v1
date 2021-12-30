/// @file Runtime/Status.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_STATUS_H_INCLUDED)
#define MACHINE_RUNTIME_STATUS_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "_Eal.h"

/// @brief Type of a status variable values.
typedef int Machine_StatusValue;

/// @brief Symbolic constant for a status variable value.
/// That value indicates success. Guaranteed to be @a 0.
#define Machine_Status_Success (0)

/// @brief Symbolic constant for a status variable value.
/// That value indicates an allocation failed.
#define Machine_Status_AllocationFailed (1)

/// @brief Symbolic constant for a status variable value.
/// That value indicates an pointer argument is null.
#define Machine_Status_ArgumentNull (2)

/// @brief Symbolic constant for a status variable value.
/// That value indicates a capacity is exhausted.
#define Machine_Status_CapacityExhausted (3)

/// @brief Symbolic constant for a status variable value.
/// That value indicates a conversion failed.
#define Machine_Status_ConversionFailed (4)

/// @brief Symbolic constant for a status variable value.
/// That value indicates a failure because something is empty.
#define Machine_Status_Empty (5)

/// @brief Symbolic constant for a status variable value.
/// The value indicates that the environment failed.
#define Machine_Status_EnvironmentFailed (6)

/// @brief Symbolic constant for a status variable value.
/// That value indicates a failure because something (already) exists.
#define Machine_Status_Exists (7)

/// @brief Symbolic constant for a status variable value.
/// That value indicates an index is out of bounds.
#define Machine_Status_IndexOutOfBounds (8)

/// @brief Symbolic constant for a status variable value.
/// That value indicates a failure because something is (already) initialized.
#define Machine_Status_Initialized (9)

/// @brief Symbolic constant for a status variable value.
/// That value indicates a failure because of an internal error.
#define Machine_Status_InternalError (10)

/// @brief Symbolic constant for a status variable value.
/// That value indicates an invalid argument was passed.
#define Machine_Status_InvalidArgument (11)

/// @brief Symbolic constant for a status variable value.
/// That value indicates an invalid operation.
#define Machine_Status_InvalidOperation (12)

/// @brief Symbolic constant for a status variable value.
/// That value indicates an invalid number of arguments.
#define Machine_Status_InvalidNumberOfArguments (13)

/// @brief Symbolic constant for a status variable value.
/// That value indicates the occurrence of a lexical error.
#define Machine_Status_LexicalError (14)

/// @brief Symbolic constant for a status variable value.
/// That value indicates a negative overflow.
/// @remark
/// If [a,b] is the interval of numbers a numeric data type can represent,
/// then a negative overflow occurs if an operation results in a value x < a.
#define Machine_Status_NegativeOverflow (15)

/// @brief Symbolic constant for a status variable value.
/// This value indicates a failure because something is not (yet) initialized.
#define Machine_Status_NotInitialized (16)

/// @brief Symbolic constant for a status variable value.
/// That value indicates that something is not yet implemented.
#define Machine_Status_NotYetImplemented (17)

/// @brief Symbolic constant for a status variable value.
/// That value indicates a positive overflow.
/// @remark
/// If [a,b] is the interval of numbers a numeric data type can represent,
/// then a positive overflow occurs if an operation results in a value x > b.
#define Machine_Status_PositiveOverflow (18)

/// @brief Symbolic constant for a status variable value.
/// That value indicates the occurrence of a semantical error.
#define Machine_Status_SemanticalError (19)

/// @brief Symbolic constant for a status variable value.
/// That value indicates the occurrence of a syntactical error.
#define Machine_Status_SyntacticalError (20)

/// @brief Symbolic constant for a status variable value.
/// That value indicates a test failed.
#define Machine_Status_TestFailed (21)

/// @brief Symbolic constant for a status variable value.
/// That value indicates something is too long.
#define Machine_Status_TooLong (22)

/// @brief Symbolic constant for a status variable value.
/// That value indicates something is too short.
#define Machine_Status_TooShort (23)

/// @brief Symbolic constant for a status variable value.
/// The value indicates an underflow.
/// @remark
/// An underflow occurs if the magnitude of a value is too close to zero to be representable.
#define Machine_Status_Underflow (24)

/// @brief Symbolic constant for a status variable value.
/// The value indicates a program point was reached which should not be reached.
#define Machine_Status_UnreachableProgramPointReached (25)

/// @brief Get the value of the status variable.
/// @return The value.
/// @default #Machine_Status_Success
Machine_StatusValue Machine_getStatus();

/// @brief Set the value of the status variable.
/// @param status The value.
void Machine_setStatus(Machine_StatusValue status);

#endif // MACHINE_RUNTIME_STATUS_H_INCLUDED
