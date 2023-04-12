/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "spectre/cc_resolve.h"


#include "cc_os_lib.h"
#include <string.h>


static const char KEY[] = "resolve";

/* Resolve a T. */
static cc_symbol* resolve_type_0(cc_resolve* self, cc_cstring* name, int mask)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(name);

  for (cc_symbol* current = cc_sym_first(self->ctx); NULL != current; current = cc_sym_next(current))
  {
    if ((current->flags & mask) != 0)
    {
      cc_cstring* fqn = cc_sym_get_fqn(current);
      if (!strcmp(fqn->p, name->p))
      {
        return current;
      }
    }
  }
  return NULL;
}

static cc_symbol* cc_get_default_namespace(cc_resolve *self)
{
  return resolve_type_0(self, cc_cstring_create("Ring2"), CC_SYMBOL_FLAGS_NAMESPACE);
}

#include "cc_file_manager.h"
#include <inttypes.h>

/* Resolve a type T or T[]. */
static cc_symbol* resolve_type(cc_resolve* self, cc_tree* tree, int mask)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(tree);
  if ((tree->flags & (CC_TT_DIRECT_TYPE_REFERENCE | CC_TT_ARRAY_TYPE_REFERENCE)) == 0)
  {
    cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_INTERNAL, "%s:%d: <internal error>\n", __FILE__, __LINE__);
    cc_error(CC_EINVAL);
  }
  switch (cc_t_get_kind(tree))
  {
  case CC_TT_DIRECT_TYPE_REFERENCE:
  {
    cc_cstring* string = cc_tree_to_direct_type_reference(tree)->name;
    cc_symbol* sym = resolve_type_0(self, string, mask);
    if (!sym)
    {
      cc_direct_type_reference_tree* source = cc_tree_to_direct_type_reference(tree);
      // @todo Add some diagnostic funtionality.
      if (source->position->offset > SIZE_MAX) {
        cc_error(CC_EINVAL);
      }
      uint32_t line = cc_line_map_get_line(source->position->line_map, (size_t)source->position->offset);
      uint32_t column = cc_line_map_get_column(source->position->line_map, (size_t)source->position->offset);
      cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_USER, "%s:%d: %s:%"PRIu32 ":%"PRIu32 ": unable to resolve type %s\n", __FILE__, __LINE__, source->position->line_map->file_path->p, line, column, string->p);
      cc_error(CC_EINVAL);
    }
    return sym;
  } break;
  case CC_TT_ARRAY_TYPE_REFERENCE:
  {
    cc_tree* innermost_type = cc_tree_to_array_type_reference(tree)->inner_type;
    size_t count = 1;
    while (innermost_type->flags & CC_TT_ARRAY_TYPE_REFERENCE)
    {
      innermost_type = cc_tree_to_array_type_reference(innermost_type)->inner_type;
      count++;
    }
    cc_symbol* sym = resolve_type(self, innermost_type, CC_SYMBOL_FLAGS_CLASS | CC_SYMBOL_FLAGS_ENUMERATION | CC_SYMBOL_FLAGS_SCALAR | CC_SYMBOL_FLAGS_STRUCTURE);
    while (count > 0)
    {
      sym = cc_syms_get_or_create_array_type(self->syms, cc_get_default_namespace(self), sym);
      --count;
    }
    return sym;
  } break;
  default:
  {
    cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_INTERNAL, "%s:%d: <internal error>\n", __FILE__, __LINE__);
    cc_error(CC_EINVAL);
  } break;
  };
}

static void resolve_member_variable(cc_resolve* self, cc_symbol* sym)
{
  cc_var_tree* tree = cc_tree_to_var(sym->source);
  if (!cc_tree_is_member_variable_kind((cc_tree*)tree))
  {
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_INTERNAL, "%s:%d: <internal error>\n", __FILE__, __LINE__);
    cc_error(CC_EINVAL);
  }
  cc_symbol* type_sym = resolve_type(self, tree->type, CC_SYMBOL_FLAGS_CLASS | CC_SYMBOL_FLAGS_ENUMERATION | CC_SYMBOL_FLAGS_SCALAR | CC_SYMBOL_FLAGS_STRUCTURE);
  sym->type = type_sym;
}

