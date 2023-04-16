// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Common/Diagnostics.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_DIAGNOSTICS_H_INCLUDED)
#define MKX_SCRIBE_DIAGNOSTICS_H_INCLUDED

#if !defined(MKX_SCRIBE_COMMON_PRIVATE)
#error Do not include `Mkx/Scribe/Common/Position.h` directly. Include `Mkx/Scribe/Common.h` instead
#endif

#include "Mkx/Scribe/Common/Position.h"


/// @brief Allows for building a diagnostic message from a non-empty set of expected items, a received item, and a position as well as a message type.
MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Diagnostics);

struct Mkx_Scribe_Diagnostics_Class {
  Machine_Object_Class _parent;
};

struct Mkx_Scribe_Diagnostics {
  Machine_Object _parent;
  /// @brief Pointer to a Mkx_Scribe_Position object or a null pointer.
  Mkx_Scribe_Position *position;
  /// @brief Pointer to a Ring2_String object value denoting the received item or the void value.
  Ring2_String* received;
  /// @brief An Ring2.Collections.ArrayList value.
  /// The elements are Ring2_String objects denoting the expected items.
  Ring2_Collections_HashSet *expected;
  Ring2_String* positionFormatString;
};

void
Mkx_Scribe_Diagnostics_construct
  (
    Mkx_Scribe_Diagnostics* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Create an Mkx_Scribe_Diagnostics object.
/// @param context The context.
/// @return A pointer to the Mkx_Scribe_Diagnostics object.
Mkx_Scribe_Diagnostics*
Mkx_Scribe_Diagnostics_create
  (
  );

/// @brief Set position and received to null pointers, clear the expected set.
/// @param self A pointer to this Mkx_Scribe_Diagnostics object.
void
Mkx_Scribe_Diagnostics_clear
  (
    Mkx_Scribe_Diagnostics* self
  );

/// @brief Set the position.
void
Mkx_Scribe_Diagnostics_setPosition
  (
    Mkx_Scribe_Diagnostics* self,
    Mkx_Scribe_Position* position
  );

/// @brief Set the received item.
void
Mkx_Scribe_Diagnostics_setReceived
  (
    Mkx_Scribe_Diagnostics* self,
    Ring2_String* received
  );

/// @brief Add an expected item.
void
Mkx_Scribe_Diagnostics_addExpected
  (
    Mkx_Scribe_Diagnostics* self,
    Ring2_String* expected
  );

Ring2_String*
Mkx_Scribe_Diagnostics_makeMessage
  (
    Mkx_Scribe_Diagnostics* self
  );

#endif // MKX_SCRIBE_DIAGNOSTICS_H_INCLUDED
