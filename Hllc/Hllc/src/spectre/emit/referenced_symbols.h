/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#if !defined(CC_EMIT_REFERENCED_SYMBOLS_H_INCLUDED)
#define CC_EMIT_REFERENCED_SYMBOLS_H_INCLUDED

#include "spectre/cc_emit-protected.h"

/// @brief Get the symbols referenced in the definition of the specified symbol.
/// @param self This emit stage.
/// @param symbol The specified symbol.
/// @return List of symbols referenced in the definition of the specified symbol. 
cc_arraylist*
cc_emit_get_referenced_symbols
  (
    cc_emit* self,
    cc_symbol* symbol
  );

#endif
