/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "spectre/cc_enter.h"


#include "cc_os_arraylist.h"


static const char KEY[] = "enter";

/// Ensure namespaces exist inside a specified enclosing symbol.
/// The innermost created namespace is returned.
/// @a enclosing must be a namespace symbol or a module symbol.
static cc_symbol* cc_sym_make_namespace_ex(cc_enter* self, cc_symbol* enclosing, cc_cstring* name)
{
  cc_arraylist* el = self->scratch_list;
  cc_arraylist_clear(el);
  cc_symbol* current = enclosing;
  cc_cstring_split(name, '.', el);
  for (size_t i = 0, n = cc_arraylist_get_size(el); i < n; ++i)
  {
    cc_cstring* e = (cc_cstring *)cc_arraylist_get_at(el, i);
    current = cc_syms_get_or_create_namespace(self->syms, current, e);
  }
  return current;
}

/// Apply the modifiers specified by @a modifier to a symbol @a symbol.
/// Raises an error a modifier specified by @a modifier can not be applied to the program element represented by that symbol.
static void apply_modifier(cc_enter* self, cc_modifier_tree* modifier, cc_symbol* target)
{
  switch (target->flags & (CC_SYMBOL_FLAGS_CALLABLE_MASK | CC_SYMBOL_FLAGS_TYPE_MASK))
  {
  case CC_SYMBOL_FLAGS_CLASS:
  {
    if (cc_cstring_equal(modifier->modifier, self->names->ABSTRACT->string))
    {
      target->flags |= CC_SYMBOL_FLAGS_ABSTRACT;
    }
    else
    {
      cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_USER, "%s:%d: modifier %s not supported for classes\n", __FILE__, __LINE__, modifier->modifier->p);
      cc_error(CC_EINVAL);
    }
  } break;
  case CC_SYMBOL_FLAGS_METHOD:
  {
    if (cc_cstring_equal(modifier->modifier, self->names->PUBLIC->string))
    {
      target->flags &= ~(CC_SYMBOL_FLAGS_PROTECTED | CC_SYMBOL_FLAGS_PRIVATE);
    }
    else if (cc_cstring_equal(modifier->modifier, self->names->PRIVATE->string))
    {
      target->flags &= ~(CC_SYMBOL_FLAGS_PROTECTED | CC_SYMBOL_FLAGS_PRIVATE);
      target->flags |= CC_SYMBOL_FLAGS_PRIVATE;
    }
    else if (cc_cstring_equal(modifier->modifier, self->names->PROTECTED->string))
    {
      target->flags &= ~(CC_SYMBOL_FLAGS_PROTECTED | CC_SYMBOL_FLAGS_PRIVATE);
      target->flags |= CC_SYMBOL_FLAGS_PROTECTED;
    }
    else if (cc_cstring_equal(modifier->modifier, self->names->STATIC->string))
    {
      target->flags |= CC_SYMBOL_FLAGS_STATIC;
    }
    else if (cc_cstring_equal(modifier->modifier, self->names->SEALED->string))
    {
      target->flags |= CC_SYMBOL_FLAGS_SEALED;
    }
    else if (cc_cstring_equal(modifier->modifier, self->names->ABSTRACT->string))
    {
      target->flags |= CC_SYMBOL_FLAGS_ABSTRACT;
    }
    else if (cc_cstring_equal(modifier->modifier, self->names->OVERRIDE->string))
    {
      target->flags |= CC_SYMBOL_FLAGS_OVERRIDE;
    }
    else
    {
      cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_USER, "%s:%d: modifier %s not supported for methods\n", __FILE__, __LINE__, modifier->modifier->p);
      cc_error(CC_EINVAL);
    }
  } break;
  case CC_SYMBOL_FLAGS_DESTRUCTOR:
  {
    if (cc_cstring_equal(modifier->modifier, self->names->PUBLIC->string))
    {
      target->flags &= ~(CC_SYMBOL_FLAGS_PROTECTED | CC_SYMBOL_FLAGS_PRIVATE);
    }
    else if (cc_cstring_equal(modifier->modifier, self->names->PRIVATE->string))
    {
      target->flags &= ~(CC_SYMBOL_FLAGS_PROTECTED | CC_SYMBOL_FLAGS_PRIVATE);
      target->flags |= CC_SYMBOL_FLAGS_PRIVATE;
    }
    else if (cc_cstring_equal(modifier->modifier, self->names->PROTECTED->string))
    {
      target->flags &= ~(CC_SYMBOL_FLAGS_PROTECTED | CC_SYMBOL_FLAGS_PRIVATE);
      target->flags |= CC_SYMBOL_FLAGS_PROTECTED;
    }
    else if (cc_cstring_equal(modifier->modifier, self->names->FOREIGN->string))
    {
      target->flags |= CC_SYMBOL_FLAGS_FOREIGN;
    }
    else
    {
      cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_USER, "%s:%d: modifier %s not supported for destructors\n", __FILE__, __LINE__, modifier->modifier->p);
      cc_error(CC_EINVAL);
    }
  } break;
  case CC_SYMBOL_FLAGS_CONSTRUCTOR:
  {
    if (cc_cstring_equal(modifier->modifier, self->names->PUBLIC->string))
    {
      target->flags &= ~(CC_SYMBOL_FLAGS_PROTECTED | CC_SYMBOL_FLAGS_PRIVATE);
    }
    else if (cc_cstring_equal(modifier->modifier, self->names->PRIVATE->string))
    {
      target->flags &= ~(CC_SYMBOL_FLAGS_PROTECTED | CC_SYMBOL_FLAGS_PRIVATE);
      target->flags |= CC_SYMBOL_FLAGS_PRIVATE;
    }
    else if (cc_cstring_equal(modifier->modifier, self->names->PROTECTED->string))
    {
      target->flags &= ~(CC_SYMBOL_FLAGS_PROTECTED | CC_SYMBOL_FLAGS_PRIVATE);
      target->flags |= CC_SYMBOL_FLAGS_PROTECTED;
    }
    else
    {
      cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_USER, "modifier %s not supported for constructors\n", modifier->modifier->p);
      cc_error(CC_EINVAL);
    }
  } break;
  default:
  {
    cc_print_f(CC_PRINT_FLAG_ERROR|CC_PRINT_FLAG_USER, "modifier %s not supported\n", modifier->modifier->p);
    cc_error(CC_EINVAL);
  } break;
  };
}

