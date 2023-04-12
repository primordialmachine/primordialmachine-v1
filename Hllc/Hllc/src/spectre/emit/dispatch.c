#include "spectre/emit/dispatch.h"


#include "spectre/cc_c99_node.h"
#include "c99/ast/_include.h"
#include "spectre/c99/type_node.h"
#include "spectre/c99/names.h"


/// @todo Rename to is_class_member.
static bool is_defined_in_class(cc_symbol* symbol)
{
  return (symbol->enclosing->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS;
}

static bool is_override(cc_symbol* symbol)
{
  return ((cc_syms_method*)symbol)->override;
}

static bool is_static(cc_symbol* symbol)
{
  return (symbol->flags & CC_SYMBOL_FLAGS_STATIC) == CC_SYMBOL_FLAGS_STATIC;
}

static bool is_sealed(cc_symbol* symbol)
{
  return (symbol->flags & CC_SYMBOL_FLAGS_SEALED) == CC_SYMBOL_FLAGS_SEALED;
}

static bool is_abstract(cc_symbol* symbol)
{
  return (symbol->flags & CC_SYMBOL_FLAGS_ABSTRACT) == CC_SYMBOL_FLAGS_ABSTRACT;
}

static bool is_protected(cc_symbol* symbol)
{
  return (symbol->flags & CC_SYMBOL_FLAGS_PROTECTED) == CC_SYMBOL_FLAGS_PROTECTED;
}

static bool is_public(cc_symbol* symbol)
{
  return !is_protected(symbol);
}

static cc_cstring* get_default_value(cc_emit* self, cc_symbol* sym)
{
#define DEFINE(NAME) \
    else if (sym == self->symbols->NAME) \
    { return self->c99_names->NAME##_DEFAULT_VALUE->string; }

  if (false)
  { }

  DEFINE(BOOLEAN)
  DEFINE(INTEGER)
  DEFINE(NATURAL)

  DEFINE(INTEGER8)
  DEFINE(INTEGER16)
  DEFINE(INTEGER32)
  DEFINE(INTEGER64)

  DEFINE(NATURAL8)
  DEFINE(NATURAL16)
  DEFINE(NATURAL32)
  DEFINE(NATURAL64)

  DEFINE(SIZE)

  else
  {
    if ((sym->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS)
    {
      return self->c99_names->REFERENCE_DEFAULT_VALUE->string;
    }
    else if ((sym->flags & CC_SYMBOL_FLAGS_ENUMERATION) == CC_SYMBOL_FLAGS_ENUMERATION)
    {
      return self->c99_names->INTEGER_DEFAULT_VALUE->string;
    }
    else if ((sym->flags & CC_SYMBOL_FLAGS_INTERFACE) == CC_SYMBOL_FLAGS_INTERFACE)
    {
      return self->c99_names->REFERENCE_DEFAULT_VALUE->string;
    }
    else
    {
      return NULL;
    }
  }
}

static cc_c99_node* make_wrapper_defn(cc_emit* self, cc_symbol* sym)
{
  cc_c99_node* c99_result_type = to_c99_type(self, ((cc_syms_method*)sym)->result);
  cc_c99_params_list_node* c99_params = to_c99_params_list(self, sym, true, true, true);
  cc_cstring* c99_name = cc_emit_compute_name(self, sym, false);
  cc_c99_function_declarator_node* c99_function_declarator = cc_c99_node_create_function_declarator(c99_name, false, c99_result_type, c99_params);
  cc_c99_function_definition_node* c99_function_definition = cc_c99_node_create_function_definition(c99_function_declarator);

  cc_c99_group_node* BODY = cc_c99_node_create_group_node();
  
  cc_c99_nameexp_node* fun;
  if (((cc_syms_method*)sym)->result != self->symbols->VOID)
  {
    fun = cc_c99_nameexp_node_create(self->c99_names->G_VIRTUALCALL->string);
  }
  else
  {
    fun = cc_c99_nameexp_node_create(self->c99_names->G_VIRTUALCALL_NO_RESULT->string);
  }
  
  cc_arraylist* args = cc_arraylist_create(0);

  cc_arraylist_append(args, (cc_object *)cc_c99_nameexp_node_create(cc_emit_compute_name(self, sym->enclosing, false)));
  cc_arraylist_append(args, (cc_object*)cc_c99_nameexp_node_create(sym->name));
  if (((cc_syms_method*)sym)->result != self->symbols->VOID)
  {
    cc_arraylist_append(args, (cc_object *)cc_c99_nameexp_node_create(get_default_value(self, ((cc_syms_method*)sym)->result)));
  }
  for (size_t i = 0, n = cc_arraylist_get_size(c99_params->params); i < n; ++i)
  {
    cc_c99_param_node* param = (cc_c99_param_node *)cc_arraylist_get_at(c99_params->params, i);
    cc_arraylist_append(args, (cc_object *)cc_c99_nameexp_node_create(param->name));
  }
  cc_c99_node* CALL = (cc_c99_node *)cc_c99_callexp_node_create((cc_c99_node *)fun, args);
  CALL = (cc_c99_node*)cc_c99_expstat_node_create(CALL);
  cc_c99_group_node_append(BODY, (cc_c99_node *)CALL);

  c99_function_declarator->body = BODY;

  return (cc_c99_node*)c99_function_definition;
}

static cc_c99_node* make_wrapper_decl(cc_emit* self, cc_symbol *sym)
{
  cc_c99_node* c99_result_type = to_c99_type(self, ((cc_syms_method*)sym)->result);
  cc_c99_params_list_node* c99_params = to_c99_params_list(self, sym, true, true, true);
  cc_cstring* c99_name = cc_emit_compute_name(self, sym, false);
  cc_c99_function_declarator_node* c99_function_declarator = cc_c99_node_create_function_declarator(c99_name, false, c99_result_type, c99_params);
  cc_c99_function_declaration_node* c99_function_declaration = cc_c99_node_create_function_declaration(c99_function_declarator);
  return (cc_c99_node*)c99_function_declaration;
}

cc_c99_group_node*
cc_emit_get_dispatch_declarations
  (
    cc_emit* self,
    cc_emit_dispatch_generation_strategy strategy,
    cc_symbol* symbol
  )
{
  cc_c99_group_node* group_node = cc_c99_node_create_group_node();

  switch (strategy)
  {
  case CC_EMIT_DISPATCH_GENERATION_STRATEGY_DEFINITIONS_CLASS_STRUCT:
  {
    for (size_t i = 0, n = cc_arraylist_get_size(symbol->enclosed); i < n; ++i)
    {
      cc_symbol* child_symbol = (cc_symbol*)cc_arraylist_get_at(symbol->enclosed, i);
      if ((child_symbol->flags & CC_SYMBOL_FLAGS_METHOD) == CC_SYMBOL_FLAGS_METHOD)
      {
        if (!is_static(child_symbol) && !is_override(child_symbol) && !is_sealed(child_symbol))
        {
          cc_c99_node* c99_result_type = to_c99_type(self, ((cc_syms_method*)child_symbol)->result);
          cc_c99_params_list_node* c99_params = to_c99_params_list(self, child_symbol, true, true, true);
          cc_cstring* c99_name = child_symbol->name;
          cc_c99_function_declarator_node* c99_function_declarator = cc_c99_node_create_function_declarator(c99_name, false, c99_result_type, c99_params);
          cc_c99_function_type_declarator_node* c99_function_type_declarator = cc_c99_node_create_function_type_declarator(c99_function_declarator);
          cc_c99_pointer_type_declarator_node* c99_pfunction = cc_c99_node_create_pointer_type_declarator((cc_c99_node*)c99_function_type_declarator);
          cc_c99_var_declarator_node* c99_var_decl = cc_c99_node_create_var_declarator(c99_name, false, (cc_c99_node*)c99_pfunction);
          cc_c99_group_node_append(group_node, (cc_c99_node *)c99_var_decl);
        }
      }
    }
  } break;
  case CC_EMIT_DISPATCH_GENERATION_STRATEGY_DECLARATIONS_HEADER_INLAY:
  {
    for (size_t i = 0, n = cc_arraylist_get_size(symbol->enclosed); i < n; ++i)
    {
      cc_symbol* child_symbol = (cc_symbol*)cc_arraylist_get_at(symbol->enclosed, i);
      if ((child_symbol->flags & CC_SYMBOL_FLAGS_METHOD) == CC_SYMBOL_FLAGS_METHOD)
      {
        if ((!is_sealed(child_symbol) || is_override(child_symbol)) && !is_abstract(child_symbol) && !is_static(child_symbol))
        {
          cc_c99_node* result_type = to_c99_type(self, ((cc_syms_method*)child_symbol)->result);
          cc_c99_params_list_node* params = to_c99_params_list(self, child_symbol, true, true, true);
          cc_cstring* name = child_symbol->name;
          cc_c99_function_declarator_node* function_declarator = cc_c99_node_create_function_declarator(name, true, result_type, params);
          cc_c99_function_declaration_node* function_declaration = cc_c99_node_create_function_declaration(function_declarator);
          cc_c99_group_node_append(group_node, (cc_c99_node *)function_declaration);
        }
      }
    }
  } break;
  case CC_EMIT_DISPATCH_GENERATION_STRATEGY_DECLARATIONS_PUBLIC_HEADER:
  {
    for (size_t i = 0, n = cc_arraylist_get_size(symbol->enclosed); i < n; ++i)
    {
      cc_symbol* child_symbol = (cc_symbol*)cc_arraylist_get_at(symbol->enclosed, i);
      if ((child_symbol->flags & CC_SYMBOL_FLAGS_METHOD) == CC_SYMBOL_FLAGS_METHOD && is_public(child_symbol))
      {
        if (!is_override(child_symbol))
        {
          cc_c99_group_node_append(group_node, make_wrapper_decl(self, child_symbol));
        }
      }
    }
  } break;
  case CC_EMIT_DISPATCH_GENERATION_STRATEGY_DECLARATIONS_PROTECTED_HEADER:
  {
    for (size_t i = 0, n = cc_arraylist_get_size(symbol->enclosed); i < n; ++i)
    {
      cc_symbol* child_symbol = (cc_symbol*)cc_arraylist_get_at(symbol->enclosed, i);
      if ((child_symbol->flags & CC_SYMBOL_FLAGS_METHOD) == CC_SYMBOL_FLAGS_METHOD && is_protected(child_symbol))
      {
        if (!is_override(child_symbol))
        {
          cc_c99_group_node_append(group_node, make_wrapper_decl(self, child_symbol));
        }
      }
    }
  } break;
  case CC_EMIT_DISPATCH_GENERATION_STRATEGY_DEFINITIONS_FOOTER_INLAY:
  {
    for (size_t i = 0, n = cc_arraylist_get_size(symbol->enclosed); i < n; ++i)
    {
      cc_symbol* child_symbol = (cc_symbol*)cc_arraylist_get_at(symbol->enclosed, i);
      if ((child_symbol->flags & CC_SYMBOL_FLAGS_METHOD) == CC_SYMBOL_FLAGS_METHOD)
      {
        if (!is_static(child_symbol) && !is_override(child_symbol) && !is_sealed(child_symbol))
        {
          if (((cc_syms_method *)child_symbol)->result == self->symbols->VOID || NULL != get_default_value(self, ((cc_syms_method*)child_symbol)->result))
          {
            cc_c99_group_node_append(group_node, make_wrapper_defn(self, child_symbol));
          }
        }
      }
    }
  } break;
  default:
    cc_error(CC_EINVAL);
  };

  return group_node;
}
