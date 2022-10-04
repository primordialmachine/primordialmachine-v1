// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Atom.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_ATOM_H_INCLUDED)
#define RING1_ATOM_H_INCLUDED


#include "Ring1/Intrinsic.h"
#include "Ring1/Module.h"
#include "Ring1/Status.h"


Ring1_Module_Declare(Atom)



/// @brief A deque of pointers.
/// @remark Implemented using the PIMPL idiom.
/// Supports null pointers.
typedef struct Mkx_Atom Mkx_Atom;

/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure. 
Ring1_CheckReturn() Ring1_Result
Mkx_Atom_getOrCreate
  (
    Mkx_Atom **result,
    const char* bytes,
    size_t numberOfBytes
  );

void
Mkx_Atom_reference
  (
    Mkx_Atom* atom
  );

void
Mkx_Atom_unreference
  (
    Mkx_Atom* atom
  );

Ring1_CheckReturn() Ring1_Result
Mkx_Atom_getBytes
  (
    const char **result,
    Mkx_Atom* atom
  );

Ring1_CheckReturn() Ring1_Result
Mkx_Atom_getNumberOfBytes
  (
    int64_t *result,
    Mkx_Atom* atom
  );

Ring1_CheckReturn() int
Mkx_Atom_getHashValue
  (
    int64_t* result,
    Mkx_Atom* atom
  );

#endif // RING1_ATOM_H_INCLUDED