static void apply_modifiers(cc_enter* self, cc_arraylist* modifiers, cc_symbol* target)
{
  for (size_t i = 0, n = cc_arraylist_get_size(modifiers); i < n; ++i)
  {
    cc_modifier_tree* modifier = (cc_modifier_tree*)cc_arraylist_get_at(modifiers, i);
    apply_modifier(self, modifier, target);
  }
}

static void enter_modifiers(cc_enter* self, cc_symbol* sym, cc_tree *tree)
{
  uint32_t kind = cc_t_get_kind(tree);
  switch (kind)
  {
  case CC_TT_CLASS:
  {
    apply_modifiers(self, cc_tree_to_defn(tree)->modifiers, sym);
  } break;
  case CC_TT_CONSTRUCTOR:
  case CC_TT_METHOD:
  case CC_TT_DESTRUCTOR:
  {
    apply_modifiers(self, cc_tree_to_proc(tree)->modifiers, sym);
  } break;
  };
}

static void do_enter_builtin_windows(cc_enter* self, cc_symbol* program)
{
  cc_symbol* module = cc_syms_get_or_create_module(self->syms, program, self->names->BUILTIN_MODULE->string);
  module->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  cc_symbol* namespace = cc_syms_get_or_create_namespace(self->syms, module, self->names->RING2->string);
  namespace->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  namespace = cc_syms_get_or_create_namespace(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "windows")->string);

  cc_symbol* s;

  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "HWND")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "HDC")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "HICON")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
}

static void do_enter_builtin(cc_enter *self, cc_symbol* program)
{
  cc_symbol* module = cc_syms_get_or_create_module(self->syms, program, self->names->BUILTIN_MODULE->string);
  module->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  cc_symbol* namespace = cc_syms_get_or_create_namespace(self->syms, module, self->names->RING2->string);
  namespace->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  cc_symbol* s;

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  s = cc_syms_make_class_type(self->syms, namespace, self->names->STRING->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  {
    cc_symbol* machine_namespace = cc_syms_get_or_create_namespace(self->syms, module, self->names->MACHINE->string);
    machine_namespace->flags |= CC_SYMBOL_FLAGS_BUILTIN;
    s = cc_syms_make_class_type(self->syms, machine_namespace, self->names->OBJECT->string);
    s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  }
  s = cc_syms_make_class_type(self->syms, namespace, self->names->WEAK_REFERENCE->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  // TODO: Remove this.
  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "array")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "reference_array")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "scalar_array")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "hashmap")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "signal")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "rgb_uint8")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "rgb_flt")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "l_uint8")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "matrix44")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "vector3")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "vector2_i32")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  s = cc_syms_make_structure(self->syms, namespace, cc_spectre_names_get_or_create(self->names, "vector2_f32")->string);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  do_enter_builtin_windows(self, program);

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
}

