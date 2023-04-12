#include "spectre/cc_emit_destructor.h"

#include "spectre/cc_c99_node.h"
#include "c99/ast/_include.h"
#include "spectre/c99/type_node.h"

static cc_syms_destructor*
find_destructor
(
  cc_emit* self,
  cc_symbol* sym
)
{
  for (size_t i = 0, n = cc_arraylist_get_size(sym->enclosed); i < n; ++i)
  {
    cc_symbol* child_sym = (cc_symbol*)cc_arraylist_get_at(sym->enclosed, i);
    if (cc_symbol_is_destructor(child_sym))
    {
      return (cc_syms_destructor*)child_sym;
    }
  }
  return NULL;
}

static cc_c99_group_node*
make_body
  (
    cc_emit* self,
    cc_symbol* sym
  )
{
  bool warn = false;
  cc_c99_group_node* group_node = cc_c99_node_create_group_node();
  for (size_t i = 0, n = cc_arraylist_get_size(sym->enclosed); i < n; ++i)
  {
    cc_symbol* child_sym = (cc_symbol*)cc_arraylist_get_at(sym->enclosed, i);
    if ((child_sym->flags & CC_SYMBOL_FLAGS_MEMBER_VARIABLE) == CC_SYMBOL_FLAGS_MEMBER_VARIABLE)
    {
      cc_symbol* type = child_sym->type;
      if (cc_symbol_is_class(type))
      {
        cc_cstring_buffer_clear(self->temporary);
        cc_cstring_buffer_append_p(self->temporary, "G_VAR_SET");
        cc_cstring_buffer_append_p(self->temporary, "(self->");
        cc_cstring_buffer_append_s(self->temporary, child_sym->name);
        cc_cstring_buffer_append_p(self->temporary, ",");
        cc_cstring_buffer_append_p(self->temporary, " ");
        cc_cstring_buffer_append_p(self->temporary, "NULL");
        cc_cstring_buffer_append_p(self->temporary, ")");
        cc_cstring_buffer_append_p(self->temporary, ";");
        cc_c99_group_node_append(group_node, (cc_c99_node*)cc_c99_node_create_text_line(cc_cstring_buffer_to_string(self->temporary)));
      }
      else if (cc_symbol_is_scalar(type) || cc_symbol_is_enumeration(type))
      {

      }
      else
      {
        warn = true;
      }
    }
  }
  if (warn)
  {
    // TODO: Should be part of the semantic analysis stage.
    cc_print_f(CC_PRINT_FLAG_USER | CC_PRINT_FLAG_ERROR, "unable to generated destructor for class %s - please mark the destructor as 'foreign' and implement manually\n", sym->qualified_name->string->p);
    return NULL;
  }
  return group_node;
}

cc_c99_function_declarator_node*
cc_emit_make_object_destructor_declarator
  (
    cc_emit* self,
    cc_symbol* sym
  )
{
  if (!cc_symbol_is_class(sym))
  {
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: symbol is not a class symbol\n", __FILE__, __LINE__);
    cc_error(CC_EINVAL);
  }

  cc_syms_destructor* destructor = find_destructor(self, sym);
  if (!destructor)
  {
    cc_print_f(CC_PRINT_FLAG_USER | CC_PRINT_FLAG_ERROR, "%s:%d: unable to generated destructor for class %s - missing destructor definition\n", __FILE__, __LINE__, sym->qualified_name->string->p);
    cc_error(CC_EINVAL);
  }

  cc_cstring* c99_self_name, * c99_function_name;
  cc_c99_node* c99_self_type, * c99_return_type;
  cc_c99_node* c99_self_param;
  cc_c99_params_list_node* c99_params_list;
  cc_c99_function_declarator_node* c99_function_node;

  cc_cstring* type_name = cc_emit_compute_name(self, sym, false);

  // object destructor
  cc_cstring_buffer_clear(self->temporary);
  cc_cstring_buffer_append_s(self->temporary, type_name);
  cc_cstring_buffer_append_p(self->temporary, "_destruct");
  c99_function_name = cc_cstring_buffer_to_string(self->temporary);

  c99_return_type = (cc_c99_node*)cc_c99_node_create_named_type_declarator(self->names->VOID->string);

  c99_self_name = self->names->SELF->string;
  c99_self_type = (cc_c99_node*)cc_c99_node_create_pointer_type_declarator((cc_c99_node*)cc_c99_node_create_named_type_declarator(type_name));
  c99_self_param = (cc_c99_node*)cc_c99_node_create_param(c99_self_name, c99_self_type, true, false);

  c99_params_list = cc_c99_node_create_params_list(true);
  cc_arraylist_append(c99_params_list->params, (cc_object*)c99_self_param);

  c99_function_node = cc_c99_node_create_function_declarator(c99_function_name, true, c99_return_type, c99_params_list);

  if ((((cc_symbol*)destructor)->flags & CC_SYMBOL_FLAGS_FOREIGN) == 0)
  {
    c99_function_node->body = make_body(self, sym);
  }

  return c99_function_node;
}

cc_c99_function_declaration_node*
cc_emit_make_object_destructor_declaration
  (
    cc_emit* self,
    cc_symbol* sym
  )
{
  cc_c99_function_declarator_node *declarator = cc_emit_make_object_destructor_declarator(self, sym);
  cc_c99_function_declaration_node *declaration = cc_c99_node_create_function_declaration(declarator);
  return declaration;
}

cc_c99_function_definition_node*
cc_emit_make_object_destructor_definition
  (
    cc_emit* self,
    cc_symbol* sym
  )
{
  cc_c99_function_declarator_node* declarator = cc_emit_make_object_destructor_declarator(self, sym);
  if (declarator->body)
  {
    cc_c99_function_definition_node* definition = cc_c99_node_create_function_definition(declarator);
    return definition;
  }
  else
  {
    return NULL;
  }
}
