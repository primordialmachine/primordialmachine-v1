/// @file Runtime/Io/_FileMapping.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Io/_FileMapping.h"

void _Machine_FileMapping_openRead(_Machine_FileMapping* self, Ring2_String* path) {
  _Machine_FileHandle_open(&self->fileHandle, path,
                           Ring1_FileSystem_FileAccessMode_Read,
                           Ring1_FileSystem_ExistingFilePolicy_Retain,
                           Ring1_FileSystem_NonExistingFilePolicy_Fail);
  Ring2_JumpTarget jumpTarget1;
  Ring2_pushJumpTarget(&jumpTarget1);
  if (!setjmp(jumpTarget1.environment)) {
    self->numberOfBytes = _Machine_FileHandle_getFileSize(&self->fileHandle);
    // If the file is empty, use a dummy buffer.
    if (0 == self->numberOfBytes) {
      // Use a dummy buffer.
      static const char DUMMY = 0;
      self->bytes = (char*)&DUMMY;
    } else {
      // Create file mapping.
      self->hFileMapping = CreateFileMapping(self->fileHandle.hHandle, 0, PAGE_READONLY, 0, 0, 0);
      if (NULL == self->hFileMapping) {
        Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__,
                    "unable to create file mapping for file '%s'\n", Machine_String_getBytes(path));
        Ring1_Status_set(Ring1_Status_EnvironmentFailed);
        Ring2_jump();
      }
      // Create view of file mapping.
      self->bytes = (char*)MapViewOfFile(self->hFileMapping, FILE_MAP_READ, 0, 0, 0);
      if (NULL == self->bytes) {
        // Close file mapping.
        CloseHandle(self->hFileMapping);
        self->hFileMapping = NULL;
        //
        Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__,
                    "unable to create file mapping view for file '%s'\n",
                    Machine_String_getBytes(path));
        Ring1_Status_set(Ring1_Status_EnvironmentFailed);
        Ring2_jump();
      }
    }
    //
    Ring2_popJumpTarget();
  } else {
    Ring2_popJumpTarget();
    //
    _Machine_FileHandle_close(&self->fileHandle);
  }
}

void _Machine_FileMapping_openWrite(_Machine_FileMapping* self, Ring2_String* path,
                                                  size_t numberOfBytes) {
  _Machine_FileHandle_open(&self->fileHandle, path,
                           Ring1_FileSystem_FileAccessMode_Write,
                           Ring1_FileSystem_ExistingFilePolicy_Truncate,
                           Ring1_FileSystem_NonExistingFilePolicy_Create);
  Ring2_JumpTarget jumpTarget1;
  Ring2_pushJumpTarget(&jumpTarget1);
  if (!setjmp(jumpTarget1.environment)) {
    self->numberOfBytes = numberOfBytes;
    // If the file is empty, use a dummy buffer.
    if (0 == self->numberOfBytes) {
      // Use a dummy buffer.
      static const char DUMMY = 0;
      self->bytes = (char*)&DUMMY;
    } else {
      // Create file mapping.
      self->hFileMapping
          = CreateFileMapping(self->fileHandle.hHandle, 0, PAGE_READWRITE, 0, numberOfBytes, 0);
      if (NULL == self->hFileMapping) {
        Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__,
                    "unable to create file mapping for file '%s'\n", Machine_String_getBytes(path));
        Ring1_Status_set(Ring1_Status_EnvironmentFailed);
        Ring2_jump();
      }
      // Create view of file mapping.
      self->bytes
          = (char*)MapViewOfFile(self->hFileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
      if (NULL == self->bytes) {
        // Close file mapping.
        CloseHandle(self->hFileMapping);
        self->hFileMapping = NULL;
        //
        Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__,
                    "unable to create file mapping view for file '%s'\n",
                    Machine_String_getBytes(path));
        Ring1_Status_set(Ring1_Status_EnvironmentFailed);
        Ring2_jump();
      }
    }
    //
    Ring2_popJumpTarget();
  } else {
    Ring2_popJumpTarget();
    //
    _Machine_FileHandle_close(&self->fileHandle);
  }
}

void _Machine_FileMapping_close(_Machine_FileMapping* self) {
  if (self->hFileMapping) {
    if (self->bytes) {
      UnmapViewOfFile(self->bytes);
      self->bytes = NULL;
    }
    CloseHandle(self->hFileMapping);
    self->hFileMapping = NULL;
  }
  self->numberOfBytes = 0;
  _Machine_FileHandle_close(&self->fileHandle);
}
