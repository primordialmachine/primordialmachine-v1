#if !defined(MACHINE_RUNTIME_STATUS_H_INCLUDED)
#define MACHINE_RUNTIME_STATUS_H_INCLUDED

/// @brief Type of a status variable values.
typedef int Machine_StatusValue;

/// @brief Symbolic constant for a status variable value.
/// That value indicates success. Guaranteed to be @a 0.
#define Machine_Status_Success (0)

/// @brief Symbolic constant for a status variable value.
/// That value indicates an allocation failed.
#define Machine_Status_AllocationFailed (1)

/// @brief Symbolic constant for a status variable value.
/// That value indicates an invalid argument.
#define Machine_Status_InvalidArgument (2)

/// @brief Symbolic constant for a status variable value.
/// That value indicates an invalid operation.
#define Machine_Status_InvalidOperation (3)

/// @brief Symbolic constant for a status variable value.
/// That value indicates an index is out of bounds.
#define Machine_Status_IndexOutOfBounds (4)

/// @brief Symbolic constant for a status variable value.
/// That value indicates a capacity is exhausted.
#define Machine_Status_CapacityExhausted (5)

/// @brief Symbolic constant for a status variable value.
/// That value indicates that something is not yet implemented.
#define Machine_Status_NotYetImplemented (6)

/// @brief Symbolic constant for a status variable value.
/// The value indicates that the environment failed.
#define Machine_Status_EnvironmentFailed (7)

/// @brief Get the value of the status variable.
/// @return The value.
/// @default #Machine_Status_Success
Machine_StatusValue Machine_getStatus();

/// @brief Set the value of the status variable.
/// @param status The value.
void Machine_setStatus(Machine_StatusValue status);

#endif // MACHINE_RUNTIME_STATUS_H_INCLUDED