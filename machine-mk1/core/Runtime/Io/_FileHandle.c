/// @file Runtime/Io/_FileHandle.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Io/_FileHandle.h"

void _Machine_FileHandle_open(_Machine_FileHandle* self, Ring2_String* path,
                              Ring1_FileSystem_FileAccessMode fileAccessMode,
                              Ring1_FileSystem_ExistingFilePolicy existingFilePolicy,
                              Ring1_FileSystem_NonExistingFilePolicy nonExistingFilePolicy) {
  // Validate arguments.
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(path);

  // Translate desired access and (non) existing file policies.
  DWORD dwDesiredAccess = 0;
  if (!(fileAccessMode & (Ring1_FileSystem_FileAccessMode_ReadWrite))) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "invalid argument\n");
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
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "invalid argument\n");
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  dwDesiredAccess |= policyMapping->dwDesiredAccessModifier;

  self->hHandle = CreateFileA(Machine_String_getBytes(path), dwDesiredAccess, dwShareMode, 0,
                              policyMapping->dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, 0);
  if (INVALID_HANDLE_VALUE == self->hHandle) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "unable to open file `%s`\n",
                Machine_String_getBytes(path));
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
}

void _Machine_FileHandle_close(_Machine_FileHandle* self) {
  MACHINE_ASSERT_NOTNULL(self);
  // Close file handle.
  if (INVALID_HANDLE_VALUE != self->hHandle) {
    CloseHandle(self->hHandle);
    self->hHandle = INVALID_HANDLE_VALUE;
  }
}

size_t _Machine_FileHandle_getFileSize(_Machine_FileHandle* self) {
  MACHINE_ASSERT_NOTNULL(self);
  if (INVALID_HANDLE_VALUE == self->hHandle) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "invalid argument\n");
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  // Get the size of the file. The file size must be smaller than or equal to SIZE_MAX.
  DWORD fileSize = GetFileSize(self->hHandle, NULL);
  if (INVALID_FILE_SIZE == fileSize || fileSize > SIZE_MAX) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "environment failed\n");
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
  return fileSize;
}
