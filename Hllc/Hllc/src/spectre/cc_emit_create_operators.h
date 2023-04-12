#if !defined(CC_EMIT_CREATE_OPERATORS_H_INCLUDED)
#define CC_EMIT_CREATE_OPERATORS_H_INCLUDED

#include "cc_emit-protected.h"
#include "spectre/cc_c99_node.h"

/// Create the create operators of a class.
cc_c99_group_node* cc_emit_make_create_operators(cc_emit* self, cc_symbol* sym);

#endif // CC_EMIT_CREATE_OPERATORS_H_INCLUDED
