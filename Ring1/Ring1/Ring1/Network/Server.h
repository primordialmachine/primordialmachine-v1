#if !defined(RING1_NETWORK_SERVER_H_INCLUDED)
#define RING1_NETWORK_SERVER_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include <stdint.h>

/// @brief Enumeration of flags for creating a server.
typedef enum Ring1_Network_CreateServerFlags {

  /// @brief Symbolic constant denoting the protocol "TCP".
  Ring1_Network_CreateServerFlags_Tcp = (1),

  /// @brief Symbolic constant denoting the protocol "UDP".
  Ring1_Network_CreateServerFlags_Udp = (2),

} Ring1_Network_CreateServerFlags;

typedef struct Ring1_Network_IpAddress {
  // 32 bit IPv4 host address.
  uint32_t host;
  // 16-bit protocol port.
  uint16_t port;
} Ring1_Network_IpAddress;


/// @brief The type of a handle to a server instance.
typedef void *Ring1_Network_ServerHandle;

/// @brief Symbolic constant evaluating to a Ring1_Network_ServerHandle value refering to the special invalid server instance.
#define Ring1_Network_ServerHandle_Invalid (NULL)

/// @brief Create a server instance.
/// Sets a mutex such that no other instance can be created until server_destroy was invoked for that instance.
/// @param result A pointer to a <code>Ring1_Network_ServerHandle</code> variable.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @success <code>*result</code> was assigned the handle.
Ring1_CheckReturn() Ring1_Result
Ring1_Network_CreateServer
  (
    Ring1_Network_ServerHandle *result,
    Ring1_Network_CreateServerFlags flags
  );

/// @brief Destroy a server instance.
/// @param serverHandle A server instance handle or ServerHandle_Invalid.
void
Ring1_Network_DestroyServer
  (
    Ring1_Network_ServerHandle serverHandle
  );
  
#endif // RING1_NETWORK_SERVER_H_INCLUDED

