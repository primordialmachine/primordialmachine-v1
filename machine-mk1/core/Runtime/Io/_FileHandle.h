/// @file Runtime/Io/_FileHandle.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_IO__FILEHANDLE_H_INCLUDED)
#define MACHINE_RUNTIME_IO__FILEHANDLE_H_INCLUDED

#include "Machine.h"

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "Runtime/Io/ExistingFilePolicy.h"
#include "Runtime/Io/FileAccessMode.h"
#include "Runtime/Io/NonExistingFilePolicy.h"
#include "Runtime/String.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/// @brief Helper for file handles.
typedef struct _Machine_FileHandle {
  HANDLE hHandle;
} _Machine_FileHandle;

static inline void _Machine_FileHandle_open(_Machine_FileHandle* self, Machine_String* path,
                                            Machine_FileAccessMode fileAccessMode,
                                            Machine_ExistingFilePolicy existingFilePolicy,
                                            Machine_NonExistingFilePolicy nonExistingFilePolicy) {
  // Validate arguments.
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(path);

  // Translate desired access and (non) existing file policies.
  DWORD dwDesiredAccess = 0;
  if (!(fileAccessMode & (Machine_FileAccessMode_ReadWrite))) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "invalid argument\n");
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  if (fileAccessMode & Machine_FileAccessMode_Read) {
    dwDesiredAccess |= GENERIC_READ;
  }
  if (fileAccessMode & Machine_FileAccessMode_Write) {
    dwDesiredAccess |= GENERIC_WRITE;
  }
  DWORD dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
  DWORD dwCreationDisposition = 0;
  typedef struct PolicyMapping {
    Machine_ExistingFilePolicy existingFilePolicy;
    Machine_NonExistingFilePolicy nonExistingFilePolicy;
    DWORD dwCreationDisposition;
    DWORD dwDesiredAccessModifier;
  } PolicyMapping;
  static const PolicyMapping policyMappings[] =
  {
    // CREATE_NEW is a conditional flag which fails
    // if the file exists and succeeds if the file
    // does not exist and is successfully created.
    // It is not used.
    { Machine_ExistingFilePolicy_Truncate,
      Machine_NonExistingFilePolicy_Create,
      CREATE_ALWAYS,
      0 },
    { Machine_ExistingFilePolicy_Retain,
      Machine_NonExistingFilePolicy_Create,
      OPEN_ALWAYS,
      0 },
    { Machine_ExistingFilePolicy_Truncate,
      Machine_NonExistingFilePolicy_Fail,
      TRUNCATE_EXISTING,
      GENERIC_WRITE },
    { Machine_ExistingFilePolicy_Retain,
      Machine_NonExistingFilePolicy_Fail,
      OPEN_EXISTING,
      0 },
  };
  const PolicyMapping* policyMapping = NULL;
  for (size_t i = 0, n = sizeof(policyMappings) / sizeof(PolicyMapping); i < n; ++i) {
    policyMapping = policyMappings + i;
    if (policyMapping->existingFilePolicy == existingFilePolicy &&
        policyMapping->nonExistingFilePolicy == nonExistingFilePolicy) {
      break;
    }
  }
  if (policyMapping == NULL) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "invalid argument\n");
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  dwDesiredAccess |= policyMapping->dwDesiredAccessModifier;

  self->hHandle = CreateFileA(Machine_String_getBytes(path), dwDesiredAccess, dwShareMode, 0, policyMapping->dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, 0);
  if (INVALID_HANDLE_VALUE == self->hHandle) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "unable to open file `%s`\n", Machine_String_getBytes(path));
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }
}

static inline void _Machine_FileHandle_close(_Machine_FileHandle* self) {
  MACHINE_ASSERT_NOTNULL(self);
  // Close file handle.
  if (INVALID_HANDLE_VALUE != self->hHandle) {
    CloseHandle(self->hHandle);
    self->hHandle = INVALID_HANDLE_VALUE;
  }
}

static inline size_t _Machine_FileHandle_getFileSize(_Machine_FileHandle *self) {
  MACHINE_ASSERT_NOTNULL(self);
  if (INVALID_HANDLE_VALUE == self->hHandle) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "invalid argument\n");
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  // Get the size of the file. The file size must be smaller than or equal to SIZE_MAX.
  DWORD fileSize = GetFileSize(self->hHandle, NULL);
  if (INVALID_FILE_SIZE == fileSize || fileSize > SIZE_MAX) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "environment failed\n");
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Machine_jump();
  }
  return fileSize;
}

#endif // MACHINE_RUNTIME_IO__FILEHANDLE_H_INCLUDED
