// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Atom/_Include.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_ATOM__INCLUDE_H_INCLUDED)
#define RING1_ATOM__INCLUDE_H_INCLUDED

#include "Ring1/Module.h"

Ring1_Module_Declare(Ring1, Atom)

/// @brief An atom.
typedef struct Ring1_Atom Ring1_Atom;

/// @brief Get or create an atom from an array of Bytes.
/// @param result A pointer to a <code>Ring1_Atom *</code> variable.
/// @param bytes A pointer to an array of @a numberOfBytes Bytes.
/// @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure. 
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Atom_getOrCreate
  (
    Ring1_Atom **result,
    const char* bytes,
    size_t numberOfBytes
  );

/// @brief Increment the reference count of an atom.
/// @param atom A pointer to the atom.
void
Ring1_Atom_reference
  (
    Ring1_Atom* atom
  );

/// @brief Decrement the reference count of an atom.
/// @param atom A pointer to the atom.
void
Ring1_Atom_unreference
  (
    Ring1_Atom* atom
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Atom_getBytes
  (
    const char **result,
    Ring1_Atom* atom
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Atom_getNumberOfBytes
  (
    int64_t *result,
    Ring1_Atom* atom
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Atom_getHashValue
  (
    int64_t* result,
    Ring1_Atom* atom
  );

#endif // RING1_ATOM__INCLUDE_H_INCLUDED
