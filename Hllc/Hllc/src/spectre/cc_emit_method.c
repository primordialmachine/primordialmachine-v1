#include "cc_emit_method.h"


#include "spectre/cc_c99_node.h"
#include "c99/ast/_include.h"


cc_c99_node* cc_emit_method(cc_emit* self, cc_symbol* sym)
{
  bool condition = true;

  condition = condition && ((sym->flags & CC_SYMBOL_FLAGS_METHOD) == CC_SYMBOL_FLAGS_METHOD);

  if (!condition)
  { return NULL; }

  bool is_protected = (sym->flags & CC_SYMBOL_FLAGS_PROTECTED) == CC_SYMBOL_FLAGS_PROTECTED;
  bool is_public = !is_protected;

  if ((self->file_context == CC_CLANG_FILE_CONTEXT_PUBLIC && self->section_context == CC_CLANG_SECTION_CONTEXT_FUNCTION_DECLS && is_public) ||
      (self->file_context == CC_CLANG_FILE_CONTEXT_PROTECTED && self->section_context == CC_CLANG_SECTION_CONTEXT_FUNCTION_DECLS && is_protected))
  {
    // Declare constructors and destructors.
    if (((cc_syms_method*)sym)->override == NULL && (sym->flags & (CC_SYMBOL_FLAGS_CONSTRUCTOR|CC_SYMBOL_FLAGS_DESTRUCTOR)) != 0)
    {
      cc_c99_node* c99_result_type = to_c99_type(self, ((cc_syms_method*)sym)->result);
      cc_c99_params_list_node* c99_params = to_c99_params_list(self, sym, true, true, true);
      cc_cstring* c99_name = cc_emit_compute_name(self, sym, false);
      cc_c99_function_declarator_node* c99_function_declarator = cc_c99_node_create_function_declarator(c99_name, false, c99_result_type, c99_params);
      cc_c99_function_declaration_node* c99_function_declaration = cc_c99_node_create_function_declaration(c99_function_declarator);
      return (cc_c99_node*)c99_function_declaration;
    }
  }
  return NULL;
}