static void enter_parameter_modifiers(cc_resolve* self, cc_symbol* sym, cc_var_tree* tree)
{
  for (size_t i = 0, n = cc_arraylist_get_size(tree->modifiers); i < n; ++i)
  {
    cc_modifier_tree* modifier_tree = (cc_modifier_tree*)cc_arraylist_get_at(tree->modifiers, i);
    if (cc_cstring_equal(modifier_tree->modifier, self->OUT->string))
    {
      sym->flags |= CC_SYMBOL_FLAGS_OUT;
    }
    else
    {
      cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_USER, "%s:%d: modifier %s not supported for parameters\n", __FILE__, __LINE__, modifier_tree->modifier->p);
      cc_error(CC_EINVAL);
    }
  }
}

static void resolve_callable_override(cc_resolve* self, cc_symbol* sym)
{
  cc_cstring* name = sym->name;
  cc_symbol* enclosing = sym->enclosing;
  if ((enclosing->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS)
  {
    while (true)
    {
      enclosing = enclosing->parent;
      if (enclosing == NULL)
      {
        break;
      }
      cc_symbol* override_of = cc_sym_find_enclosed_2(enclosing, CC_SEARCH_FLAGS_METHODS, name);
      if (NULL != override_of)
      {
        if ((override_of->flags & CC_SYMBOL_FLAGS_SEALED) == CC_SYMBOL_FLAGS_SEALED)
        {
          cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_USER, "%s:%d: unable to override sealed method\n", __FILE__, __LINE__);
          cc_error(CC_EINVAL);
        }
        else if ((override_of->flags & CC_SYMBOL_FLAGS_STATIC) == CC_SYMBOL_FLAGS_STATIC)
        {
          cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_USER, "%s:%d: unable to override static method\n", __FILE__, __LINE__);
          cc_error(CC_EINVAL);
        }
        ((cc_syms_method*)sym)->override = override_of;
        if (override_of && (sym->flags & CC_SYMBOL_FLAGS_OVERRIDE) == 0)
        {
          cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_USER, "%s:%d: method overrides other method but has no override qualifier specified\n", __FILE__, __LINE__);
          cc_error(CC_EINVAL);
        }
        break;
      }
    }
    if (!((cc_syms_method*)sym)->override && (sym->flags & CC_SYMBOL_FLAGS_OVERRIDE) == CC_SYMBOL_FLAGS_OVERRIDE)
    {
      cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_USER, "%s:%d: method is not an override of a method\n", __FILE__, __LINE__);
      cc_error(CC_EINVAL);
    }
  }
}

/// @todo The term "proc" is used instead of the term "callable".
static void resolve_callable(cc_resolve* self, cc_symbol* sym)
{
  cc_proc_tree* tree = cc_tree_to_proc(sym->source);
  // Resolve parameter types.
  cc_arraylist* parameter_variables_tree = cc_proc_tree_get_parameters(tree);
  for (size_t i = 0, n = cc_arraylist_get_size(parameter_variables_tree); i < n; ++i)
  {
    cc_var_tree* parameter_variable_tree = cc_tree_to_var((cc_tree*)cc_arraylist_get_at(parameter_variables_tree, i));
    cc_cstring* name = cc_t_get_name((cc_tree*)parameter_variable_tree);
    CC_ASSERT_NOT_NULL(name);
    cc_symbol* parameter_variable_sym = cc_syms_make_parameter_variable(self->syms, sym, name);
    enter_parameter_modifiers(self, parameter_variable_sym, parameter_variable_tree);
    parameter_variable_sym->type = resolve_type(self, parameter_variable_tree->type, CC_SYMBOL_FLAGS_CLASS | CC_SYMBOL_FLAGS_ENUMERATION | CC_SYMBOL_FLAGS_SCALAR | CC_SYMBOL_FLAGS_STRUCTURE);
  }
  if ((sym->flags & CC_SYMBOL_FLAGS_METHOD) == CC_SYMBOL_FLAGS_METHOD)
  {
    // Resolve result type.
    cc_tree* result_type_tree = cc_proc_tree_get_result_type(tree);
    cc_symbol* result_type_sym = resolve_type(self, result_type_tree, CC_SYMBOL_FLAGS_CLASS | CC_SYMBOL_FLAGS_ENUMERATION | CC_SYMBOL_FLAGS_SCALAR);
    ((cc_syms_method *)sym)->result = result_type_sym;
  }
}

