#if !defined(CC_EMIT_CLASS_CONSTRUCTOR_H_INCLUDED)
#define CC_EMIT_CLASS_CONSTRUCTOR_H_INCLUDED


#include "cc_emit-protected.h"
#include "spectre/cc_c99_node.h"


/// Create the function declarator for the class constructor.
cc_c99_function_declarator_node*
cc_emit_make_class_constructor_declarator
  (
    cc_emit* self,
    cc_symbol* sym
  );

/// Create the function declaration for the class constructor.
cc_c99_function_declaration_node*
cc_emit_make_class_constructor_declaration
  (
    cc_emit* self,
    cc_symbol* sym
  );

/// Create the function definition for the class constructor.
cc_c99_function_definition_node*
cc_emit_make_class_constructor_definition
  (
    cc_emit* self,
    cc_symbol* sym
  );

#endif // CC_EMIT_CLASS_CONSTRUCTOR_H_INCLUDED
