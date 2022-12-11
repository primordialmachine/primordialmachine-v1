#if !defined(RING1_FILESYSTEM_PATH_H_INCLUDED)
#define RING1_FILESYSTEM_PATH_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"

typedef struct Ring1_FileSystem_Path Ring1_FileSystem_Path;

/// @param [out] result A pointer to a <code>Ring1_FileSystem_Path *</code> variable.
/// @param string A pointer to a string denoting a path.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @remarks
/// - The empty string denotes the empty path.
Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Path_create
  (
    Ring1_FileSystem_Path **result,
    const char *string
  );

void
Ring1_FileSystem_Path_ref
  (
    Ring1_FileSystem_Path *self
  );
  
void
Ring1_FileSystem_Path_unref
  (
    Ring1_FileSystem_Path *self
  );

#endif // RING1_FILESYSTEM_PATH_H_INCLUDED
