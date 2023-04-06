/// @file Ring3/Gdl/Lexical/Scanner.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_LEXICAL_SCANNER_H_INCLUDED)
#define RING3_GDL_LEXICAL_SCANNER_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Lexical/Scanner.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/Configuration.h"
#include "Ring3/Gdl/Lexical/Token.h"

MACHINE_DECLARE_INTERFACETYPE(Ring3_Gdl_Scanner)

struct Ring3_Gdl_Scanner_Dispatch {
  Machine_InterfaceDispatch parent;
  
  /// @brief Set the input for this GDL scanner.
  /// @param self This GDL scanner.
  /// @param inputName The name of the input.
  /// @param inputBytes The Bytes of the input.
  /// @post The GDL scanner is in its initial state w.r.t. the specified input.
  void
  (*setInput)
    (
      Ring3_Gdl_Scanner* self,
      Ring2_String* inputName,
      Ring2_ByteBuffer* inputBytes
    );
    
  /// @brief Compute the next token.
  /// @param self This scanner.
  void
  (*step)
    (
      Ring3_Gdl_Scanner* self
    );
  
  /// @brief Get the current token of this scanner.
  /// @param self This scanner.
  /// @return The current token of this scanner.
  Ring1_NoDiscardReturn() Ring3_Gdl_Token*
  (*getToken)
    (
      Ring3_Gdl_Scanner const* self
    );

};

/// @brief Set the input.
/// @param self This GDL scanner.
/// @param inputName The name of the input.
/// @param inputBytes The Bytes of the input.
/// @post The GDL scanner is in its initial state w.r.t. the specified input.
void
Ring3_Gdl_Scanner_setInput
  (
    Ring3_Gdl_Scanner* self,
    Ring2_String* inputName,
    Ring2_ByteBuffer* inputBytes
  );

/// @brief Compute the next token.
/// @param self This GDL scanner.
void
Ring3_Gdl_Scanner_step
  (
    Ring3_Gdl_Scanner* self
  );

/// @brief Get the current token.
/// @param self This GDL scanner.
/// @return The current token.
Ring1_NoDiscardReturn() Ring3_Gdl_Token*
Ring3_Gdl_Scanner_getToken
  (
    Ring3_Gdl_Scanner const* self
  );

#endif // RING3_GDL_LEXICAL_SCANNER_H_INCLUDED
