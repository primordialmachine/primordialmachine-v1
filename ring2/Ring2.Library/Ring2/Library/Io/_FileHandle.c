// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/_FileHandle.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Io/_FileHandle.h"

void
_Machine_FileHandle_open
  (
    _Machine_FileHandle* self,
    Ring2_String* path,
    Ring1_FileSystem_FileAccessMode fileAccessMode,
    Ring1_FileSystem_ExistingFilePolicy existingFilePolicy,
    Ring1_FileSystem_NonExistingFilePolicy nonExistingFilePolicy
  )
{
  // Validate arguments.
  Ring2_assertNotNull(self);
  Ring2_assertNotNull(path);

  // Translate desired access and (non) existing file policies.
  DWORD dwDesiredAccess = 0;
  if (!(fileAccessMode & (Ring1_FileSystem_FileAccessMode_ReadWrite))) {
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "invalid argument\n");
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (fileAccessMode & Ring1_FileSystem_FileAccessMode_Read) {
    dwDesiredAccess |= GENERIC_READ;
  }
  if (fileAccessMode & Ring1_FileSystem_FileAccessMode_Write) {
    dwDesiredAccess |= GENERIC_WRITE;
  }
  DWORD dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
  DWORD dwCreationDisposition = 0;
  typedef struct PolicyMapping {
    Ring1_FileSystem_ExistingFilePolicy existingFilePolicy;
    Ring1_FileSystem_NonExistingFilePolicy nonExistingFilePolicy;
    DWORD dwCreationDisposition;
    DWORD dwDesiredAccessModifier;
  } PolicyMapping;
  static const PolicyMapping policyMappings[] = {
    // CREATE_NEW is a conditional flag which fails
    // if the file exists and succeeds if the file
    // does not exist and is successfully created.
    // It is not used.
    { Ring1_FileSystem_ExistingFilePolicy_Truncate, Ring1_FileSystem_NonExistingFilePolicy_Create, CREATE_ALWAYS, 0 },
    { Ring1_FileSystem_ExistingFilePolicy_Retain, Ring1_FileSystem_NonExistingFilePolicy_Create, OPEN_ALWAYS, 0 },
    { Ring1_FileSystem_ExistingFilePolicy_Truncate, Ring1_FileSystem_NonExistingFilePolicy_Fail, TRUNCATE_EXISTING, GENERIC_WRITE },
    { Ring1_FileSystem_ExistingFilePolicy_Retain, Ring1_FileSystem_NonExistingFilePolicy_Fail, OPEN_EXISTING, 0 },
  };
  const PolicyMapping* policyMapping = NULL;
  for (size_t i = 0, n = sizeof(policyMappings) / sizeof(PolicyMapping); i < n; ++i) {
    policyMapping = policyMappings + i;
    if (policyMapping->existingFilePolicy == existingFilePolicy
        && policyMapping->nonExistingFilePolicy == nonExistingFilePolicy) {
      break;
    }
  }
  if (policyMapping == NULL) {
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "invalid argument\n");
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  dwDesiredAccess |= policyMapping->dwDesiredAccessModifier;

  self->hHandle = CreateFileA(Ring2_String_getBytes(Ring2_Context_get(), path), dwDesiredAccess, dwShareMode, 0,
                              policyMapping->dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, 0);
  if (INVALID_HANDLE_VALUE == self->hHandle) {
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "unable to open file `%s`\n",
              Ring2_String_getBytes(Ring2_Context_get(), path));
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
}

void
_Machine_FileHandle_close
  (
    _Machine_FileHandle* self
  )
{
  Ring2_assertNotNull(self);
  // Close file handle.
  if (INVALID_HANDLE_VALUE != self->hHandle) {
    CloseHandle(self->hHandle);
    self->hHandle = INVALID_HANDLE_VALUE;
  }
}

size_t
_Machine_FileHandle_getFileSize
  (
    _Machine_FileHandle* self
  )
{
  Ring2_assertNotNull(self);
  if (INVALID_HANDLE_VALUE == self->hHandle) {
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "invalid argument\n");
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  // Get the size of the file. The file size must be smaller than or equal to SIZE_MAX.
  DWORD fileSize = GetFileSize(self->hHandle, NULL);
  if (INVALID_FILE_SIZE == fileSize || fileSize > SIZE_MAX) {
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "environment failed\n");
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
  return fileSize;
}