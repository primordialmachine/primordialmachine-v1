// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Console/ConnectionBase.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CONSOLE_CONNECTIONBASE_H_INCLUDED)
#define RING1_CONSOLE_CONNECTIONBASE_H_INCLUDED


#include "Ring1/Console.h"
#include "Ring1/Memory/_Include.h"
#include "Ring1/ReferenceCounter.h"


#define RING1_CONSOLE_CONNECTIONBASE(p) ((Ring1_Console_ConnectionBase *)p)

/// @brief The base of all connection.
typedef struct Ring1_Console_ConnectionBase Ring1_Console_ConnectionBase;

struct Ring1_Console_ConnectionBase {
  Ring1_ReferenceCounter referenceCount;
  void (*destruct)(Ring1_Console_ConnectionBase* connection);
  Ring1_Result (*getColor)(Ring1_Console_ConnectionBase* connection, Ring1_Console_Color *colo);
  Ring1_Result (*flush)(Ring1_Console_ConnectionBase* connection);
  Ring1_Result (*setColor)(Ring1_Console_ConnectionBase* connection, Ring1_Console_Color color);
  Ring1_Result (*write)(Ring1_Console_ConnectionBase* connection, const char *bytes, size_t numberOfBytes);
}; // struct Ring1_Console_ConnectionBase

/// @brief Destruct a console connection.
/// @param console A pointer to a constructed console connection.
void
Ring1_Console_ConnectionBase_destruct
  (
    Ring1_Console_ConnectionBase* connection
  );

/// @brief Construct a console connection.
/// @param connection A pointer to the unconstructed console connection.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_ConnectionBase_construct
  (
    Ring1_Console_ConnectionBase* connection
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_ConnectionBase_flush
  (
    Ring1_Console_ConnectionBase* connection
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_ConnectionBase_getColor
  (
    Ring1_Console_ConnectionBase* connection,
    Ring1_Console_Color* color
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_ConnectionBase_setColor
  (
    Ring1_Console_ConnectionBase* connection,
    Ring1_Console_Color color
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_ConnectionBase_write
  (
    Ring1_Console_ConnectionBase* connection,
    const char* bytes,
    size_t numberOfBytes
  );

void
Ring1_Console_ConnectionBase_ref
  (
    Ring1_Console_ConnectionBase* connection
  );

void
Ring1_Console_ConnectionBase_unref
  (
    Ring1_Console_ConnectionBase* connection
  );


#endif // RING1_CONSOLE_CONNECTIONBASE_H_INCLUDED
