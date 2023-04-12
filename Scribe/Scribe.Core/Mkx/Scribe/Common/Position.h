// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Common/Position.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_POSITION_H_INCLUDED)
#define MKX_SCRIBE_POSITION_H_INCLUDED

#if !defined(MKX_SCRIBE_COMMON_PRIVATE)
#error Do not include `Mkx/Scribe/Common/Position.h` directly. Include `Mkx/Scribe/Common.h` instead
#endif

#include "Mkx/Scribe/Common/Node.h"


/// @brief A position (file (name) and line (number)) in a source code.
MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Position);

struct Mkx_Scribe_Position_Class {
  Machine_Object_Class _parent;
};

struct Mkx_Scribe_Position {
  Machine_Object _parent;
  /// @brief The path (name).
  Ring2_String* pathName;
  /// @brief The line (number).
  Ring2_Integer lineNumber;
};

void
Mkx_Scribe_Position_construct
  (
    Mkx_Scribe_Position *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create an Mkx_Scribe_Position object.
/// @param pathName The path (name).
/// @param lineNumber The line (number).
/// @return A pointer to the Mkx_Scribe_Position object.
Ring1_NoDiscardReturn() Mkx_Scribe_Position *
Mkx_Scribe_Position_create
  (
    Ring2_String* pathName,
    Ring2_Integer lineNumber
  );
  
/// @brief Get the path (name).
/// @param self This position.
/// @return The path (name).
Ring1_NoDiscardReturn() Ring2_String*
Mkx_Scribe_Position_getPathName
  (
	  Mkx_Scribe_Position* self
  );

/// @brief Get the line (number).
/// @param self This position.
/// @return The line (number).
Ring1_NoDiscardReturn() Ring2_Integer
Mkx_Scribe_Position_getLineNumber
  (
    Mkx_Scribe_Position* self
  );

#endif // MKX_SCRIBE_POSITION_H_INCLUDED
