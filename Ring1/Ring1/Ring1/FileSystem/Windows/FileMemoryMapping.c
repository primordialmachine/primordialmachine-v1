// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/FileMemoryMapping.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Windows/FileMemoryMapping.h"

#include <stdio.h>
#include "Ring1/Status.h"

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Windows_FileMemoryMapping_openRead
  (
    Ring1_FileSystem_Windows_FileMemoryMapping* self,
    const char* path
  )
{
  if (Ring1_FileSystem_Windows_FileHandle_create(&self->fileHandle, path,
                                                 Ring1_FileSystem_FileAccessMode_Read,
                                                 Ring1_FileSystem_ExistingFilePolicy_Retain,
                                                 Ring1_FileSystem_NonExistingFilePolicy_Fail)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_FileSystem_Windows_FileHandle_getFileSize(&self->numberOfBytes, self->fileHandle)) {
    // Destroy the file handle.
    Ring1_FileSystem_Windows_FileHandle_destroy(self->fileHandle);
    self->fileHandle = NULL;
    //
    fprintf(stderr, "%s:%d: unable to determine file size of file '%s'\n", 
            __FILE__, __LINE__, path);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  // If the file is empty, use a dummy buffer.
  if (0 == self->numberOfBytes) {
    // Use a dummy buffer.
    static const char DUMMY = 0;
    self->bytes = (char*)&DUMMY;
    self->hFileMapping = NULL;
    return Ring1_Result_Success;
  } else {
    // Create file mapping.
    self->hFileMapping = CreateFileMapping(self->fileHandle->hFileHandle, 0, PAGE_READONLY, 0, 0, 0);
    if (NULL == self->hFileMapping) {
      // Destroy the file handle.
      Ring1_FileSystem_Windows_FileHandle_destroy(self->fileHandle);
      self->fileHandle = NULL;
      //
      fprintf(stderr, "%s:%d: unable to create file mapping for file '%s'\n", 
              __FILE__, __LINE__, path);
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      return Ring1_Result_Failure;
    }
    // Create view of file mapping.
    self->bytes = (char*)MapViewOfFile(self->hFileMapping, FILE_MAP_READ, 0, 0, 0);
    if (NULL == self->bytes) {
      // Close file mapping.
      CloseHandle(self->hFileMapping);
      self->hFileMapping = NULL;
      // Destroy the file handle.
      Ring1_FileSystem_Windows_FileHandle_destroy(self->fileHandle);
      self->fileHandle = NULL;
      //
      fprintf(stderr, "%s:%d: unable to create file mapping view for file '%s'\n",
              __FILE__, __LINE__, path);
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      return Ring1_Result_Failure;
    }
    return Ring1_Result_Success;
  }
}

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Windows_FileMemoryMapping_openWrite
  (
    Ring1_FileSystem_Windows_FileMemoryMapping* self,
    const char* path,
    size_t numberOfBytes
  )
{
  // Must be file access mode read and write even though we are just writing.
  if (Ring1_FileSystem_Windows_FileHandle_create(&self->fileHandle, path,
                                                 Ring1_FileSystem_FileAccessMode_ReadWrite,
                                                 Ring1_FileSystem_ExistingFilePolicy_Truncate,
                                                 Ring1_FileSystem_NonExistingFilePolicy_Create)) {
    return Ring1_Result_Failure;
  }
  self->numberOfBytes = numberOfBytes;
  // If the file is empty, use a dummy buffer.
  if (0 == self->numberOfBytes) {
    // Use a dummy buffer.
    static const char DUMMY = 0;
    self->bytes = (char*)&DUMMY;
    self->hFileMapping = NULL;
    return Ring1_Result_Success;
  } else {
    // Create file mapping.
    self->hFileMapping = CreateFileMapping(self->fileHandle->hFileHandle, 0, PAGE_READWRITE, 0, numberOfBytes, 0);
    if (NULL == self->hFileMapping) {
      // Destroy the file handle.
      Ring1_FileSystem_Windows_FileHandle_destroy(self->fileHandle);
      self->fileHandle = NULL;
      //
      fprintf(stderr, "%s: %d: unable to create file mapping for file '%s' for writing\n", __FILE__, __LINE__, path);
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      return Ring1_Result_Failure;
    }
    // Create view of file mapping.
    self->bytes = (char*)MapViewOfFile(self->hFileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
    if (NULL == self->bytes) {
      // Close file mapping.
      CloseHandle(self->hFileMapping);
      self->hFileMapping = NULL;
      // Destroy the file handle.
      Ring1_FileSystem_Windows_FileHandle_destroy(self->fileHandle);
      self->fileHandle = NULL;
      //
      fprintf(stderr, "%s:%d: unable to create file mapping view for file '%s' for writing\n", __FILE__, __LINE__, path);
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      return Ring1_Result_Failure;
    }
    return Ring1_Result_Success;
  }
}

void
Ring1_FileSystem_Windows_FileMemoryMapping_close
  (
    Ring1_FileSystem_Windows_FileMemoryMapping* self
  )
{
  if (self->hFileMapping) {
    if (self->bytes) {
      UnmapViewOfFile(self->bytes);
      self->bytes = NULL;
    }
    CloseHandle(self->hFileMapping);
    self->hFileMapping = NULL;
  }
  self->numberOfBytes = 0;
  Ring1_FileSystem_Windows_FileHandle_destroy(self->fileHandle);
  self->fileHandle = NULL;
}
