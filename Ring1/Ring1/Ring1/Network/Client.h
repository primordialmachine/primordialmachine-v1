#if !defined(RING1_NETWORK_CLIENT_H_INCLUDED)
#define RING1_NETWORK_CLIENT_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include <stdint.h>
  
/// @brief Enumeration of flags for creating a client.
typedef enum Ring1_Network_CreateClientFlags {

  /// @brief Symbolic constant denoting the protocol "TCP".
  Ring1_Network_CreateServerFlags_Tcp = (1),

  /// @brief Symbolic constant denoting the protocol "UDP".
  Ring1_Network_CreateServerFlags_Udp = (2),

} Ring1_Network_Createclient;

/// @brief The type of a handle to a client instance.
typedef void *Ring1_Network_ClientHandle;

/// @brief Symbolic constant evaluating to a Ring1_Network_ClientInstanceHandle value refering to the special invalid client instance.
#define Ring1_Network_ServerHandle_Invalid (NULL)

/// @brief Create a client instance.
/// Sets a mutex suh that no other instance can be created until ClientDestroy was invoked for that instance.
/// @param result A pointer to a <code>Ring1_Network_ClientHandle</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @success <code>*result</code> was assigned the handle.
Ring1_CheckReturn() Ring1_Result
Ring1_Network_createClient
  (
    Ring1_Network_ClientHandle *clientHandle
  );

/// @brief Destroy a client instance.
/// @param clientHandle A client instance handle or ClientHandle_Invalid.
void
Ring1_Network_destroyClient
  (
    Ring1_Network_ClientHandle clientHandle
  );
  
#endif // RING1_NETWORK_CLIENT_H_INCLUDED
