#include "spectre/cc_emit_class_constructor.h"


#include "spectre/cc_emit.h"
#include "spectre/c99/names.h"
#include "spectre/cc_c99_node.h"
#include "c99/ast/_include.h"
#include "spectre/c99/type_node.h"


static bool condition(cc_emit* self, cc_symbol* sym)
{
  bool condition = true;
  condition = condition && ((self->file_context == CC_CLANG_FILE_CONTEXT_FOOTER_INLAY));
  condition = condition && ((sym->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS);
  return condition;
}

/// @brief Get the base method of which the specified method is an override of (transitive).
/// @param symbol The method symbol. 
/// @return The base method if any, the method itself otherwise.
static cc_symbol* get_base(cc_symbol* symbol)
{
  cc_symbol* base = ((cc_syms_method*)symbol)->override;
  if (base != NULL)
  {
    while (((cc_syms_method*)base)->override)
    {
      base = ((cc_syms_method*)base)->override;
    }
  }
  if (base == NULL)
  {
    base = symbol;
  }
  return base;
}

// @todo Later versions: Precompute once and store in per-symbol emission data.
static cc_cstring* get_class_constructor_name(cc_emit* self, cc_symbol* symbol)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(symbol);
  if ((symbol->flags & CC_SYMBOL_FLAGS_CLASS) == 0)
  {
    cc_error(CC_EINVAL);
  }
  cc_cstring* name;
  name = cc_emit_compute_name(self, symbol, false);
  cc_cstring_buffer_clear(self->temporary);
  cc_cstring_buffer_append_s(self->temporary, name);
  cc_cstring_buffer_append_p(self->temporary, "_class_construct");
  return cc_cstring_buffer_to_string(self->temporary);
}

// @todo Later versions: Precompute once and store in per-symbol emission data.
static cc_cstring* get_class_struct_name(cc_emit* self, cc_symbol* symbol)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(symbol);
  if ((symbol->flags & CC_SYMBOL_FLAGS_CLASS) == 0)
  {
    cc_error(CC_EINVAL);
  }
  cc_cstring* name;
  name = cc_emit_compute_name(self, symbol, false);
  cc_cstring_buffer_clear(self->temporary);
  cc_cstring_buffer_append_s(self->temporary, name);
  cc_cstring_buffer_append_p(self->temporary, "_class");
  return cc_cstring_buffer_to_string(self->temporary);
}

cc_c99_function_declarator_node *
cc_emit_make_class_constructor_declarator
  (
    cc_emit* self,
    cc_symbol* sym
  )
{
  cc_cstring* c99_function_name = get_class_constructor_name(self, sym);
  cc_c99_named_type_declarator_node* c99_return_type = cc_c99_node_create_named_type_declarator(self->c99_names->VOID->string);
  cc_c99_params_list_node* c99_params_list = cc_c99_node_create_params_list(true);

  cc_cstring* c99_self_name = self->names->SELF->string;

  cc_c99_node* c99_self_type = (cc_c99_node*)cc_c99_node_create_named_type_declarator(get_class_struct_name(self, sym));
  c99_self_type = (cc_c99_node*)cc_c99_node_create_pointer_type_declarator(c99_self_type);
  cc_c99_param_node* c99_self_param = cc_c99_node_create_param(c99_self_name, (cc_c99_node*)c99_self_type, true, false);
  cc_arraylist_append(c99_params_list->params, (cc_object*)c99_self_param);
  cc_c99_function_declarator_node* c99_function_declarator = cc_c99_node_create_function_declarator(c99_function_name, true, (cc_c99_node*)c99_return_type, c99_params_list);

  cc_c99_group_node* body = cc_c99_node_create_group_node();
  c99_function_declarator->body = body;
  for (size_t i = 0, n = cc_arraylist_get_size(sym->enclosed); i < n; ++i)
  {
    cc_symbol* method = (cc_symbol*)cc_arraylist_get_at(sym->enclosed, i);
    if ((method->flags & CC_SYMBOL_FLAGS_METHOD) == CC_SYMBOL_FLAGS_METHOD &&
      (method->flags & CC_SYMBOL_FLAGS_ABSTRACT) == 0 &&
      (method->flags & CC_SYMBOL_FLAGS_STATIC) == 0)
    {
      cc_symbol* override = get_base(method);
      if ((override->flags & CC_SYMBOL_FLAGS_SEALED) == 0)
      {
        // Basically `'G_CAST' '('<base class name> ',' self)-><method name> '=' '(' <base method pointer> ')' '&' <method name> ';'`.
        cc_c99_node* LHS = (cc_c99_node*)cc_c99_node_create_pointer_type_declarator((cc_c99_node*)cc_c99_node_create_named_type_declarator(get_class_struct_name(self, override->enclosing)));
        LHS = (cc_c99_node*)cc_c99_castexp_node_create(LHS, (cc_c99_node*)cc_c99_nameexp_node_create(self->names->SELF->string));
        LHS = (cc_c99_node*)cc_c99_unexp_node_create(CC_C99_UNOP_GROUP, LHS);
        LHS = (cc_c99_node*)cc_c99_binexp_node_create(CC_C99_BINOP_STRUCTURE_DEREFERENCE, LHS, (cc_c99_node*)cc_c99_nameexp_node_create(method->name));

        cc_c99_node* RHS = (cc_c99_node*)cc_c99_unexp_node_create(CC_C99_UNOP_ADDRESS_OF, (cc_c99_node*)cc_c99_nameexp_node_create(method->name));
        if (override != method)
        {
          cc_c99_node* c99_result_type = to_c99_type(self, ((cc_syms_method*)override)->result);
          cc_c99_params_list_node* c99_params = to_c99_params_list(self, override, true, true, true);
          cc_cstring* c99_name = override->name;
          cc_c99_function_declarator_node* c99_function_declarator_2 = cc_c99_node_create_function_declarator(c99_name, false, c99_result_type, c99_params);
          cc_c99_function_type_declarator_node* c99_function_type_declarator = cc_c99_node_create_function_type_declarator(c99_function_declarator_2);
          cc_c99_pointer_type_declarator_node* c99_pointer_type_declarator = cc_c99_node_create_pointer_type_declarator((cc_c99_node*)c99_function_type_declarator);

          RHS = (cc_c99_node*)cc_c99_castexp_node_create((cc_c99_node*)c99_pointer_type_declarator, (cc_c99_node*)RHS);
        }
        cc_c99_node* ASSIGN = (cc_c99_node*)cc_c99_binexp_node_create(CC_C99_BINOP_ASSIGN, LHS, RHS);
        cc_c99_node* ASSIGN_STAT = (cc_c99_node*)cc_c99_expstat_node_create(ASSIGN);
        cc_c99_group_node_append(body, ASSIGN_STAT);

      }
    }
  }
  return c99_function_declarator;
}

cc_c99_function_declaration_node*
cc_emit_make_class_constructor_declaration
  (
    cc_emit* self,
    cc_symbol* sym
  )
{
  cc_c99_function_declarator_node* declarator = cc_emit_make_class_constructor_declarator(self, sym);
  cc_c99_function_declaration_node* declaration = cc_c99_node_create_function_declaration(declarator);
  return declaration;
}


cc_c99_function_definition_node *
cc_emit_make_class_constructor_definition
  (
    cc_emit* self,
    cc_symbol* sym
  )
{
  if (!condition(self, sym))
  { return NULL; }

  cc_c99_function_declarator_node* declarator = cc_emit_make_class_constructor_declarator(self, sym);
  cc_c99_function_definition_node* definition = cc_c99_node_create_function_definition(declarator);
  return definition;
}
