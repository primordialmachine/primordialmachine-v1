#include "spectre/cc_emit_class_struct.h"


#include "spectre/cc_c99_node.h"
#include "spectre/c99/names.h"
#include "c99/ast/_include.h"
#include "spectre/c99/type_node.h"
#include "spectre/emit/dispatch.h"


cc_c99_struct_declarator_node* cc_emit_make_class_struct(cc_emit* self, cc_symbol* symbol)
{
  cc_cstring* this_name = cc_emit_compute_name(self, symbol, false);
  cc_cstring_buffer_clear(self->temporary);
  cc_cstring_buffer_append_s(self->temporary, this_name);
  cc_cstring_buffer_append_p(self->temporary, "_class");
  cc_cstring* this_class_name = cc_cstring_buffer_to_string(self->temporary);

  cc_arraylist* STRUCT_BODY = cc_arraylist_create(0);
  cc_c99_struct_declarator_node* STRUCT_DECLARATOR = cc_c99_node_create_struct_declarator(this_class_name);
  STRUCT_DECLARATOR->body = STRUCT_BODY;

  if (symbol->parent)
  {
    cc_cstring* variable_name = self->c99_names->PARENT->string;
    cc_cstring* parent_name = cc_emit_compute_name(self, symbol->parent, false);
    cc_cstring_buffer_clear(self->temporary);
    cc_cstring_buffer_append_s(self->temporary, parent_name);
    cc_cstring_buffer_append_p(self->temporary, "_class");
    parent_name = cc_cstring_buffer_to_string(self->temporary);
    cc_c99_named_type_declarator_node* type_node = cc_c99_node_create_named_type_declarator(parent_name);
    cc_c99_var_declarator_node* variable_node = cc_c99_node_create_var_declarator(variable_name, false, (cc_c99_node*)type_node);
    cc_arraylist_append(STRUCT_BODY, (cc_object*)variable_node);
  }
  else
  {
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: internal error: class has no parent type\n", __FILE__, __LINE__);
    cc_error(CC_EINVAL);
  }

  cc_c99_node* temporary = (cc_c99_node*)cc_emit_get_dispatch_declarations(self, CC_EMIT_DISPATCH_GENERATION_STRATEGY_DEFINITIONS_CLASS_STRUCT, symbol);
  if (temporary) cc_arraylist_append(STRUCT_BODY, (cc_object*)temporary);

  return STRUCT_DECLARATOR;
}
