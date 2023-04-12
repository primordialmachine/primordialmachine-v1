#include "spectre/cc_emit_constructors.h"


#include "spectre/cc_emit.h"
#include "spectre/c99/names.h"
#include "spectre/cc_c99_node.h"
#include "c99/ast/_include.h"
#include "spectre/c99/type_node.h"


bool enabled(cc_emit* self, cc_symbol* sym)
{
  bool condition = true;
  
  // Must be a constructor.
  condition = condition && (sym->flags & CC_SYMBOL_FLAGS_CONSTRUCTOR) == CC_SYMBOL_FLAGS_CONSTRUCTOR;
  // visibility must be "public" and section must be "public header file" OR
  // visibility must be "protected" and section must be "protected header file".
  condition = condition && 
              ((self->file_context == CC_CLANG_FILE_CONTEXT_PROTECTED && (sym->flags & CC_SYMBOL_FLAGS_PROTECTED) == CC_SYMBOL_FLAGS_PROTECTED) ||
               (self->file_context == CC_CLANG_FILE_CONTEXT_PUBLIC && (sym->flags & CC_SYMBOL_FLAGS_PROTECTED) == 0));
  condition = condition && (self->section_context == CC_CLANG_SECTION_CONTEXT_FUNCTION_DECLS);
  return condition;
}

cc_c99_node* cc_emit_constructor(cc_emit* self, cc_symbol* sym)
{
  if (!enabled(self, sym))
  { return NULL; }

  cc_symbol* enclosing = sym->enclosing;
  cc_cstring* name = cc_emit_compute_name(self, enclosing, false);

  cc_c99_named_type_declarator_node* f_return_type = cc_c99_node_create_named_type_declarator(self->c99_names->BOOLEAN->string);
  cc_cstring_buffer_clear(self->temporary);
  cc_cstring_buffer_append_s(self->temporary, name);
  cc_cstring_buffer_append_p(self->temporary, "_construct");
  if (((cc_syms_constructor*)sym)->suffix)
  {
    cc_cstring_buffer_append_p(self->temporary, "_");
    cc_cstring_buffer_append_s(self->temporary, ((cc_syms_constructor*)sym)->suffix);
  }
  cc_cstring* f_name = cc_cstring_buffer_to_string(self->temporary);
  cc_c99_params_list_node* c99_params_list = to_c99_params_list(self, sym, true, true, true);
  cc_c99_function_declarator_node* c99_function_declarator = cc_c99_node_create_function_declarator(f_name, false, (cc_c99_node*)f_return_type, c99_params_list);
  cc_c99_function_declaration_node* c99_function_declaration = cc_c99_node_create_function_declaration(c99_function_declarator);
  return (cc_c99_node*)c99_function_declaration;
}
