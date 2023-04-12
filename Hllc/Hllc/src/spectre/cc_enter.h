/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */

/// @file spectre/cc_enter.h
/// @author Michael Heilmann
/// @copyright Copyright (c) 2020 Michael Heilmann. All rights reserved.
/// 
/// @brief
/// "enter" phase of the compiler.
/// 
/// @detail
/// "enter" phase of the compiler.
/// - enter builtin symbols
/// - enter type symbols
/// - enter member variable symbols
/// - enter callable symbols
/// 
/// In particular, ensure no two type symbols of the same name exist in a symbol.
/// Ensure no two member symbols exist in a class or enumeration.

#if !defined(CC_ENTER_H_INCLUDED)
#define CC_ENTER_H_INCLUDED


#include "cc_tree.h"
#include "cc_sym.h"
#include "cc_names.h"


BEGIN_DECLARE_COMPONENT(cc_enter)

  cc_arraylist* scratch_list;

  cc_bytebuffer *buffer;

  /// @brief The symbol table.
  cc_syms* syms;

  /// @brief The names.
  cc_spectre_names* names;

END_DECLARE_COMPONENT(cc_enter)

void cc_enter_run(cc_enter* self, cc_program_tree* tree);


#endif // CC_ENTER_H_INCLUDED
