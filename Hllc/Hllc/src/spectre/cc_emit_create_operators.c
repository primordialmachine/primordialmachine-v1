#include "spectre/cc_emit_create_operators.h"


#include "spectre/cc_c99_node.h"
#include "spectre/c99/names.h"
#include "c99/ast/_include.h"
#include "c99/ast/returnstat_node.h"
#include "c99/ast/ifstat_node.h"
#include "spectre/c99/type_node.h"


/// Create the function definition of a create operator.
cc_c99_function_definition_node*
cc_emit_make_create_operator_definition
  (
    cc_emit* self,
    cc_symbol* sym
  );

/// Create the function declarator of a create operator.
cc_c99_function_declarator_node*
cc_emit_make_create_operator_declarator
  (
    cc_emit* self,
    cc_symbol* sym
  );

static cc_arraylist*
make_constructor_call_arguments
  (
    cc_emit* self,
    cc_symbol* sym
  )
{
  cc_arraylist* l = cc_arraylist_create(0);
  cc_arraylist_append(l, (cc_object *)cc_c99_nameexp_node_create(self->names->SELF->string));
  cc_arraylist* parameters = ((cc_syms_constructor*)sym)->parameters;
  for (size_t i = 0, n = cc_arraylist_get_size(parameters); i < n; ++i)
  {
    cc_symbol* parameter = (cc_symbol*)cc_arraylist_get_at(parameters, i);
    cc_arraylist_append(l, (cc_object *)cc_c99_nameexp_node_create(parameter->name));
  }
  return l;
}

static cc_cstring *
make_constructor_name
  (
    cc_emit* self,
    cc_symbol* sym
  )
{
  cc_cstring* name = cc_emit_compute_name(self, sym->enclosing, false);
  cc_cstring_buffer_clear(self->temporary);
  cc_cstring_buffer_append_s(self->temporary, name);
  cc_cstring_buffer_append_p(self->temporary, "_construct");
  if (((cc_syms_constructor*)sym)->suffix)
  {
    cc_cstring_buffer_append_p(self->temporary, "_");
    cc_cstring_buffer_append_s(self->temporary, ((cc_syms_constructor*)sym)->suffix);
  }
  return cc_cstring_buffer_to_string(self->temporary);
}

cc_c99_function_definition_node *
cc_emit_make_create_operator_definition
  (
    cc_emit* self,
    cc_symbol* sym
  )
{
  cc_c99_function_declarator_node* DECLARATOR = cc_emit_make_create_operator_declarator(self, sym);

  cc_cstring* name = cc_emit_compute_name(self, sym->enclosing, false);
  cc_cstring* call_name = make_constructor_name(self, sym);
  cc_arraylist* call_args = make_constructor_call_arguments(self, sym);
  cc_c99_node* ctrl_expr = (cc_c99_node*)cc_c99_callexp_node_create((cc_c99_node*)cc_c99_nameexp_node_create(call_name), call_args);
  ctrl_expr = (cc_c99_node*)cc_c99_unexp_node_create(CC_C99_UNOP_NOT, (cc_c99_node*)ctrl_expr);

  cc_c99_group_node* BODY = cc_c99_node_create_group_node();

  cc_cstring_buffer_clear(self->temporary);
  cc_cstring_buffer_append_p(self->temporary, "ALLOCATE_OBJECT");
  cc_cstring_buffer_append_p(self->temporary, "(");
  cc_cstring_buffer_append_s(self->temporary, name);
  cc_cstring_buffer_append_p(self->temporary, ");");
  cc_c99_text_line_node* text_line = cc_c99_node_create_text_line(cc_cstring_buffer_to_string(self->temporary));
  cc_c99_group_node_append(BODY, (cc_c99_node*)text_line);

  cc_c99_blockstat_node* block_stat = cc_c99_blockstat_node_create();
  cc_c99_node* temporary;
  temporary = (cc_c99_node*)cc_c99_node_create_text_line(cc_cstring_create("g_object_unref(G_CAST(g_object, self));"));
  cc_c99_blockstat_node_append(block_stat, temporary);
  temporary = (cc_c99_node*)cc_c99_returnstat_node_create((cc_c99_node*)cc_c99_nameexp_node_create(self->c99_names->REFERENCE_NULL_VALUE->string));
  cc_c99_blockstat_node_append(block_stat, temporary);

  temporary = (cc_c99_node*)cc_c99_ifstat_node_create((cc_c99_node*)ctrl_expr, (cc_c99_node*)block_stat);
  cc_c99_group_node_append(BODY, (cc_c99_node*)temporary);

  temporary = (cc_c99_node*)cc_c99_returnstat_node_create((cc_c99_node*)cc_c99_nameexp_node_create(self->names->SELF->string));
  cc_c99_group_node_append(BODY, temporary);

  DECLARATOR->body = BODY;

  cc_c99_function_definition_node* DEFINITION = cc_c99_node_create_function_definition(DECLARATOR);

  return DEFINITION;
}