static void do_enter_tree(cc_enter* self, cc_tree* t, cc_symbol* enclosing_sym);

static void do_enter_defn(cc_enter* self, cc_defn_tree* tree, cc_symbol* enclosing_sym)
{
  // Ensure no class or enumeration of same name exists.
  cc_cstring* name = cc_t_get_name((cc_tree *)tree);
  cc_symbol* existing = cc_sym_find_enclosed_2(enclosing_sym, CC_SEARCH_FLAGS_CLASS_TYPES | CC_SEARCH_FLAGS_ENUMERATION_TYPES, name);
  cc_symbol* incoming = NULL;
  switch (cc_t_get_kind((cc_tree *)tree))
  {
  case CC_TT_CLASS:
    incoming = cc_syms_make_class_type(self->syms, enclosing_sym, name);
    break;
  case CC_TT_ENUMERATION:
    incoming = cc_syms_make_enumeration(self->syms, enclosing_sym, name);
    break;
  default:
    cc_error(CC_EINVAL);
  };
  incoming->source = (cc_tree *)tree;
  enter_modifiers(self, incoming, (cc_tree *)tree);
  if (existing != NULL)
  {
    cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_USER, "%s:%d: a symbol of name '%s' already exists\n", __FILE__, __LINE__, name->p);
    cc_error(CC_EINVAL);
  }
  for (size_t i = 0; i < cc_arraylist_get_size(cc_defn_tree_get_members(tree)); ++i)
  {
    cc_tree* child = (cc_tree*)cc_arraylist_get_at(cc_defn_tree_get_members(tree), i);
    CC_ASSERT_NOT_NULL(child);
    do_enter_tree(self, child, incoming);
  }
}

static void do_enter_program_tree(cc_enter* self, cc_program_tree* tree, cc_symbol* enclosing_sym)
{
  for (size_t i = 0, n = cc_arraylist_get_size(tree->compilation_units); i < n; ++i)
  {
    cc_tree* child_tree = (cc_tree*)cc_arraylist_get_at(tree->compilation_units, i);
    do_enter_tree(self, child_tree, enclosing_sym);
  }
}

static void do_enter_namespace_tree(cc_enter* self, cc_namespace_tree* tree, cc_symbol* enclosing_sym)
{
  cc_symbol* namespace_sym = cc_sym_make_namespace_ex(self, enclosing_sym, cc_t_get_name((cc_tree*)tree));
  namespace_sym->source = (cc_tree*)tree;
  for (size_t i = 0; i < cc_arraylist_get_size(tree->definitions); ++i)
  {
    cc_tree* child_tree = (cc_tree*)cc_arraylist_get_at(tree->definitions, i);
    CC_ASSERT_NOT_NULL(child_tree);
    do_enter_tree(self, child_tree, namespace_sym);
  }
}

static void do_enter_module_tree(cc_enter* self, cc_module_tree* tree, cc_symbol* enclosing_sym)
{
  cc_symbol* module_sym = cc_syms_get_or_create_module(self->syms, enclosing_sym, cc_t_get_name((cc_tree*)tree));
  module_sym->source = (cc_tree *)tree;
  for (size_t i = 0; i < cc_arraylist_get_size(tree->definitions); ++i)
  {
    cc_tree* child_tree = (cc_tree*)cc_arraylist_get_at(tree->definitions, i);
    CC_ASSERT_NOT_NULL(child_tree);
    do_enter_tree(self, child_tree, module_sym);
  }
}

static void do_enter_compilation_unit(cc_enter* self, cc_compilation_unit_tree* tree, cc_symbol* enclosing_sym)
{
  for (size_t i = 0, n = cc_arraylist_get_size(tree->modules); i < n; ++i)
  {
    cc_tree* child_tree = (cc_tree*)cc_arraylist_get_at(tree->modules, i);
    do_enter_tree(self, child_tree, enclosing_sym);
  }
}

