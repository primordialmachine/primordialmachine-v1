// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Console/Demo/Main.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include <stdlib.h>
#include <string.h>
#include "Ring1/Console.h"

static Ring1_Result
demo
  (
    const char *name,
    Ring1_Console_Connection* connection
  )
{
  Ring1_Console_Connection_write(connection, "this is console connection `", strlen("this is console connection `"));
  Ring1_Console_Connection_write(connection, name, strlen(name));
  Ring1_Console_Connection_write(connection, "`\n", strlen("`\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_Default);
  Ring1_Console_Connection_write(connection, "  this is text in the default color\n", strlen("  this is text in the default color\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_Gray);
  Ring1_Console_Connection_write(connection, "  this is gray text\n", strlen("  this is gray text\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_White);
  Ring1_Console_Connection_write(connection, "  this is white text\n", strlen("  this is white text\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_DarkYellow);
  Ring1_Console_Connection_write(connection, "  this is dark yellow text\n", strlen("  this is dark yellow text\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_LightYellow);
  Ring1_Console_Connection_write(connection, "  this is light yellow text\n", strlen("  this is light yellow text\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_DarkRed);
  Ring1_Console_Connection_write(connection, "  this is dark red text\n", strlen("  this is dark red text\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_LightRed);
  Ring1_Console_Connection_write(connection, "  this is light red text\n", strlen("  this is light red text\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_DarkGreen);
  Ring1_Console_Connection_write(connection, "  this is dark green text\n", strlen("  this is dark green text\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_LightGreen);
  Ring1_Console_Connection_write(connection, "  this is light green text\n", strlen("  this is light green text\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_DarkBlue);
  Ring1_Console_Connection_write(connection, "  this is dark blue text\n", strlen("  this is dark blue text\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_LightBlue);
  Ring1_Console_Connection_write(connection, "  this is light blue text\n", strlen("  this is light blue text\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_DarkCyan);
  Ring1_Console_Connection_write(connection, "  this is dark cyan text\n", strlen("  this is dark cyan text\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_LightCyan);
  Ring1_Console_Connection_write(connection, "  this is light cyan text\n", strlen("  this is light cyan text\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_DarkMagenta);
  Ring1_Console_Connection_write(connection, "  this is dark magenta text\n", strlen("  this is dark magenta text\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_LightMagenta);
  Ring1_Console_Connection_write(connection, "  this is light magenta text\n", strlen("  this is light magenta text\n"));

  Ring1_Console_Connection_setColor(connection, Ring1_Console_Color_Default);

  return Ring1_Result_Success;
}

int
main
  (
  )
{
  Ring1_Console_ModuleHandle handle = Ring1_Console_ModuleHandle_acquire();
  if (!handle) {
    return EXIT_FAILURE;
  }

  Ring1_Console_Connection* connection = Ring1_Console_getOutputConnection();
  if (!connection) {
    Ring1_Console_ModuleHandle_relinquish(handle);
    handle = Ring1_Console_ModuleHandle_Invalid;
    return EXIT_FAILURE;
  }
  demo("Windows output (default)", connection);
  Ring1_Console_Connection_unref(connection);

  Ring1_Console_ModuleHandle_relinquish(handle);
  handle = Ring1_Console_ModuleHandle_Invalid;

  return EXIT_SUCCESS;
}