cc_c99_function_declarator_node *
cc_emit_make_create_operator_declarator
  (
    cc_emit* self,
    cc_symbol* sym
  )
{
  // Compute <fully-qualified-name>_create_<suffix>.
  cc_cstring* c99_name = cc_emit_compute_name(self, sym->enclosing, false);
  cc_cstring_buffer* buffer = self->temporary;
  cc_cstring_buffer_clear(buffer);
  cc_cstring_buffer_append_s(buffer, c99_name);
  cc_cstring_buffer_append_p(buffer, "_create");
  if (((cc_syms_constructor*)sym)->suffix)
  {
    cc_cstring_buffer_append_p(buffer, "_");
    cc_cstring_buffer_append_s(buffer, ((cc_syms_constructor*)sym)->suffix);
  }
  c99_name = cc_cstring_buffer_to_string(buffer);
  cc_c99_params_list_node* c99_params_list = to_c99_params_list(self, sym, false, true, true);
  cc_c99_node* c99_result_type = (cc_c99_node*)to_c99_type(self, sym->enclosing);
  cc_c99_function_declarator_node* c99_function_declarator = cc_c99_node_create_function_declarator(c99_name, false, c99_result_type, c99_params_list);

  return c99_function_declarator;
}

static cc_c99_node* cc_emit_write_create_operator(cc_emit* self, cc_symbol* sym)
{
  if (self->file_context == CC_CLANG_FILE_CONTEXT_FOOTER_INLAY)
  {
    cc_c99_function_definition_node* DEFINITION = cc_emit_make_create_operator_definition(self, sym);
    return (cc_c99_node *)DEFINITION;
  }
  else if (self->file_context == CC_CLANG_FILE_CONTEXT_PUBLIC && (sym->flags & CC_SYMBOL_FLAGS_PROTECTED) == 0)
  {
    cc_c99_function_declarator_node *DECLARATOR = cc_emit_make_create_operator_declarator(self, sym);
    cc_c99_function_declaration_node* DECLARATION = cc_c99_node_create_function_declaration(DECLARATOR);
    return (cc_c99_node*)DECLARATION;
  }
  else if (self->file_context == CC_CLANG_FILE_CONTEXT_PROTECTED && (sym->flags & CC_SYMBOL_FLAGS_PROTECTED) == CC_SYMBOL_FLAGS_PROTECTED)
  {
    cc_c99_function_declarator_node* DECLARATOR = cc_emit_make_create_operator_declarator(self, sym);
    cc_c99_function_declaration_node* DECLARATION = cc_c99_node_create_function_declaration(DECLARATOR);
    return (cc_c99_node*)DECLARATION;
  }
  else
  {
    return NULL;
  }
}

static bool condition(cc_emit* self, cc_symbol* sym)
{
  bool condition = true;

  // Must be a non-abstract class symbol.
  condition = condition && (sym->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS;
  condition = condition && (sym->flags & CC_SYMBOL_FLAGS_ABSTRACT) == 0;

  // file context must be either "public file", "protected file", or "footer inlay file".
  condition = condition &&
    ((self->file_context == CC_CLANG_FILE_CONTEXT_FOOTER_INLAY) || (self->file_context == CC_CLANG_FILE_CONTEXT_PUBLIC) || (self->file_context == CC_CLANG_FILE_CONTEXT_PROTECTED));

  return condition;
}

cc_c99_group_node * cc_emit_make_create_operators(cc_emit* self, cc_symbol* sym)
{
  if (!condition(self, sym))
  { return NULL; }

  cc_c99_group_node* GROUP = cc_c99_node_create_group_node();
  for (size_t i = 0, n = cc_arraylist_get_size(sym->enclosed); i < n; ++i)
  {
    cc_symbol* child = (cc_symbol*)cc_arraylist_get_at(sym->enclosed, i);
    if (cc_symbol_is_constructor(child))
    {
      cc_c99_node* node = cc_emit_write_create_operator(self, child);
      if (node) cc_c99_group_node_append(GROUP, node);
    }
  }
  return GROUP;
}