static void do_enter_tree(cc_enter* self, cc_tree* t, cc_symbol* enclosing_sym)
{
  switch (cc_t_get_kind(t))
  {
  case CC_TT_PROGRAM:
  {
    do_enter_program_tree(self, cc_tree_to_program(t), enclosing_sym);
  } break;
  case CC_TT_COMPILATION_UNIT:
  {
    do_enter_compilation_unit(self, cc_tree_to_compilation_unit(t), enclosing_sym);
  } break;
  case CC_TT_METHOD:
  {
    // Ensure no method or member variable of same name exists.
    cc_cstring* name = cc_t_get_name(t);
    cc_symbol* existing = cc_sym_find_enclosed_2(enclosing_sym, CC_SEARCH_FLAGS_METHODS | CC_SEARCH_FLAGS_MEMBER_VARIABLES, name);
    cc_symbol* incoming = cc_syms_make_method(self->syms, enclosing_sym, name);
    incoming->source = t;
    enter_modifiers(self, incoming, t);
    if (existing != NULL)
    {
      cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_USER, "%s:%d: a symbol of name '%s' already exists\n", __FILE__, __LINE__, name->p);
      cc_error(CC_EINVAL);
    }
  } break;
  case CC_TT_MODULE:
  {
    do_enter_module_tree(self, cc_tree_to_module(t), enclosing_sym);
  } break;
  case CC_TT_NAMESPACE:
  {
    do_enter_namespace_tree(self, cc_tree_to_namespace(t), enclosing_sym);
  } break;
  case CC_TT_CONSTRUCTOR:
  {
    cc_symbol* sym = cc_syms_make_constructor(self->syms, enclosing_sym, cc_tree_to_proc(t)->suffix);
    sym->source = t;
    enter_modifiers(self, sym, t);
  } break;
  case CC_TT_DESTRUCTOR:
  {
    cc_symbol* sym = cc_syms_make_destructor(self->syms, enclosing_sym);
    sym->source = t;
    enter_modifiers(self, sym, t);
  } break;
  case CC_TT_CLASS:
  case CC_TT_ENUMERATION:
  {
    do_enter_defn(self, cc_tree_to_defn(t), enclosing_sym);
  } break;
  case CC_TT_MEMBER_VARIABLE:
  {
    // Ensure no method or member variable of the same name exists.
    cc_cstring* name = cc_t_get_name(t);
    cc_symbol* existing = cc_sym_find_enclosed_2(enclosing_sym, CC_SEARCH_FLAGS_METHODS | CC_SEARCH_FLAGS_MEMBER_VARIABLES, name);
    cc_symbol* incoming = cc_syms_make_member_variable(self->syms, enclosing_sym, name);
    incoming->source = t;
    if (cc_tree_is_member_variable_kind(t))
    {
      ((cc_syms_member_variable*)incoming)->initializer = cc_tree_to_var(t)->initializer;
    }
    if (existing != NULL)
    {
      cc_print_f(CC_PRINT_FLAG_ERROR | CC_PRINT_FLAG_USER, "%s:%d: a symbol of name '%s' already exists\n", __FILE__, __LINE__, name->p);
      cc_error(CC_EINVAL);
    }
  } break;
  };
}

void cc_enter_run(cc_enter *self, cc_program_tree* tree)
{
  do_enter_builtin(self, self->syms->PROGRAM);
  do_enter_tree(self, (cc_tree*)tree, self->syms->PROGRAM);
}

static void cc_enter_visit(cc_enter* self)
{
  CC_VISIT(self->ctx);
  CC_VISIT(self->buffer);
}

static cc_enter* factory(cc_ctx* ctx)
{
  cc_type* type = CC_DECORATE(cc_enter_get_type)();
  cc_enter* self = (cc_enter*)cc_object_allocate_2(type);

  self->buffer = cc_bytebuffer_create();
  self->scratch_list = cc_arraylist_create(8);

  self->names = cc_spectre_names_get_instance(ctx);

  self->syms = cc_syms_get_instance(ctx);

  return self;
}

DEFINE_COMPONENT(cc_enter, &factory, &cc_enter_visit, NULL)
