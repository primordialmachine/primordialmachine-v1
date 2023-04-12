#if !defined(CC_EMIT_CLASS_H_INCLUDED)
#define CC_EMIT_CLASS_H_INCLUDED

#include "spectre/cc_emit-protected.h"
#include "spectre/cc_c99_node.h"

/// Create the struct of a class type.
cc_c99_struct_declarator_node*
cc_emit_make_class_type_struct
  (
    cc_emit* self,
    cc_symbol* sym
  );

#endif // CC_EMIT_CLASS_H_INCLUDED
