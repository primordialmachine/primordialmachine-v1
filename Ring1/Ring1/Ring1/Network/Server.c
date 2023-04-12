#include "Ring1/Network/Server.h"

#include "Ring1/Memory.h"
#include "Ring1/Status.h"

typedef struct Server {
  int dummy;
} Server;

Ring1_CheckReturn() Ring1_Result
Ring1_Network_reateServer
  (
    Ring1_Network_ServerHandle *result,
    Ring1_Network_CreateServerFlags flags
  )
{
  Server* server = NULL;
  if (Ring1_Memory_allocate(&server, sizeof(Server))) {
    return Ring1_Result_Failure;
  }
  *result = server;
  return Ring1_Result_Success;
}

void
Ring1_Network_destroyServer
  (
    Ring1_Network_ServerHandle serverHandle
  )
{
  Ring1_Memory_deallocate(serverHandle);
  serverHandle = NULL;
}
