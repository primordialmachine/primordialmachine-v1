// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/CommandLine/ArgumentList.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_COMMANDLINE_ARGUMENTLIST_H_INCLUDED)
#define MKX_COMMANDLINE_ARGUMENTLIST_H_INCLUDED


#include "Ring1/Intrinsic/_Include.h"
#include "Ring1/Status.h"


typedef struct Mkx_CommandLine_Argument Mkx_CommandLine_Argument;

typedef struct Mkx_CommandLine_ArgumentList Mkx_CommandLine_ArgumentList;

/// @brief
/// Create a <code>Ring1_CommandLine_ArgumentList</code> object.
/// 
/// @param [out] result
/// A pointer to a <code>Mkx_CommandLine_ArgumentList *</code> variable.
/// 
/// @return
/// #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// 
/// @success
/// <code>*result</code> was assigned a pointer the <code>Ring1_CommandLine_ArgumentList</code> object.
/// 
/// @failure
/// <code>result</code> was not dereferenced.
/// The by-thread status variable was set to status not equal to #Ring1_Status_Success.
Ring1_CheckReturn() Ring1_Result
Mkx_CommandLine_ArgumentList_create
  (
    Mkx_CommandLine_ArgumentList **result
  );

/// @brief Increment the reference count of this <code>Ring1_CommandLine_ArgumentList</code> object.
/// @param self A pointer to this <code>Ring1_CommandLine_ArgumentList</code> object.
void
Mkx_CommandLine_ArgumentList_ref
  (
    Mkx_CommandLine_ArgumentList* self
  );

/// @brief Decrement the reference count of this <code>Ring1_CommandLine_ArgumentList</code> object.
/// @param self A pointer to this <code>Ring1_CommandLine_ArgumentList</code> object.
void
Mkx_CommandLine_ArgumentList_unref
  (
    Mkx_CommandLine_ArgumentList* self
  );

/// @brief
/// Append an argument to this argument list.
/// 
/// @param self
/// A pointer to this argument list.
/// 
/// @param argument
/// A pointer to the argument.
/// 
/// @return
/// #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// 
/// @success
/// The argument was appended to this argument list.
/// 
/// @failure
/// <code>result</code> was not dereferenced.
/// The by-thread status variable was set to status not equal to #Ring1_Status_Success.
Ring1_CheckReturn() Ring1_Result
Mkx_CommandLine_ArgumentList_append
  (
    Mkx_CommandLine_ArgumentList* self,
    Mkx_CommandLine_Argument* argument
  );

/// @brief
/// Get the size of an argument list.
/// 
/// @param [out] result
/// A pointer to an <code>int64_t</code> variable.
/// 
/// @param self
/// A pointer to this argument list.
/// 
/// @return
/// #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// 
/// @success
/// <code>*result</code> was assigned the size of this argument list.
/// 
/// @failure
/// <code>result</code> was not dereferenced.
/// The by-thread status variable was set to status not equal to #Ring1_Status_Success.
Ring1_CheckReturn() Ring1_Result
Mkx_CommandLine_ArgumentList_getSize
  (
    int64_t *result,
    Mkx_CommandLine_ArgumentList* self
  );

/// @brie
/// Get the argument at the specified index in this argument list.
/// 
/// @param result
/// A pointer to a <code>Mkx_CommandLine_Argument *</code> variable.
/// 
/// @param self
/// A pointer to this argument list.
/// 
/// @param index
/// The index.
/// 
/// @return
/// #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// 
/// @success
/// - <code>*result</code> was assigned a pointer to the argument at the specified index in this argument list.
/// - the caller acquirees a reference to that object.
/// 
/// @failure
/// <code>result</code> was not dereferenced.
/// The by-thread status variable was set to status not equal to #Ring1_Status_Success. 
Ring1_CheckReturn() Ring1_Result
Mkx_CommandLine_ArgumentList_getAt
  (
    Mkx_CommandLine_Argument **result,
    Mkx_CommandLine_ArgumentList* argumentList,
    int64_t index
  );

/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// 
/// @failure
/// <code>result</code> was not dereferenced.
/// The by-thread status variable was set to status not equal to #Ring1_Status_Success. 
Ring1_CheckReturn() Ring1_Result
Mkx_CommandLine_ArgumentList_removeAt
  (
    Mkx_CommandLine_ArgumentList* argumentList,
    int64_t index
  );

#endif // MKX_COMMANDLINE_ARGUMENTLIST_H_INCLUDED
