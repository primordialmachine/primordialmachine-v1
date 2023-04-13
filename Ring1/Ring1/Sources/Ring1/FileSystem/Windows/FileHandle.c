// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/FileHandle.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Windows/FileHandle.h"

#include "Ring1/Memory/_Include.h"
#include "Ring1/Status.h"

static HANDLE g_outputFileHandle = INVALID_HANDLE_VALUE;
static HANDLE g_inputFileHandle = INVALID_HANDLE_VALUE;
static HANDLE g_errorFileHandle = INVALID_HANDLE_VALUE;

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_startup() {
  //
  g_outputFileHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  if (g_outputFileHandle == INVALID_HANDLE_VALUE) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  //
  g_inputFileHandle = GetStdHandle(STD_INPUT_HANDLE);
  if (g_inputFileHandle == INVALID_HANDLE_VALUE) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  //
  g_errorFileHandle = GetStdHandle(STD_ERROR_HANDLE);
  if (g_errorFileHandle == INVALID_HANDLE_VALUE) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  //
  return Ring1_Result_Success;
}

void
Ring1_FileSystem_Windows_shutdown() {
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_FileHandle_create
  (
    Ring1_FileSystem_Windows_FileHandle** result,
    const char *pathname,
    Ring1_FileSystem_FileAccessMode fileAccessMode,
    Ring1_FileSystem_ExistingFilePolicy existingFilePolicy,
    Ring1_FileSystem_NonExistingFilePolicy nonExistingFilePolicy
  )
{
  if (!result || !pathname) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  // Translate desired access and (non) existing file policies.
  DWORD dwDesiredAccess = 0;
  if (!(fileAccessMode & Ring1_FileSystem_FileAccessMode_ReadWrite)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (fileAccessMode & Ring1_FileSystem_FileAccessMode_Read) {
    dwDesiredAccess |= GENERIC_READ;
  }
  if (fileAccessMode & Ring1_FileSystem_FileAccessMode_Write) {
    dwDesiredAccess |= GENERIC_WRITE;
  }
  // Set share mode.
  DWORD dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
  // Translate existing file policy and non-existing file policy to creation disposition
  // and desired access.
  DWORD dwCreationDisposition = 0;
  typedef struct PolicyMapping
  {
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
    { Ring1_FileSystem_ExistingFilePolicy_Truncate,
      Ring1_FileSystem_NonExistingFilePolicy_Create,
      CREATE_ALWAYS,
      0 },
    { Ring1_FileSystem_ExistingFilePolicy_Retain,
      Ring1_FileSystem_NonExistingFilePolicy_Create,
      OPEN_ALWAYS,
      0 },
    { Ring1_FileSystem_ExistingFilePolicy_Truncate,
      Ring1_FileSystem_NonExistingFilePolicy_Fail,
      TRUNCATE_EXISTING,
      GENERIC_WRITE },
    { Ring1_FileSystem_ExistingFilePolicy_Retain,
      Ring1_FileSystem_NonExistingFilePolicy_Fail,
      OPEN_EXISTING,
      0 },
  };
  const PolicyMapping* policyMapping = NULL;
  for (size_t i = 0, n = sizeof(policyMappings) / sizeof(PolicyMapping);
       i < n;
       ++i) {
    policyMapping = policyMappings + i;
    if (policyMapping->existingFilePolicy == existingFilePolicy &&
        policyMapping->nonExistingFilePolicy == nonExistingFilePolicy) {
      break;
    }
  }
  if (policyMapping == NULL) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  dwDesiredAccess |= policyMapping->dwDesiredAccessModifier;

  Ring1_FileSystem_Windows_FileHandle* self;
  if (Ring1_Memory_allocate(&self, sizeof(Ring1_FileSystem_Windows_FileHandle))) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  self->hFileHandle = CreateFileA(pathname,
                                  dwDesiredAccess,
                                  dwShareMode,
                                  0,
                                  policyMapping->dwCreationDisposition,
                                  FILE_ATTRIBUTE_NORMAL,
                                  0);
  if (self->hFileHandle == INVALID_HANDLE_VALUE) {
    Ring1_Memory_deallocate(self);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  *result = self;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_FileHandle_createStandardOutput
  (
    Ring1_FileSystem_Windows_FileHandle** result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Windows_FileHandle* self;
  if (Ring1_Memory_allocate(&self, sizeof(Ring1_FileSystem_Windows_FileHandle))) {
    return Ring1_Result_Failure;
  }
  self->hFileHandle = g_outputFileHandle;
  if (self->hFileHandle == INVALID_HANDLE_VALUE || self->hFileHandle == NULL) {
    Ring1_Memory_deallocate(self);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  *result = self;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_FileHandle_createStandardError
  (
    Ring1_FileSystem_Windows_FileHandle** result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Windows_FileHandle* self;
  if (Ring1_Memory_allocate(&self, sizeof(Ring1_FileSystem_Windows_FileHandle))) {
    return Ring1_Result_Failure;
  }
  self->hFileHandle = g_errorFileHandle;
  if (self->hFileHandle == INVALID_HANDLE_VALUE || self->hFileHandle == NULL) {
    Ring1_Memory_deallocate(self);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  *result = self;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_FileHandle_createStandardInput
  (
    Ring1_FileSystem_Windows_FileHandle** result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Windows_FileHandle* self;
  if (Ring1_Memory_allocate(&self, sizeof(Ring1_FileSystem_Windows_FileHandle))) {
    return Ring1_Result_Failure;
  }
  self->hFileHandle = g_inputFileHandle;
  if (self->hFileHandle == INVALID_HANDLE_VALUE || self->hFileHandle == NULL) {
    Ring1_Memory_deallocate(self);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  *result = self;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_FileHandle_getFileSize
  (
    size_t *result,
    Ring1_FileSystem_Windows_FileHandle *self
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  
  }
  LARGE_INTEGER liFileSize;
  if (!GetFileSizeEx(self->hFileHandle, &liFileSize)) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  if (liFileSize.QuadPart > SIZE_MAX) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
    return Ring1_Result_Failure;
  }
  *result = liFileSize.QuadPart;
  return Ring1_Result_Success;
}

void
Ring1_FileSystem_Windows_FileHandle_destroy
  (
    Ring1_FileSystem_Windows_FileHandle *self
  )
{ 
  if (self->hFileHandle != INVALID_HANDLE_VALUE && self->hFileHandle != NULL) {
    if (self->hFileHandle != g_outputFileHandle &&
        self->hFileHandle != g_inputFileHandle &&
        self->hFileHandle != g_errorFileHandle) {
      CloseHandle(self->hFileHandle);
      self->hFileHandle = NULL;
    }
    self->hFileHandle = NULL;
  }
  Ring1_Memory_deallocate(self);
}