static void resolve_class(cc_resolve* self, cc_symbol* sym)
{
  cc_defn_tree* tree = cc_tree_to_defn(sym->source);
  if (cc_arraylist_get_size(tree->extends) == 0)
  {
    sym->parent = resolve_type(self, (cc_tree*)cc_tree_factory_create_direct_type_reference(self->tree_factory, tree->keyword_position, self->names->MACHINE_OBJECT->string), CC_SYMBOL_FLAGS_CLASS);
  }
  else if (cc_arraylist_get_size(tree->extends) == 1)
  {
    sym->parent = resolve_type(self, ((cc_tree *)cc_arraylist_get_at(tree->extends, 0)), CC_SYMBOL_FLAGS_CLASS);
  }
  else
  {
    cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_USER, "%s:%d: a class can not extend more than one class\n", __FILE__, __LINE__);
    cc_error(CC_EINVAL);
  }
}

void cc_resolve_run(cc_resolve *self)
{
  for (cc_symbol* current = cc_sym_first(self->ctx); NULL != current; current = cc_sym_next(current))
  {
    if ((current->flags & CC_SYMBOL_FLAGS_BUILTIN) == CC_SYMBOL_FLAGS_BUILTIN)
    {
      continue;
    }
    else if ((current->flags & CC_SYMBOL_FLAGS_MEMBER_VARIABLE) == CC_SYMBOL_FLAGS_MEMBER_VARIABLE)
    {
      resolve_member_variable(self, current);
    }
    else if ((current->flags & (CC_SYMBOL_FLAGS_CONSTRUCTOR | CC_SYMBOL_FLAGS_DESTRUCTOR | CC_SYMBOL_FLAGS_METHOD)) != 0)
    {
      resolve_callable(self, current);
    }
    else if ((current->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS)
    {
      resolve_class(self, current);
    }
  }

  for (cc_symbol* current = cc_sym_first(self->ctx); NULL != current; current = cc_sym_next(current))
  {
    if ((current->flags & CC_SYMBOL_FLAGS_BUILTIN) == CC_SYMBOL_FLAGS_BUILTIN)
    {
      continue;
    }
    else if ((current->flags & CC_SYMBOL_FLAGS_METHOD) != 0)
    {
      resolve_callable_override(self, current);
    }
  }
}

static void cc_resolve_visit(cc_resolve* self)
{ 
  CC_VISIT(self->ctx);
  CC_VISIT(self->syms);
  CC_VISIT(self->names);
  CC_VISIT(self->tree_factory);
}

static cc_resolve* factory(cc_ctx* ctx)
{
  cc_type* type = CC_DECORATE(cc_resolve_get_type)();
  cc_resolve* self = (cc_resolve*)cc_object_allocate_2(type);

  self->syms = cc_syms_get_instance(ctx);
  self->names = cc_spectre_names_get_instance(ctx);
  self->tree_factory = cc_tree_factory_get_instance(ctx);
  self->OUT = self->names->OUT;

  return self;
}

DEFINE_COMPONENT(cc_resolve, &factory, &cc_resolve_visit, NULL)
