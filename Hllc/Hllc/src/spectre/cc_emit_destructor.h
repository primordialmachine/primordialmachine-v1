#if !defined(CC_EMIT_DESTRUCTOR_H_INCLUDED)
#define CC_EMIT_DESTRUCTOR_H_iNCLUDED


#include "cc_emit-protected.h"
#include "spectre/cc_c99_node.h"


cc_c99_function_declarator_node*
cc_emit_make_object_destructor_declarator
  (
    cc_emit* self,
    cc_symbol* sym
  );

cc_c99_function_declaration_node*
cc_emit_make_object_destructor_declaration
  (
    cc_emit* self,
    cc_symbol* sym
  );

cc_c99_function_definition_node*
cc_emit_make_object_destructor_definition
  (
    cc_emit* self,
    cc_symbol* sym
  );

#endif // CC_EMIT_DESTRUCTOR_H_INCLUDED
