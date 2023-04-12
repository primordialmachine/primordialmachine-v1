/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#include "spectre/emit/referenced_symbols.h"

#include "spectre/cc_emit-protected.h"

static bool already_included(cc_arraylist* referenced_symbols, cc_symbol* symbol)
{
  for (size_t i = 0, n = cc_arraylist_get_size(referenced_symbols); i < n; ++i)
  {
    cc_symbol* e = (cc_symbol*)cc_arraylist_get_at(referenced_symbols, i);
    if (e == symbol)
    {
      return true;
    }
  }
  return false;
}

static void maybe_add(cc_arraylist* referenced_symbols, cc_symbol* symbol)
{
  if (!already_included(referenced_symbols, symbol))
  {
    cc_arraylist_append(referenced_symbols, (cc_object*)symbol);
  }
}

static void compute_for_type(cc_symbol* symbol, cc_arraylist* referenced_symbols)
{
  while ((symbol->flags & CC_SYMBOL_FLAGS_ARRAY) == CC_SYMBOL_FLAGS_ARRAY)
  {
    symbol = ((cc_syms_array_type*)symbol)->inner_type;
  }
  if ((symbol->flags & CC_SYMBOL_FLAGS_BUILTIN) == 0)
  {
    maybe_add(referenced_symbols, symbol);
  }
}

static void compute_for_member_variable(cc_symbol* symbol, cc_arraylist* referenced_symbols)
{
  cc_symbol* type_symbol = symbol->type;
  compute_for_type(type_symbol, referenced_symbols);
}

static void compute_for_parameter(cc_symbol* symbol, cc_arraylist* referenced_symbols)
{
  cc_symbol* type_symbol = symbol->type;
  compute_for_type(type_symbol, referenced_symbols);
}

static void compute_for_constructor(cc_symbol* symbol, cc_arraylist* referenced_symbols)
{
  for (size_t i = 0, n = cc_arraylist_get_size(((cc_syms_constructor*)symbol)->parameters); i < n; ++i)
  {
    cc_symbol* parameter_symbol = (cc_symbol*)cc_arraylist_get_at(((cc_syms_constructor*)symbol)->parameters, i);
    compute_for_parameter(parameter_symbol, referenced_symbols);
  }
}

static void compute_for_destructor(cc_symbol* symbol, cc_arraylist* referenced_symbols)
{
  for (size_t i = 0, n = cc_arraylist_get_size(((cc_syms_destructor*)symbol)->parameters); i < n; ++i)
  {
    cc_symbol* parameter_symbol = (cc_symbol*)cc_arraylist_get_at(((cc_syms_destructor*)symbol)->parameters, i);
    compute_for_parameter(parameter_symbol, referenced_symbols);
  }
}

static void compute_for_method(cc_symbol* symbol, cc_arraylist* referenced_symbols)
{
  for (size_t i = 0, n = cc_arraylist_get_size(((cc_syms_method*)symbol)->parameters); i < n; ++i)
  {
    cc_symbol* parameter_symbol = (cc_symbol*)cc_arraylist_get_at(((cc_syms_method*)symbol)->parameters, i);
    compute_for_parameter(parameter_symbol, referenced_symbols);
  }
  compute_for_type(((cc_syms_method*)symbol)->result, referenced_symbols);
}

static void compute(cc_emit* self, cc_symbol* symbol, cc_arraylist* referenced_symbols)
{
  if ((symbol->flags & (CC_SYMBOL_FLAGS_CLASS | CC_SYMBOL_FLAGS_ENUMERATION)) == 0 ||
      (symbol->flags & CC_SYMBOL_FLAGS_BUILTIN) == CC_SYMBOL_FLAGS_BUILTIN)
  { cc_error(CC_EINVAL); }

  // Add the parent symbol of a class.
  // Compute the includes of the class members.
  if ((symbol->flags & CC_SYMBOL_FLAGS_CLASS) == CC_SYMBOL_FLAGS_CLASS)
  {
    if ((symbol->parent->flags & CC_SYMBOL_FLAGS_BUILTIN) == 0)
    {
      maybe_add(referenced_symbols, symbol->parent);
    }
    for (size_t i = 0, n = cc_arraylist_get_size(symbol->enclosed); i < n; ++i)
    {
      cc_symbol* enclosed_symbol = (cc_symbol*)cc_arraylist_get_at(symbol->enclosed, i);
      switch (enclosed_symbol->flags & CC_SYMBOL_FLAGS_MEMBER_MASK)
      {
      case CC_SYMBOL_FLAGS_CONSTRUCTOR:
        compute_for_constructor(enclosed_symbol, referenced_symbols);
        break;
      case CC_SYMBOL_FLAGS_DESTRUCTOR:
        compute_for_destructor(enclosed_symbol, referenced_symbols);
        break;
      case CC_SYMBOL_FLAGS_METHOD:
        compute_for_method(enclosed_symbol, referenced_symbols);
        break;
      case CC_SYMBOL_FLAGS_MEMBER_VARIABLE:
        compute_for_member_variable(enclosed_symbol, referenced_symbols);
        break;
      }
    }
  }
}

cc_arraylist*
cc_emit_get_referenced_symbols
  (
    cc_emit* self,
    cc_symbol* symbol
  )
{
  cc_arraylist* referenced_symbols = cc_arraylist_create(0);
  compute(self, symbol, referenced_symbols);
  return referenced_symbols;
}
