/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */

/// @file spectre/cc_resolve.h
/// @author Michael Heilmann
/// @copyright Copyright (c) 2020 Michael Heilmann. All rights reserved.
/// 
/// @brief
/// "resolve" phase of the compiler.
/// 
/// @details
/// "resolve" phase of the compiler.
/// 1st iteration:
/// - for any member variable or parameter variable
///   - resolve type
/// - for any class symbol except of g.object:
///   - ensure class extends exactly one parent class
///   - resolve parent class
/// 2nd iteration:
/// - for any method:
///   of which method is that method an override of.

#if !defined(CC_RESOLVE_H_INCLUDED)
#define CC_RESOLVE_H_INCLUDED

#include "cc_sym.h"

BEGIN_DECLARE_COMPONENT(cc_resolve)

  cc_syms* syms;

  cc_spectre_names* names;

  cc_tree_factory* tree_factory;

  /// @brief The modifier literal "out".
  cc_name* OUT;

END_DECLARE_COMPONENT(cc_resolve)

void cc_resolve_run(cc_resolve *self);


#endif // CC_RESOLVE_H_INCLUDED
