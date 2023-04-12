#if !defined(CC_EMIT_CLASS_STRUCT_H_INCLUDED)
#define CC_EMIT_CLASS_STRUCT_H_INCLUDED

#include "cc_emit-protected.h"
#include "spectre/cc_c99_node.h"
typedef struct cc_c99_named_type_declarator_node cc_c99_named_type_declarator_node;

cc_c99_struct_declarator_node* cc_emit_make_class_struct(cc_emit* self, cc_symbol* symbol);

#endif // CC_EMIT_CLASS_STRUCT_H_INCLUDED
