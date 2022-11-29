// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Libc/FileHandle.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Libc/FileHandle.h"

#include "Ring1/Memory.h"
#include "Ring1/Status.h"

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_FileHandle_createRead
  (
    Ring1_FileSystem_Libc_FileHandle** result,
    const char *pathname
  )
{
  if (!result || !pathname) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Libc_FileHandle* self;
  if (Ring1_Memory_allocate(&self, sizeof(Ring1_FileSystem_Libc_FileHandle))) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  self->fileDescriptor = fopen(pathname, "rb");
  if (!self->fileDescriptor) {
    Ring1_Memory_deallocate(self);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  *result = self;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_FileHandle_createWrite
  (
    Ring1_FileSystem_Libc_FileHandle** result,
    const char* pathname
  )
{
  if (Ring1_Unlikely(!result || !pathname)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Libc_FileHandle* self;
  if (Ring1_Memory_allocate(&self, sizeof(Ring1_FileSystem_Libc_FileHandle))) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  self->fileDescriptor = fopen(pathname, "wb");
  if (!self->fileDescriptor) {
    Ring1_Memory_deallocate(self);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  *result = self;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_FileHandle_createStandardOutput
  (
    Ring1_FileSystem_Libc_FileHandle** result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Libc_FileHandle* self;
  if (Ring1_Memory_allocate(&self, sizeof(Ring1_FileSystem_Libc_FileHandle))) {
    return Ring1_Result_Failure;
  }
  self->fileDescriptor = stdout;
  *result = self;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_FileHandle_createStandardError
  (
    Ring1_FileSystem_Libc_FileHandle** result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Libc_FileHandle* self;
  if (Ring1_Memory_allocate(&self, sizeof(Ring1_FileSystem_Libc_FileHandle))) {
    return Ring1_Result_Failure;
  }
  self->fileDescriptor = stderr;
  *result = self;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
  Ring1_FileSystem_Libc_FileHandle_createStandardInput
  (
    Ring1_FileSystem_Libc_FileHandle** result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Libc_FileHandle* self;
  if (Ring1_Memory_allocate(&self, sizeof(Ring1_FileSystem_Libc_FileHandle))) {
    return Ring1_Result_Failure;
  }
  self->fileDescriptor = stdin;
  *result = self;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_FileHandle_getFileSize
  (
    size_t *result,
    Ring1_FileSystem_Libc_FileHandle *self
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  
  }
  if (fseek(self->fileDescriptor, 0, SEEK_END)) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  long n = ftell(self->fileDescriptor);
  if (n == -1L) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  if (fseek(self->fileDescriptor, 0, SEEK_SET)) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  *result = n;
  return Ring1_Result_Success;
}

void
Ring1_FileSystem_Libc_FileHandle_destroy
  (
    Ring1_FileSystem_Libc_FileHandle *self
  )
{ 
  if (self->fileDescriptor) {
    if (self->fileDescriptor != stdout && self->fileDescriptor != stderr && self->fileDescriptor != stdin) {
      fclose(self->fileDescriptor);
    }
    self->fileDescriptor = NULL;
  }
  Ring1_Memory_deallocate(self);
}
