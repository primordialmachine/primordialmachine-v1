#if !defined(RING1_COMMANDLINE_ARGUMENT_H_INCLUDED)
#define RING1_COMMANDLINE_ARGUMENT_H_INCLUDED

#include "Ring1/ReferenceCounter.h"
#include "Ring1/Status.h"
#include "Ring1/Result.h"
#include "Ring1/Annotations/_Include.h"


/// @brief A command-line argument consisting of a name and/or a value.
/// There are three kinds of arguments:
/// - both name and value are null pointers:
///   an argument of the form <code>--&lt;string&gt;</code>.
///   This is called a switch argument.
/// - name is not a null pointer, value is a null pointer:
///   an argument of the form <code>--<name>=&lt;string&gt;</code>.
///   This is called a named argument.
/// - name is a null pointer, value is not a null pointer:
///   an argument of the form <code>&lt;string&gt;</code>.
///   This is called a value argument.
typedef struct Ring1_CommandLine_Argument Ring1_CommandLine_Argument;

/// @brief
/// Create an <code>Ring1_CommandLine_Argument</code> object..
/// @param [out] result
/// A pointer to a <code>Ring1_CommandLine_Argument *</code> variable.
/// @param name
/// Pointer to the name or null pointer.
/// @param value
/// Pointer to the value or null pointer.
/// @return
/// #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @success
/// <code>*result</code> was assigned a pointer value to the <code>Ring1_CommandLine_Argument</code> object.
/// @failure
/// <code>result</code> was not dereferenced.
/// This function has set the by-thread status variable.
Ring1_CheckReturn() Ring1_Result
Ring1_CommandLine_Argument_create
  (
    Ring1_CommandLine_Argument **result,
    char const* name,
    char const* value
  );

/// @brief Get the name of an argument.
/// @param [out] result A pointer to a <code>char const *</code> variable.
/// @param self A pointer to this argument.
/// @success <code>*result</code> was assigned a pointer to the name (if any) or a null pointer.
/// @return Pointer to the name (if any), null pointer otherwise.
/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @success
/// <code>*result</code> was assigned a pointer value to the name (if there is a name).
/// Otherwise it was assigned the null pointer value.
/// @failure
/// <code>result</code> is not dereferenced.
/// This function sets the by-thread status variable.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_CommandLine_Argument_getName
  (
    char const** result,
    Ring1_CommandLine_Argument const* self
  );

/// @brief Get the value of an argument.
/// @param [out] result A pointer to a <code>char const *</code> variable.
/// @param argument Pointer to the argument.
/// @return Pointer to the value (if any), null pointer otherwise.
/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @success
/// <code>*result</code> was assigned a pointer value to the value (if there is a value).
/// Otherwise it was assigned the null pointer value.
/// @failure
/// <code>result</code> is not dereferenced.
/// This function sets the by-thread status variable.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_CommandLine_Argument_getValue
  (
    char const** result,
    Ring1_CommandLine_Argument const* self
  );

/// @brief Increment the reference count of an argument.
/// @param argument Pointer to the argument.
void
Ring1_CommandLine_Argument_ref
  (
    Ring1_CommandLine_Argument* argument
  );

/// @brief Decrement the reference count of an argument.
/// @param argument Pointer to the argument.
void
Ring1_CommandLine_Argument_unref
  (
    Ring1_CommandLine_Argument* argument
  );

#endif // RING1_COMMANDLINE_ARGUMENT_H_INCLUDED
