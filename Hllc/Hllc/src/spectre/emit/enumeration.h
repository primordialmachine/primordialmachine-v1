#if !defined(CC_EMIT_ENUMERATION_H_INCLUDED)
#define CC_EMIT_ENUMERATION_H_INCLUDED

#include "spectre/cc_emit-protected.h"
#include "spectre/cc_c99_node.h"

/// Create the enum of an enumeration type.
cc_c99_enum_declarator_node*
cc_emit_make_enumeration_type_enum
  (
    cc_emit* self,
    cc_symbol* sym
  );

#endif // CC_EMIT_ENUMERATION_H_INCLUDED
