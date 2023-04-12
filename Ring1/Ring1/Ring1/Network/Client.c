#include "Ring1/Network/Client.h"

#include "Ring1/Memory.h"
#include "Ring1/Status.h"

typedef struct Client {
  int dummy;
} Client;

Ring1_CheckReturn() Ring1_Result
Ring1_Network_createClient
  (
    Ring1_Network_ClientHandle *clientHandle
  )
{
  if (!clientHandle) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Client* client = NULL;
  if (Ring1_Memory_allocate(&client, sizeof(Client))) {
    return Ring1_Result_Failure;
  }
  *clientHandle = client;
  return Ring1_Result_Success;
}

void
Ring1_Network_destroyClient
  (
    Ring1_Network_ClientHandle clientHandle
  )
{
  Ring1_Memory_deallocate(clientHandle);
}
