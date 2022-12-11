// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Console.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CONSOLE_H_INCLUDED)
#define RING1_CONSOLE_H_INCLUDED


#include "Ring1/Annotations/_Include.h"
#include "Ring1/Module.h"


Ring1_Module_Declare(Ring1, Console)


/// @brief Type of values denoting colors of consoles.
typedef int Ring1_Console_Color;

/// @brief Default console color is "gray".
#define Ring1_Console_Color_Default (0)

/// @brief "gray" console color.
#define Ring1_Console_Color_Gray (0)

/// @brief "white" console color.
#define Ring1_Console_Color_White (1)

/// @brief "dark red" console color.
#define Ring1_Console_Color_DarkRed (2)

/// @brief "light red" console color.
#define Ring1_Console_Color_LightRed (3)

/// @brief "dark green" console color.
#define Ring1_Console_Color_DarkGreen (4)

/// @brief "light green" console color.
#define Ring1_Console_Color_LightGreen (5)

/// @brief "dark blue" console color.
#define Ring1_Console_Color_DarkBlue (6)

/// @brief "light blue" console color.
#define Ring1_Console_Color_LightBlue (7)

/// @brief "dark yellow" console color.
#define Ring1_Console_Color_DarkYellow (8)

/// @brief "light yellow" console color.
#define Ring1_Console_Color_LightYellow (9)

/// @brief "dark magenta" console color.
#define Ring1_Console_Color_DarkMagenta (10)

/// @brief "light magenta" console color.
#define Ring1_Console_Color_LightMagenta (11)

/// @brief "dark cyan" console color.
#define Ring1_Console_Color_DarkCyan (12)

/// @brief "light cyan" console color.
#define Ring1_Console_Color_LightCyan (13)

/// @brief The value of the numerically least Mkx_Console_Color_* symbolic constant.
#define Ring1_Console_Color_Min (0)

/// @brief The value of the numerically greatest Mkx_Console_Color_* symbolic constant.
#define Ring1_Console_Color_Max (13)

/// @brief The opaque type of a console connection.
typedef void Ring1_Console_Connection;

/// @brief Get an "output" connection.
/// @return A pointer to the "output" connection on success, a null pointer on failure.
/// @remark The "output" connection is the standard output handle.
/// @remark An object returned must be unreferenced using Ring1_Console_Connection_unref when no longer required.
Ring1_NoDiscardReturn() Ring1_Console_Connection*
Ring1_Console_getOutputConnection
  (
  );

/// @brief Get an "error" connection.
/// @return A pointer to the "error" connection on success, a null pointer on failure.
/// @remark The "error" connection writes to the standard error handle.
/// @remark An object returned must be unreferenced using Ring1_Console_Connection_unref when no longer required.
Ring1_NoDiscardReturn() Ring1_Console_Connection*
Ring1_Console_getErrorConnection
  (
  );

/// @brief Flush a connection.
/// @param connection A pointer to the console.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_Connection_flush
  (
    Ring1_Console_Connection *connection
  );

/// @brief Get the text color of a connection.
/// @param result A pointer to a <code>Mkx_Console_Color</code> variable.
/// @param connection A pointer to the connection.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_Connection_getColor
  (
    Ring1_Console_Color *result,
    Ring1_Console_Connection* connection
  );

/// @brief Set the text color of a connection.
/// @param connection A pointer to the connection.
/// @param color The color.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_Connection_setColor
  (
    Ring1_Console_Connection* connection,
    Ring1_Console_Color color
  );

/// @brief Write Bytes to a connection.
/// @param connection A pointer to the connection.
/// @param bytes A pointer to an array of @a numberOfBytes Bytes.
/// @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_Connection_write
  (
    Ring1_Console_Connection* connection,
    const char* bytes,
    size_t numberOfBytes
  );

/// @brief Increment the reference count of a connection by @a 1.
/// @param connection A pointer to the connection.
void
Ring1_Console_Connection_ref
  (
    Ring1_Console_Connection* connection
  );

/// @brief Decrement the reference count of a connection by @a 1.
/// @param connection A pointer to the connection.
void
Ring1_Console_Connection_unref
  (
    Ring1_Console_Connection* connection
  );


#endif  // RING1_CONSOLE_H_INCLUDED
