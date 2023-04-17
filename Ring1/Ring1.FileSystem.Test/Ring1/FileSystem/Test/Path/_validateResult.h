#if !defined(RING1_FILESYSTEM_TEST_PATH__VALIDATERESULT_H_INCLUDED)
#define RING1_FILESYSTEM_TEST_PATH__VALIDATERESULT_H_INCLUDED

#include "Ring1/All/_Include.h"

static inline Ring1_NoDiscardReturn() Ring1_Result
_validateResult
  (
    Ring1_Test_Context* ctx,
    Ring1_FileSystem_Path* received,
    char const *expectedBytes
  )
{
  size_t numberOfExpectedBytes = crt_strlen(expectedBytes);

  int result;
  char* receivedBytes;
  size_t numberOfReceivedBytes;
  
  // not zero terminated
  if (Ring1_FileSystem_Path_toString(received, false, &receivedBytes, &numberOfReceivedBytes)) {
    Ring1_FileSystem_Path_unref(received);
    received = NULL;
    return Ring1_Result_Failure;
  }
  
  if (Ring1_Memory_compare(&result, expectedBytes, numberOfExpectedBytes, receivedBytes, numberOfReceivedBytes, Ring1_Memory_Compare_Lexicographic)) {
    Ring1_Memory_deallocate(receivedBytes);
    receivedBytes = NULL;  
    return Ring1_Result_Failure;
  }
  
  RING1_TEST_ASSERT_EQ(ctx, result, 0);
  
  Ring1_Memory_deallocate(receivedBytes);
  receivedBytes = NULL;

  // zero-terminated
  if (Ring1_FileSystem_Path_toString(received, true, &receivedBytes, &numberOfReceivedBytes)) {
    return Ring1_Result_Failure;
  }

  if (numberOfReceivedBytes != numberOfExpectedBytes + 1) {
    Ring1_Memory_deallocate(receivedBytes);
    receivedBytes = NULL;
    return Ring1_Result_Failure;
  }

  if (Ring1_Memory_compare(&result, expectedBytes, numberOfExpectedBytes, receivedBytes, numberOfReceivedBytes - 1, Ring1_Memory_Compare_Lexicographic)) {
    Ring1_Memory_deallocate(receivedBytes);
    receivedBytes = NULL;
    return Ring1_Result_Failure;
  }
  if (receivedBytes[numberOfReceivedBytes - 1] != '\0') {
    Ring1_Memory_deallocate(receivedBytes);
    receivedBytes = NULL;
    return Ring1_Result_Failure;
  }

  RING1_TEST_ASSERT_EQ(ctx, result, 0);
  
  return Ring1_Result_Success;
}

#endif // RING1_FILESYSTEM_TEST_PATH_COMPARE_H_INCLUDED
