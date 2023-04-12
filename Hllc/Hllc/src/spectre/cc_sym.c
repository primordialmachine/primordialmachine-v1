/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "spectre/cc_sym.h"

#include "cc_os_lib.h"
#include <string.h>

/// @brief Enter the following runtime builtin type symbols.
/// - <code>g.real</code>
/// - <code>g.real(32|64)</code>
///
/// - <code>g.boolean</code>
///
/// - <code>g.integer</code>
/// - <code>g.integer(8|16|32|64)</code>
///
/// - <code>g.natural</code>
/// - <code>g.natural(8|16|32|64)</code>
///
/// - <code>g.void</code>
/// - <code>g.size</code>
static void cc_syms_enter_runtime_builtins(cc_syms* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const char KEY[] = "syms";

static void cc_syms_visit(cc_syms* self)
{
  CC_VISIT(self->ctx);
  CC_VISIT(self->scratch_buffer);
  CC_VISIT(self->scratch_list);

  cc_symbol* sym = self->first;
  while (sym)
  {
    cc_visit((cc_object*)sym);
    sym = sym->next;
  }
}

static cc_syms* factory(cc_ctx* ctx)
{
  cc_type* type = CC_DECORATE(cc_syms_get_type)();
  cc_syms *self = (cc_syms *)cc_object_allocate_2(type);

  self->first = NULL;
  self->scratch_buffer = cc_cstring_buffer_create();
  self->scratch_list = cc_arraylist_create(0);
  self->names = cc_spectre_names_get_instance(ctx);

  self->PROGRAM = cc_syms_make_program(self);
  cc_syms_enter_runtime_builtins(self);

  return self;
}

DEFINE_COMPONENT(cc_syms, &factory, &cc_syms_visit, NULL)

void cc_syms_enter_runtime_builtins(cc_syms* self)
{
  cc_symbol* module = cc_syms_get_or_create_module(self, self->PROGRAM, self->names->BUILTIN_MODULE->string);
  module->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  cc_symbol* namespace = cc_syms_get_or_create_namespace(self, module, self->names->RING2->string);
  namespace->flags |= CC_SYMBOL_FLAGS_BUILTIN;

  cc_symbol* s;

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  // Default width integer/natural types.

  s = cc_syms_make_scalar_type(self, namespace, self->names->INTEGER);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->INTEGER = s;

  s = cc_syms_make_scalar_type(self, namespace, self->names->NATURAL);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->NATURAL = s;

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  // Default width real types.
  s = cc_syms_make_scalar_type(self, namespace, self->names->REAL);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->REAL = s;

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  // Fixed with integer/natural types.

  s = cc_syms_make_scalar_type(self, namespace, self->names->NATURAL8);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->NATURAL8 = s;

  s = cc_syms_make_scalar_type(self, namespace, self->names->NATURAL16);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->NATURAL16 = s;

  s = cc_syms_make_scalar_type(self, namespace, self->names->NATURAL32);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->NATURAL32 = s;

  s = cc_syms_make_scalar_type(self, namespace, self->names->NATURAL64);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->NATURAL64 = s;

  s = cc_syms_make_scalar_type(self, namespace, self->names->INTEGER8);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->INTEGER8 = s;

  s = cc_syms_make_scalar_type(self, namespace, self->names->INTEGER16);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->INTEGER16 = s;

  s = cc_syms_make_scalar_type(self, namespace, self->names->INTEGER32);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->INTEGER32 = s;

  s = cc_syms_make_scalar_type(self, namespace, self->names->INTEGER64);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->INTEGER64 = s;

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  // Fixed width real types.
  s = cc_syms_make_scalar_type(self, namespace, self->names->REAL32);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->REAL32 = s;

  s = cc_syms_make_scalar_type(self, namespace, self->names->REAL64);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->REAL64 = s;

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  s = cc_syms_make_scalar_type(self, namespace, self->names->VOID);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->VOID = s;

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  s = cc_syms_make_scalar_type(self, namespace, self->names->SIZE);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->SIZE = s;

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  s = cc_syms_make_scalar_type(self, namespace, self->names->BOOLEAN);
  s->flags |= CC_SYMBOL_FLAGS_BUILTIN;
  self->BOOLEAN = s;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_symbol_visit(cc_symbol* self)
{
  CC_VISIT(self->source);
  CC_VISIT(self->name);
  CC_VISIT(self->qualified_name);
  CC_VISIT(self->enclosing);
  CC_VISIT(self->enclosed);
}

CC_DEFINE_ABSTRACT_CLASS(cc_symbol, cc_object, &cc_symbol_visit, NULL, NULL, NULL)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static cc_cstring* make_array_type_name(cc_syms* syms, cc_symbol* inner_type)
{
  cc_cstring_buffer* buffer = syms->scratch_buffer;
  cc_cstring_buffer_clear(buffer);
  cc_cstring_buffer_append_p(buffer, "[");
  cc_cstring_buffer_append_s(buffer, inner_type->qualified_name->string);
  cc_cstring_buffer_append_p(buffer, "]");
  return cc_spectre_names_get_or_create(syms->names, buffer->byte_buffer->p)->string;
}

static cc_name* make_constructor_name(cc_syms* syms, cc_cstring* suffix)
{
  cc_cstring_buffer* buffer = syms->scratch_buffer;
  cc_cstring_buffer_clear(buffer);
  cc_cstring_buffer_append_p(buffer, "<constructor>");
  if (suffix)
  {
    cc_cstring_buffer_append_s(buffer, suffix);
  }
  return cc_spectre_names_get_or_create(syms->names, buffer->byte_buffer->p);
}

static cc_name* make_destructor_name(cc_syms* syms)
{
  return cc_spectre_names_get_or_create(syms->names, "<destructor>");
}

static cc_name* make_fully_qualified_name(cc_syms* syms, cc_symbol* symbol)
{
  cc_arraylist* list = syms->scratch_list;
  cc_arraylist_clear(list);
  
  cc_cstring_buffer* buffer = syms->scratch_buffer;
  cc_cstring_buffer_clear(buffer);

  // Concatenate names of symbols from innermost to outermost in reverse.
  // Two adjacent symbol names are separated by a '.'.
  do
  {
    cc_arraylist_append(list, (cc_object *)symbol);
    symbol = symbol->enclosing;
  } while (symbol && (symbol->flags & CC_SYMBOL_FLAGS_MODULE) != CC_SYMBOL_FLAGS_MODULE);
  
  for (size_t i = cc_arraylist_get_size(list) - 1; i > 0; --i)
  {
    symbol = (cc_symbol *)cc_arraylist_get_at(list, i);
    cc_cstring_buffer_append_s(buffer, symbol->name);
    cc_cstring_buffer_append_p(buffer, ".");
  }
  symbol = (cc_symbol *)cc_arraylist_get_at(list, 0);
  cc_cstring_buffer_append_s(buffer, symbol->name);
  
  return cc_spectre_names_get_or_create(syms->names, buffer->byte_buffer->p);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// TODO: Remove this.
/// @brief Allocate a symbol.
/// @return A pointer to the symbol.
static cc_symbol* cc_sym_alloc(cc_syms* syms, int flags)
{
  cc_type* type = CC_DECORATE(cc_symbol_get_type)();
  cc_symbol* sym = (cc_symbol *)cc_object_allocate_2(type);
  if ((flags & (CC_SYMBOL_FLAGS_CLASS | CC_SYMBOL_FLAGS_ENUMERATION | CC_SYMBOL_FLAGS_MODULE | CC_SYMBOL_FLAGS_NAMESPACE | CC_SYMBOL_FLAGS_PROGRAM)) != 0)
  {
    sym->enclosed = cc_arraylist_create(0);
  }
  sym->flags = flags;
  sym->next = syms->first; syms->first = sym;
  return sym;
}

static cc_cstring* get_name(cc_symbol* symbol)
{
  CC_ASSERT_NOT_NULL(symbol);
  CC_ASSERT_NOT_NULL(symbol->name);
  return symbol->name;
}

static bool accept_symbol(cc_symbol* sym, cc_search_flags flags, cc_cstring* name)
{
  bool c = false;

  c = name != NULL && get_name(sym) != NULL ? cc_cstring_equal(get_name(sym), name) : true;
  if (!c) return false;

  c = (flags & CC_SEARCH_FLAGS_CLASS_TYPES) == CC_SEARCH_FLAGS_CLASS_TYPES && (sym->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS;
  if (c) return true;
  c = (flags & CC_SEARCH_FLAGS_ENUMERATION_TYPES) == CC_SEARCH_FLAGS_ENUMERATION_TYPES && (sym->flags & CC_SYMBOL_FLAGS_ENUMERATION) == CC_SYMBOL_FLAGS_ENUMERATION;
  if (c) return true;
  c = (flags & CC_SEARCH_FLAGS_INTERFACE_TYPES) == CC_SEARCH_FLAGS_INTERFACE_TYPES && (sym->flags & CC_SYMBOL_FLAGS_INTERFACE) == CC_SYMBOL_FLAGS_INTERFACE;
  if (c) return true;
  c = (flags & CC_SEARCH_FLAGS_SCALAR_TYPES) == CC_SEARCH_FLAGS_SCALAR_TYPES && (sym->flags & CC_SYMBOL_FLAGS_SCALAR) == CC_SYMBOL_FLAGS_SCALAR;
  if (c) return true;
  c = (flags & CC_SEARCH_FLAGS_STRUCTURE_TYPES) == CC_SEARCH_FLAGS_STRUCTURE_TYPES && (sym->flags & CC_SYMBOL_FLAGS_STRUCTURE) == CC_SYMBOL_FLAGS_STRUCTURE;
  if (c) return true;

  c = (flags & CC_SEARCH_FLAGS_METHODS) == CC_SEARCH_FLAGS_METHODS && cc_symbol_is_method(sym);
  if (c) return true;
  c = (flags & CC_SEARCH_FLAGS_MEMBER_VARIABLES) == CC_SEARCH_FLAGS_MEMBER_VARIABLES && (sym->flags & CC_SYMBOL_FLAGS_MEMBER_VARIABLE) == CC_SYMBOL_FLAGS_MEMBER_VARIABLE;
  if (c) return true;
  c = (flags & CC_SEARCH_FLAGS_PARAMETER_VARIABLES) == CC_SEARCH_FLAGS_PARAMETER_VARIABLES && (sym->flags & CC_SYMBOL_FLAGS_PARAMETER_VARIABLE) == CC_SYMBOL_FLAGS_PARAMETER_VARIABLE;
  if (c) return true;

  c = (flags & CC_SEARCH_FLAGS_CONSTRUCTORS) == CC_SEARCH_FLAGS_CONSTRUCTORS && cc_symbol_is_constructor(sym);
  if (c) return true;
  c = (flags & CC_SEARCH_FLAGS_DESTRUCTORS) == CC_SEARCH_FLAGS_DESTRUCTORS && cc_symbol_is_destructor(sym);
  if (c) return true;

  c = (flags & CC_SEARCH_FLAGS_NAMESPACES) == CC_SEARCH_FLAGS_NAMESPACES && cc_symbol_is_namespace(sym);
  if (c) return true;

  c = (flags & CC_SEARCH_FLAGS_MODULES) == CC_SEARCH_FLAGS_MODULES && (sym->flags & CC_SYMBOL_FLAGS_MODULE) == CC_SYMBOL_FLAGS_MODULE;
  if (c) return true;

  return false;
}

cc_symbol* cc_sym_find_enclosed_2(cc_symbol* enclosing, cc_search_flags flags, cc_cstring* name)
{
  CC_ASSERT_NOT_NULL(enclosing);
  CC_ASSERT_NOT_NULL(enclosing->enclosed);

  for (size_t i = 0, n = cc_arraylist_get_size(enclosing->enclosed); i < n; ++i)
  {
    cc_symbol* enclosed = (cc_symbol*)cc_arraylist_get_at(enclosing->enclosed, i);
    if (accept_symbol(enclosed, flags, name))
    { return enclosed; }
  }
  return NULL;
}

cc_cstring* cc_sym_get_fqn(cc_symbol* self)
{
  CC_ASSERT_NOT_NULL(self);
  CC_ASSERT_NOT_NULL(self->qualified_name);
  return self->qualified_name->string;
}

cc_symbol* cc_sym_get_enclosing_module(cc_symbol* sym)
{
  sym = sym->enclosing;
  while (sym != NULL)
  {
    if ((sym->flags & CC_SYMBOL_FLAGS_MODULE) == CC_SYMBOL_FLAGS_MODULE)
    {
      break;
    }
    sym = sym->enclosing;
  }
  return sym;
}

cc_symbol* cc_sym_first(cc_ctx* ctx)
{
  cc_syms* syms = cc_syms_get_instance(ctx);
  return syms->first;
}

cc_symbol* cc_sym_next(cc_symbol* sym)
{
  if (!sym) return NULL;
  return sym->next;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DEFINE_CLASS(cc_syms_program, cc_symbol, NULL, NULL, NULL, NULL)

static cc_symbol* cc_syms_program_create(cc_syms* syms)
{
  CC_ASSERT_NOT_NULL(syms);

  cc_type* _type = CC_DECORATE(cc_syms_program_get_type)();
  cc_syms_program* self = (cc_syms_program*)cc_object_allocate_2(_type);

  ((cc_symbol*)self)->flags = CC_SYMBOL_FLAGS_PROGRAM;
  ((cc_symbol*)self)->enclosing = NULL;
  ((cc_symbol*)self)->enclosed = cc_arraylist_create(0);
  ((cc_symbol*)self)->name = cc_cstring_create("<program>");
  ((cc_symbol*)self)->next = syms->first; syms->first = ((cc_symbol*)self);
  ((cc_symbol*)self)->qualified_name = make_fully_qualified_name(syms, (cc_symbol *)self);

  return (cc_symbol*)self;
}

cc_symbol* cc_syms_make_program(cc_syms* self)
{ return cc_syms_program_create(self); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_syms_method_visit(cc_syms_method* self)
{
  CC_VISIT(self->parameters);
}

CC_DEFINE_CLASS(cc_syms_method, cc_symbol, &cc_syms_method_visit, NULL, NULL, NULL)

static cc_symbol* cc_syms_method_create(cc_syms* syms, cc_symbol* enclosing, cc_cstring* name)
{
  CC_ASSERT_NOT_NULL(syms);
  CC_ASSERT_NOT_NULL(enclosing);
  CC_ASSERT_NOT_NULL(name);

  if (((enclosing->flags & CC_SYMBOL_FLAGS_CLASS) == 0 && (enclosing->flags & CC_SYMBOL_FLAGS_ENUMERATION) == 0))
  { cc_error(CC_EPERM); }

  cc_syms_method* self = (cc_syms_method*)cc_sym_find_enclosed_2(enclosing, CC_SEARCH_FLAGS_METHODS, name);
  if (self)
  { cc_error(CC_EPERM); }
  
  cc_type* _type = CC_DECORATE(cc_syms_method_get_type)();
  self = (cc_syms_method*)cc_object_allocate_2(_type);

  ((cc_symbol*)self)->flags = CC_SYMBOL_FLAGS_METHOD;
  ((cc_symbol*)self)->enclosing = enclosing;
  ((cc_symbol*)self)->name = name;
  self->override = NULL;
  self->parameters = cc_arraylist_create(0);
  cc_arraylist_append(enclosing->enclosed, (cc_object*)self);
  ((cc_symbol*)self)->next = syms->first; syms->first = ((cc_symbol*)self);
  ((cc_symbol*)self)->qualified_name = make_fully_qualified_name(syms, (cc_symbol *)self);

  return (cc_symbol*)self;
}

cc_symbol* cc_syms_make_method(cc_syms* self, cc_symbol* enclosing, cc_cstring* name)
{ return cc_syms_method_create(self, enclosing, name); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_syms_constructor_visit(cc_syms_constructor *self)
{
  CC_VISIT(self->parameters);
  CC_VISIT(self->suffix);
}

CC_DEFINE_CLASS(cc_syms_constructor, cc_symbol, &cc_syms_constructor_visit, NULL, NULL, NULL)

static cc_symbol* cc_syms_constructor_create(cc_syms* syms, cc_symbol* enclosing, cc_cstring* suffix)
{
  CC_ASSERT_NOT_NULL(syms);
  CC_ASSERT_NOT_NULL(enclosing);

  if ((enclosing->flags & CC_SYMBOL_FLAGS_CLASS) == 0)
  { cc_error(CC_EPERM); }

  cc_syms_constructor* self = (cc_syms_constructor *)cc_sym_find_enclosed_2(enclosing, CC_SEARCH_FLAGS_DESTRUCTORS, NULL);
  if (self)
  { cc_error(CC_EPERM); }
  
  cc_type* _type = CC_DECORATE(cc_syms_constructor_get_type)();
  self = (cc_syms_constructor *)cc_object_allocate_2(_type);

  ((cc_symbol*)self)->name = make_constructor_name(syms, suffix)->string;
  ((cc_symbol*)self)->flags = CC_SYMBOL_FLAGS_CONSTRUCTOR;
  ((cc_symbol*)self)->enclosing = enclosing;
  self->suffix = suffix;
  self->parameters = cc_arraylist_create(0);
  cc_arraylist_append(enclosing->enclosed, (cc_object*)self);
  ((cc_symbol*)self)->next = syms->first; syms->first = ((cc_symbol*)self);
  ((cc_symbol*)self)->qualified_name = make_fully_qualified_name(syms, (cc_symbol*)self);

  return (cc_symbol *)self;
}

cc_symbol* cc_syms_make_constructor(cc_syms *self, cc_symbol* enclosing, cc_cstring* suffix)
{ return cc_syms_constructor_create(self, enclosing, suffix); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_syms_destructor_visit(cc_syms_destructor *self)
{
  CC_VISIT(self->parameters);
}

CC_DEFINE_CLASS(cc_syms_destructor, cc_symbol, &cc_syms_destructor_visit, NULL, NULL, NULL)

// enclosing type must be a class type.
static cc_symbol* cc_syms_destructor_create(cc_syms* syms, cc_symbol* enclosing)
{
  CC_ASSERT_NOT_NULL(syms);
  CC_ASSERT_NOT_NULL(enclosing);

  if ((enclosing->flags & CC_SYMBOL_FLAGS_CLASS) == 0)
  { cc_error(CC_EPERM); }

  cc_syms_destructor* self = (cc_syms_destructor *)cc_sym_find_enclosed_2(enclosing, CC_SEARCH_FLAGS_DESTRUCTORS, NULL);
  if (self)
  { cc_error(CC_EPERM); }
  
  cc_type* _type = CC_DECORATE(cc_syms_destructor_get_type)();
  self = (cc_syms_destructor *)cc_object_allocate_2(_type);
  
  ((cc_symbol*)self)->name = make_destructor_name(syms)->string;
  ((cc_symbol*)self)->flags = CC_SYMBOL_FLAGS_DESTRUCTOR;
  ((cc_symbol*)self)->enclosing = enclosing;
  self->parameters = cc_arraylist_create(0);
  cc_arraylist_append(enclosing->enclosed, (cc_object*)self);
  ((cc_symbol*)self)->next = syms->first; syms->first = ((cc_symbol*)self);
  ((cc_symbol*)self)->qualified_name = make_fully_qualified_name(syms, (cc_symbol *)self);

  return (cc_symbol *)self;
}

cc_symbol* cc_syms_make_destructor(cc_syms* self, cc_symbol* enclosing)
{ return cc_syms_destructor_create(self, enclosing); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DEFINE_CLASS(cc_syms_class_type, cc_symbol, NULL, NULL, NULL, NULL)

static cc_symbol*
cc_syms_class_type_create
  (
    cc_syms* syms,
    cc_symbol* enclosing,
    cc_cstring *name
  )
{
  CC_ASSERT_NOT_NULL(syms);
  CC_ASSERT_NOT_NULL(enclosing);
  CC_ASSERT_NOT_NULL(name);

  if ((enclosing->flags & CC_SYMBOL_FLAGS_NAMESPACE) == 0)
  { cc_error(CC_EPERM); }

  cc_syms_class_type* self = (cc_syms_class_type*)cc_sym_find_enclosed_2(enclosing, CC_SEARCH_FLAGS_CLASS_TYPES, name);
  if (self)
  { cc_error(CC_EPERM); }

  self = (cc_syms_class_type *)cc_object_allocate_2(CC_DECORATE(cc_syms_class_type_get_type)());
  
  ((cc_symbol*)self)->flags = CC_SYMBOL_FLAGS_CLASS;
  ((cc_symbol*)self)->enclosing = enclosing;
  ((cc_symbol*)self)->name = name;
  ((cc_symbol*)self)->enclosed = cc_arraylist_create(0);
  cc_arraylist_append(enclosing->enclosed, (cc_object*)self);
  ((cc_symbol*)self)->next = syms->first; syms->first = ((cc_symbol*)self);
  ((cc_symbol*)self)->qualified_name = make_fully_qualified_name(syms, (cc_symbol *)self);

  return (cc_symbol*)self;
}

cc_symbol* cc_syms_make_class_type(cc_syms *self, cc_symbol* enclosing, cc_cstring* name)
{ return cc_syms_class_type_create(self, enclosing, name); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DEFINE_CLASS(cc_syms_structure_type, cc_symbol, NULL, NULL, NULL, NULL)

static cc_symbol* cc_syms_structure_type_create(cc_syms* syms, cc_symbol* enclosing, cc_cstring* name)
{
  CC_ASSERT_NOT_NULL(syms);
  CC_ASSERT_NOT_NULL(enclosing);
  CC_ASSERT_NOT_NULL(name);

  if ((enclosing->flags & CC_SYMBOL_FLAGS_NAMESPACE) == 0)
  { cc_error(CC_EPERM); }

  cc_symbol* self = cc_sym_find_enclosed_2(enclosing, CC_SEARCH_FLAGS_STRUCTURE_TYPES, name);
  if (self)
  { return self; }

  self = (cc_symbol*)cc_object_allocate_2(CC_DECORATE(cc_symbol_get_type)());
  ((cc_symbol*)self)->flags = CC_SYMBOL_FLAGS_STRUCTURE;
  ((cc_symbol*)self)->enclosed = cc_arraylist_create(0);
  ((cc_symbol*)self)->name = name;
  ((cc_symbol*)self)->enclosing = enclosing;
  cc_arraylist_append(enclosing->enclosed, (cc_object*)self);
  self->next = syms->first; syms->first = self;
  ((cc_symbol*)self)->qualified_name = make_fully_qualified_name(syms, self);

  return self;
}

cc_symbol* cc_syms_make_structure(cc_syms *self, cc_symbol* enclosing, cc_cstring* name)
{ return cc_syms_structure_type_create(self, enclosing, name); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DEFINE_CLASS(cc_syms_enumeration_type, cc_object, NULL, NULL, NULL, NULL)

static cc_symbol* cc_syms_enumeration_type_create(cc_syms* syms, cc_symbol* enclosing, cc_cstring* name)
{
  CC_ASSERT_NOT_NULL(syms);
  CC_ASSERT_NOT_NULL(enclosing);
  CC_ASSERT_NOT_NULL(name);

  if ((enclosing->flags & CC_SYMBOL_FLAGS_NAMESPACE) == 0)
  { cc_error(CC_EPERM); }

  cc_symbol* self = cc_sym_find_enclosed_2(enclosing, CC_SEARCH_FLAGS_ENUMERATION_TYPES, name);
  if (self)
  { return self; }

  self = (cc_symbol*)cc_object_allocate_2(CC_DECORATE(cc_syms_enumeration_type_get_type)());

  self->flags = CC_SYMBOL_FLAGS_ENUMERATION;
  self->name = name;
  self->enclosed = cc_arraylist_create(0);
  self->enclosing = enclosing;
  cc_arraylist_append(enclosing->enclosed, (cc_object*)self);
  self->next = syms->first; syms->first = self;
  ((cc_symbol*)self)->qualified_name = make_fully_qualified_name(syms, self);

  return self;
}

cc_symbol* cc_syms_make_enumeration(cc_syms *self, cc_symbol* enclosing, cc_cstring* name)
{ return cc_syms_enumeration_type_create(self, enclosing, name); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DEFINE_CLASS(cc_syms_namespace, cc_object, NULL, NULL, NULL, NULL)

static cc_symbol* cc_syms_namespace_create(cc_syms* syms, cc_symbol* enclosing, cc_cstring* name)
{
  CC_ASSERT_NOT_NULL(syms);
  CC_ASSERT_NOT_NULL(enclosing);
  CC_ASSERT_NOT_NULL(name);

  cc_symbol* self = cc_sym_find_enclosed_2(enclosing, CC_SEARCH_FLAGS_NAMESPACES, name);
  if (self)
  { return self; }

  self = (cc_symbol*)cc_object_allocate_2(CC_DECORATE(cc_syms_namespace_get_type)());

  self->flags = CC_SYMBOL_FLAGS_NAMESPACE;
  self->name = name;
  self->enclosed = cc_arraylist_create(0);
  self->enclosing = enclosing;
  cc_arraylist_append(enclosing->enclosed, (cc_object*)self);
  self->next = syms->first; syms->first = self;
  ((cc_symbol*)self)->qualified_name = make_fully_qualified_name(syms, self);

  return self;
}

cc_symbol* cc_syms_get_or_create_namespace(cc_syms *self, cc_symbol* enclosing, cc_cstring* name)
{ return cc_syms_namespace_create(self, enclosing, name); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_syms_module_visit(cc_syms_module* self)
{ 
  CC_VISIT(self->module_path);
}

CC_DEFINE_CLASS(cc_syms_module, cc_symbol, &cc_syms_module_visit, NULL, NULL, NULL)

static cc_symbol* cc_syms_module_create(cc_syms* syms, cc_symbol* enclosing, cc_cstring* name)
{
  CC_ASSERT_NOT_NULL(syms);
  CC_ASSERT_NOT_NULL(enclosing);
  CC_ASSERT_NOT_NULL(name);

  if ((enclosing->flags & CC_SYMBOL_FLAGS_PROGRAM) == 0)
  { cc_error(CC_EINVAL); }

  cc_symbol* self = cc_sym_find_enclosed_2(enclosing, CC_SEARCH_FLAGS_MODULES, name);
  if (self)
  { return self; }

  self = (cc_symbol*)cc_object_allocate_2(CC_DECORATE(cc_syms_module_get_type)());

  self->flags = CC_SYMBOL_FLAGS_MODULE;
  self->name = name;
  ((cc_syms_module *)self)->module_path = name;
  self->enclosed = cc_arraylist_create(0);
  self->enclosing = enclosing;
  cc_arraylist_append(enclosing->enclosed, (cc_object*)self);
  self->next = syms->first; syms->first = self;
  ((cc_symbol*)self)->qualified_name = make_fully_qualified_name(syms, self);

  return self;
}

cc_symbol* cc_syms_get_or_create_module(cc_syms* self, cc_symbol* enclosing, cc_cstring *name)
{ return cc_syms_module_create(self, enclosing, name); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_syms_member_variable_visit(cc_syms_member_variable* self)
{
  CC_VISIT(self->initializer);
}

CC_DEFINE_CLASS(cc_syms_member_variable, cc_symbol, &cc_syms_member_variable_visit, NULL, NULL, NULL)

static cc_symbol* cc_syms_member_variable_create(cc_syms* syms, cc_symbol* enclosing, cc_cstring* name)
{
  CC_ASSERT_NOT_NULL(syms);
  CC_ASSERT_NOT_NULL(enclosing);
  CC_ASSERT_NOT_NULL(name);

  if ((enclosing->flags & CC_SYMBOL_FLAGS_CLASS) == 0 && (enclosing->flags & CC_SYMBOL_FLAGS_ENUMERATION) == 0)
  { cc_error(CC_EINVAL); }

  cc_symbol *self = (cc_symbol*)cc_object_allocate_2(CC_DECORATE(cc_syms_member_variable_get_type)());

  self->flags = CC_SYMBOL_FLAGS_MEMBER_VARIABLE;
  self->name = name;
  self->enclosing = enclosing;
  cc_arraylist_append(enclosing->enclosed, (cc_object*)self);
  self->next = syms->first; syms->first = self;
  ((cc_symbol*)self)->qualified_name = make_fully_qualified_name(syms, self);

  return self;
}

cc_symbol* cc_syms_make_member_variable(cc_syms* self, cc_symbol* enclosing, cc_cstring* name)
{ return cc_syms_member_variable_create(self, enclosing, name); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DEFINE_CLASS(cc_syms_parameter_variable, cc_symbol, NULL, NULL, NULL, NULL)

static cc_symbol* cc_syms_parameter_variable_create(cc_syms* syms, cc_symbol* enclosing, cc_cstring* name)
{
  CC_ASSERT_NOT_NULL(syms);
  CC_ASSERT_NOT_NULL(enclosing);
  CC_ASSERT_NOT_NULL(name);

  if ((enclosing->flags & CC_SYMBOL_FLAGS_CONSTRUCTOR) == 0 &&
      (enclosing->flags & CC_SYMBOL_FLAGS_DESTRUCTOR) == 0 &&
      (enclosing->flags & CC_SYMBOL_FLAGS_METHOD) == 0)
  { cc_error(CC_EINVAL); }

  cc_symbol* self = cc_sym_alloc(syms, CC_SYMBOL_FLAGS_PARAMETER_VARIABLE);

  self->name = name;
  self->enclosing = enclosing;

  if ((enclosing->flags & CC_SYMBOL_FLAGS_CONSTRUCTOR) == CC_SYMBOL_FLAGS_CONSTRUCTOR)
    cc_arraylist_append(((cc_syms_constructor*)enclosing)->parameters, (cc_object*)self);
  else if ((enclosing->flags & CC_SYMBOL_FLAGS_DESTRUCTOR) == CC_SYMBOL_FLAGS_DESTRUCTOR)
    cc_arraylist_append(((cc_syms_constructor*)enclosing)->parameters, (cc_object*)self);
  else if ((enclosing->flags & CC_SYMBOL_FLAGS_METHOD) == CC_SYMBOL_FLAGS_METHOD)
    cc_arraylist_append(((cc_syms_method*)enclosing)->parameters, (cc_object*)self);
  else
    cc_arraylist_append(((cc_syms_method*)enclosing)->parameters, (cc_object*)self);

  return self;
}

cc_symbol* cc_syms_make_parameter_variable(cc_syms* self, cc_symbol* enclosing, cc_cstring* name)
{ return cc_syms_parameter_variable_create(self, enclosing, name); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DEFINE_CLASS(cc_syms_scalar_type, cc_symbol, NULL, NULL, NULL, NULL)

static cc_symbol* cc_syms_scalar_type_create(cc_syms* syms, cc_symbol* enclosing, cc_cstring* name)
{
  CC_ASSERT_NOT_NULL(syms);
  CC_ASSERT_NOT_NULL(enclosing);
  CC_ASSERT_NOT_NULL(name);

  if ((enclosing->flags & CC_SYMBOL_FLAGS_NAMESPACE) == 0)
  { cc_error(CC_EINVAL); }

  for (size_t i = 0, n = cc_arraylist_get_size(enclosing->enclosed); i < n; ++i)
  {
    cc_symbol* enclosed = (cc_symbol*)cc_arraylist_get_at(enclosing->enclosed, i);
    if ((enclosed->flags & CC_SYMBOL_FLAGS_SCALAR) == CC_SYMBOL_FLAGS_SCALAR && cc_cstring_equal(enclosed->name, name))
    { cc_error(CC_EINVAL); }
  }
  cc_syms_scalar_type* self = (cc_syms_scalar_type*)cc_object_allocate_2(CC_DECORATE(cc_syms_scalar_type_get_type)());

  ((cc_symbol*)self)->flags = CC_SYMBOL_FLAGS_SCALAR;
  ((cc_symbol*)self)->name = name;
  ((cc_symbol*)self)->enclosing = enclosing;
  cc_arraylist_append(enclosing->enclosed, (cc_object*)self);
  ((cc_symbol*)self)->next = syms->first; syms->first = ((cc_symbol*)self);
  ((cc_symbol*)self)->qualified_name = make_fully_qualified_name(syms, (cc_symbol*)self);

  return (cc_symbol*)self;
}

cc_symbol* cc_syms_make_scalar_type(cc_syms* self, cc_symbol* enclosing, cc_name* name)
{ return cc_syms_scalar_type_create(self, enclosing, name->string); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void cc_syms_array_type_visit(cc_syms_array_type* self)
{
  CC_VISIT(self->inner_type);
}

CC_DEFINE_CLASS(cc_syms_array_type, cc_symbol, &cc_syms_array_type_visit, NULL, NULL, NULL)

static cc_syms_array_type* cc_syms_array_type_create(cc_syms* syms, cc_symbol* enclosing, cc_symbol* inner_type)
{
  CC_ASSERT_NOT_NULL(syms);
  CC_ASSERT_NOT_NULL(enclosing);
  CC_ASSERT_NOT_NULL(inner_type);

  if ((enclosing->flags & CC_SYMBOL_FLAGS_NAMESPACE) == 0)
  {
    cc_error(CC_EINVAL);
  }

  if ((inner_type->flags & CC_SYMBOL_FLAGS_CLASS) == 0 &&
      (inner_type->flags & CC_SYMBOL_FLAGS_SCALAR) == 0 &&
      (inner_type->flags & CC_SYMBOL_FLAGS_STRUCTURE) == 0 &&
      (inner_type->flags & CC_SYMBOL_FLAGS_ENUMERATION) == 0)
  {
    cc_error(CC_EINVAL);
  }

  cc_syms_array_type* self = (cc_syms_array_type*)cc_object_allocate_2(CC_DECORATE(cc_syms_array_type_get_type)());

  cc_cstring* name = make_array_type_name(syms, inner_type);
  ((cc_symbol*)self)->flags = CC_SYMBOL_FLAGS_ARRAY;
  self->inner_type = inner_type;
  ((cc_symbol*)self)->enclosing = enclosing;
  ((cc_symbol*)self)->name = name;
  cc_arraylist_append(enclosing->enclosed, (cc_object*)self);
  ((cc_symbol*)self)->next = syms->first; syms->first = ((cc_symbol*)self);

  return self;
}

cc_symbol* cc_syms_get_or_create_array_type(cc_syms* self, cc_symbol* enclosing, cc_symbol* inner_type)
{ return (cc_symbol *)cc_syms_array_type_create(self, enclosing, inner_type); }
