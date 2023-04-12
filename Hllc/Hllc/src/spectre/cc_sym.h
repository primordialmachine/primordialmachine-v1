/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */

/// cc_syms The symbols of a program.

#if !defined(CC_SYM_H_INCLUDED)
#define CC_SYM_H_INCLUDED


#include "cc_tree.h"
#include "cc_context.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Represents a symbol of a program.
/// @extends cc_object
/// @abstract
CC_DECLARE_ABSTRACT_CLASS(cc_symbol, cc_object)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

BEGIN_DECLARE_COMPONENT(cc_syms)

  cc_arraylist* scratch_list;
  cc_cstring_buffer* scratch_buffer;
  cc_spectre_names* names;

  cc_symbol *first;

  cc_symbol* PROGRAM;

  cc_symbol* BOOLEAN;
  cc_symbol* VOID;

  cc_symbol* REAL;
  cc_symbol* REAL32;
  cc_symbol* REAL64;

  cc_symbol* SIZE;
  
  cc_symbol* INTEGER;
  cc_symbol* INTEGER8;
  cc_symbol* INTEGER16;
  cc_symbol* INTEGER32;
  cc_symbol* INTEGER64;

  cc_symbol* NATURAL;
  cc_symbol* NATURAL8;
  cc_symbol* NATURAL16;
  cc_symbol* NATURAL32;
  cc_symbol* NATURAL64;


END_DECLARE_COMPONENT(cc_syms)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define DEFINE(NAME, DESCRIPTION, INDEX) \
  CC_SYMBOL_FLAGS_##NAME = (1 << INDEX),

typedef enum cc_symbol_flags
{

  /// @brief Symbol flag denoting a "class type" symbol.
  DEFINE(CLASS, "<class>", 0)

  /// @brief Symbol flag denoting an "enumeration type" symbol.
  DEFINE(ENUMERATION, "<enumeration>", 1)

  /// @brief Symbol flag denoting an "interface type" symbol.
  DEFINE(INTERFACE, "<interface>", 2)

  /// @brief Symbol flag denoting a "member variable" symbol.
  DEFINE(MEMBER_VARIABLE, "<member variable>", 3)

  /// @brief Symbol flag denoting a "parameter variable" symbol.
  DEFINE(PARAMETER_VARIABLE, "<parameter variable>", 4)

  /// @brief Symbol flag denoting a "module" symbol.
  DEFINE(MODULE, "<module>", 5)

  /// @brief Symbol flag denoting a "namespace" symbol.
  DEFINE(NAMESPACE, "<namespace>", 6)

  /// @brief Symbol flag denoting a "method" symbol.
  DEFINE(METHOD, "<method>", 7)

  /// @brief Symbol flag denoting a "constructor" symbol.
  DEFINE(CONSTRUCTOR, "<constructor>", 8)

  /// @brief Symbol flag denoting a "destructor" symbol.
  DEFINE(DESTRUCTOR, "<destructor>", 9)

  /// @brief Symbol flag denoting a "scalar type" symbol.
  DEFINE(SCALAR, "<scalar>", 10)

  /// @brief Symbol flag denoting a "structure" symbol.
  DEFINE(STRUCTURE, "<structure>", 11)

  /// @brief Symbol flag denoting an "array" symbol.
  DEFINE(ARRAY, "<array>", 12)

  /// @brief A class can be an abstract class, a method can be an abstract method.
  DEFINE(ABSTRACT, "<abstract>", 13)

  /// @brief A method can be a static method.
  DEFINE(STATIC, "<static>", 14)

  // @brief A class can be a sealed class, a method can be sealed method.
  DEFINE(SEALED, "<sealed>", 15)

  /// @brief A parameter can be an out parameter.
  DEFINE(OUT, "<out>", 16)

  /// @brief Callables can be private.
  DEFINE(PRIVATE, "<private>", 17)

  /// @brief Callables can be protected.
  DEFINE(PROTECTED, "<protected>", 18)

  /// @brief Callables can be public.
  DEFINE(PUBLIC, "<public>", 19)

  /// @brief Any symbol can be a builtin symbol.
  DEFINE(BUILTIN, "<builtin>", 20)

  /// @brief A method symbol can be an override.
  DEFINE(OVERRIDE, "<override>", 21)

  /// @brief Symbol flag denoting a "program" symbol.
  DEFINE(PROGRAM, "<program>", 22)

  DEFINE(FOREIGN, "<foreign>", 23)

} cc_symbol_flags;

#undef DEFINE

/// @brief Mask for the "builtin" category flags (builtin).
#define CC_SYMBOL_FLAGS_BUILTIN_MASK (CC_SYMBOL_FLAGS_BUILTIN)

/// @brief Mask for the "access modifier" category flags (public, protected, and private).
#define CC_SYMBOL_FLAGS_ACCESS_MODIFIER_MASK (CC_SYMBOL_FLAGS_PUBLIC | CC_SYMBOL_FLAGS_PROTECTED | CC_SYMBOL_FLAGS_PRIVATE)

/// @brief Mask for the "modifier" category flags (abstract, static, sealed)
#define CC_SYMBOL_FLAGS_MODIFIER_MASK (CC_SYMBOL_FLAGS_ABSTRACT | CC_SYMBOL_FLAGS_SEALED | CC_SYMBOL_FLAGS_STATIC | CC_SYMBOL_FLAGS_OUT | CC_SYMBOL_FLAGS_ACCESS_MODIFIER_MASK)

/// @brief Mask for the "callable" category flags (methods, constructors, destructors).
#define CC_SYMBOL_FLAGS_CALLABLE_MASK (CC_SYMBOL_FLAGS_METHOD | CC_SYMBOL_FLAGS_CONSTRUCTOR | CC_SYMBOL_FLAGS_DESTRUCTOR)

/// @brief Mask for the "type" category flags (array, class, enumeration, scalar, structure).
#define CC_SYMBOL_FLAGS_TYPE_MASK (CC_SYMBOL_FLAGS_ARRAY | CC_SYMBOL_FLAGS_CLASS | CC_SYMBOL_FLAGS_ENUMERATION | CC_SYMBOL_FLAGS_SCALAR | CC_SYMBOL_FLAGS_STRUCTURE)

#define CC_SYMBOL_FLAGS_MEMBER_CALLABLE_MASK (CC_SYMBOL_FLAGS_CONSTRUCTOR | CC_SYMBOL_FLAGS_DESTRUCTOR | CC_SYMBOL_FLAGS_METHOD)

/// @brief Mask for the "member" category flags (constructors, destructors, member variables, methods)
#define CC_SYMBOL_FLAGS_MEMBER_MASK (CC_SYMBOL_FLAGS_MEMBER_CALLABLE_MASK | CC_SYMBOL_FLAGS_MEMBER_VARIABLE)

struct cc_symbol
{
  cc_object __parent;
  cc_tree* source;            // pointer to the source of the symbol in the source code. null pointer if built-in.
  cc_symbol* next;
  cc_symbol_flags flags;

  cc_cstring* name;           // CC_SYMBOL_FLAGS_(CLASS|ENUMERATION|INTERFACE|SCALAR|STRUCTURE|PARAMETER_VARIABLE|MEMBER_VARIABLE) : unqualified name,
  cc_name* qualified_name;    //                              "                                                             : fully qualified name.

  cc_symbol* parent;          // CC_SYMBOL_FLAGS_(CLASS). The parent class if any, null otherwise.


  cc_symbol* type;            // CC_SYMBOL_FLAGS_MEMBER_VARIABLE: The type of the member variable or null.
  cc_symbol* enclosing;       // CC_SYMBOL_FLAGS_(CLASS|CONSTRUCTOR|DESTRUCTOR|ENUMERATION|INTERFACE|MODULE|NAMESPACE|VARIABLE). The symbol enclosing this symbol.
  cc_arraylist *enclosed;     // CC_SYMBOL_FLAGS_(CLASS|CONSTRUCTOR|DESTRUCTOR|ENUMERATION|INTERFACE|MODULE|NAMESPACE|VARIABLE). The symbols enclosed by this symbol.
};

#define DEFINE(NAME, FLAG) \
  static inline bool \
  cc_symbol_is_##NAME \
    ( \
      cc_symbol* self \
    ) \
  { \
    CC_ASSERT_NOT_NULL(self); \
    return FLAG == (self->flags & FLAG); \
  }

DEFINE(class, CC_SYMBOL_FLAGS_CLASS)
DEFINE(enumeration, CC_SYMBOL_FLAGS_ENUMERATION)
DEFINE(interface, CC_SYMBOL_FLAGS_INTERFACE)
DEFINE(method, CC_SYMBOL_FLAGS_METHOD)
DEFINE(constructor, CC_SYMBOL_FLAGS_CONSTRUCTOR)
DEFINE(destructor, CC_SYMBOL_FLAGS_DESTRUCTOR)
DEFINE(module, CC_SYMBOL_FLAGS_MODULE)
DEFINE(namespace, CC_SYMBOL_FLAGS_NAMESPACE)
DEFINE(scalar, CC_SYMBOL_FLAGS_SCALAR)

#undef DEFINE

typedef enum cc_search_flags
{
  /// @brief Consider class types.
  CC_SEARCH_FLAGS_CLASS_TYPES = (1 << 1),

  /// @brief Consider enumeration types.
  CC_SEARCH_FLAGS_ENUMERATION_TYPES = (1 << 2),

  /// @brief Consider interface types.
  CC_SEARCH_FLAGS_INTERFACE_TYPES = (1 << 3),

  /// @brief Consider structure types.
  CC_SEARCH_FLAGS_STRUCTURE_TYPES = (1 << 4),

  /// @brief Consider scalar types.
  CC_SEARCH_FLAGS_SCALAR_TYPES = (1 << 5),

  /// @brief Consider methods.
  CC_SEARCH_FLAGS_METHODS = (1 << 6),
  
  /// @brief Consider member variables.
  CC_SEARCH_FLAGS_MEMBER_VARIABLES = (1 << 7),

  /// @brief Consider parameter variables.
  CC_SEARCH_FLAGS_PARAMETER_VARIABLES = (1 << 8),

  /// @brief Consider constructors.
  CC_SEARCH_FLAGS_CONSTRUCTORS = (1 << 9),

  /// @brief Consider destructors.
  CC_SEARCH_FLAGS_DESTRUCTORS = (1 << 10),

  /// @brief Consider namespaces.
  CC_SEARCH_FLAGS_NAMESPACES = (1 << 11),

  /// @brief Consider modules.
  CC_SEARCH_FLAGS_MODULES = (1 << 12),

} cc_search_flags;

/// @brief Find the first symbol with the specified properties enclosed by the specified symbol.
/// @param enclosing The enclosing symbol.
/// @param flags The search flags. A bitwise or of cc_search_flags values.
/// @param name A name or null.
/// @return A pointer to the first symbol with the specified properties.
/// @remark
/// A candidate symbol is accepted if all of the following conditions are met:
/// - Symbol is of a kind denoted by @a flags.
/// - @a name is null OR the symbol's name is @a name.
cc_symbol* cc_sym_find_enclosed_2(cc_symbol* enclosing, cc_search_flags flags, cc_cstring* name);

/// @brief Get the fully qualified name of this symbol.
/// @param self This symbol.
/// @return The fully qualified name.
cc_cstring* cc_sym_get_fqn(cc_symbol* self);

/// @brief Find the closest module symbol enclosing this symbol.
/// @param self This symbol.
/// @return A pointer to the enclosing symbol if any, a null pointer otherwise.
cc_symbol* cc_sym_get_enclosing_module(cc_symbol* self);

/**
 * @brief
 * Get the first symbol.
 * @param ctx
 * The context.
 * @return
 * A pointer to the first symbol if the symbol exists.
 * A null pointer otherwise.
 */
cc_symbol* cc_sym_first(cc_ctx* ctx);

/**
 * @brief
 * Get the next symbol.
 * @param sym
 * A pointer to a symbol.
 * @return
 * A pointer to the next symbol if the symbol exists.
 * A null pointer otherwise.
 */
cc_symbol* cc_sym_next(cc_symbol *sym);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Symbol representing a method.
/// The name is <code>&lt;program&gt</code>.
CC_DECLARE_CLASS(cc_syms_program, cc_symbol)

struct cc_syms_program
{
  cc_symbol _parent;
};

/// @brief Create a program symbol.
/// @param self This symbol factory.
/// @return A pointer to the program symbol.
cc_symbol* cc_syms_make_program(cc_syms* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Symbol representing a method.
CC_DECLARE_CLASS(cc_syms_method, cc_symbol)

struct cc_syms_method
{
  cc_symbol _parent;

  /// @brief The list of parameters.
  cc_arraylist* parameters;

  /// @brief The return type.
  cc_symbol* result;

  /// @brief The method this method is overriding.
  cc_symbol* override;
};

/// @brief Create a method symbol in the specified enclosing symbol.
/// @param self This symbol factory.
/// @param enclosing The enclosing symbol.
/// @param name The unqualified name of the method.
/// @pre The specified enclosing symbol must be a class or enumeration symbol.
cc_symbol* cc_syms_make_method(cc_syms* self, cc_symbol* enclosing, cc_cstring* name);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Symbol representing a constructor.
CC_DECLARE_CLASS(cc_syms_constructor, cc_symbol)

struct cc_syms_constructor
{
  cc_symbol _parent;

  /// @brief The list of parameters.
  cc_arraylist* parameters;

  /// @brief The constructor's suffix.
  cc_cstring* suffix;
};

/// @brief Create a constructor symbol in the specified enclosing symbol.
/// @param self This symbol factory.
/// @param enclosing The enclosing symbol.
/// @param suffix The constructor's suffix or null.
/// @pre The specified enclosing symbol must be a class symbol.
/// @remark
/// The name of the constructor is `'<constructor>' '.' suffix` if @a suffix is not null.
/// Otherwise the name is `<constructor>`.`
cc_symbol* cc_syms_make_constructor(cc_syms* self, cc_symbol* enclosing, cc_cstring *suffix);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Symbol representing a destructor.
CC_DECLARE_CLASS(cc_syms_destructor, cc_symbol)

struct cc_syms_destructor
{
  cc_symbol _parent;

  /// @brief The list of parameters.
  cc_arraylist* parameters;
};

/// @brief Create a destructor symbol in the specified enclosing symbol.
/// @param self This symbol factory.
/// @param enclosing A pointer to the enclosing symbol.
/// @remark The specified enclosing symbol must be a class symbol.
/// @remark
/// The name of the destructor is `'<destructor>`.
cc_symbol* cc_syms_make_destructor(cc_syms *self, cc_symbol* enclosing);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A symbol representing a class type.
CC_DECLARE_CLASS(cc_syms_class_type, cc_symbol)

struct cc_syms_class_type
{ cc_symbol parent; };

/// @brief Ensure a cass type symbol of the specified unqualified name exists in the specified enclosing symbol.
/// @param self This symbol factory.
/// @param enclosing A pointer to the enclosing symbol.
/// @param name A pointer to the unqualified name of the class.
/// @remark The specified enclosing symbol must be a namespace symbol.
/// @return A pointer to the class type symbol on success, a null pointer on failure.
cc_symbol* cc_syms_make_class_type(cc_syms *self, cc_symbol* enclosing, cc_cstring* name);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A symbol representing a structure type.
CC_DECLARE_CLASS(cc_syms_structure_type, cc_symbol)

struct cc_syms_structure_type
{ cc_symbol parent; };

/// @brief Ensure a structure symbol of the specified unqualified name exists in the specified enclosing symbol.
/// @param self This symbol factory.
/// @param enclosing A pointer to the enclosing symbol.
/// @param name A pointer to the unqualified name of the structure.
/// @remark The specified enclosing symbol must be a namespace symbol.
/// @return A pointer to the structure symbol on success, a null pointer on failure.
cc_symbol* cc_syms_make_structure(cc_syms *self, cc_symbol* enclosing, cc_cstring* name);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A symbol representing an enumeration type.
CC_DECLARE_CLASS(cc_syms_enumeration_type, cc_symbol)

struct cc_syms_enumeration_type
{ cc_symbol parent; };

/// @brief Ensure an enumeration symbol of the specified unqualified name exists in the specified enclosing symbol.
/// @param self This symbol factory.
/// @param enclosing A pointer to the enclosing symbol.
/// @param name A pointer to the unqualified name of the enumeration.
/// @remark The specified enclosing symbol must be a namespace symbol.
/// @return A pointer to the enumeration symbol on success, a null pointer on failure.
cc_symbol* cc_syms_make_enumeration(cc_syms *self, cc_symbol* enclosing, cc_cstring* name);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A symbol representing a namespace.
CC_DECLARE_CLASS(cc_syms_namespace, cc_symbol)

struct cc_syms_namespace
{ cc_symbol parent; };

/// @brief Ensure a namespace symbol of the specified unqualified name exists in the specified enclosing symbol.
/// @param self The symbols.
/// @param enclosing A pointer to the enclosing symbol.
/// @param name A pointer to the unqualified name of the namespace.
/// @remark The specified enclosing symbol must be a namespace symbol or a module symbol.
/// @return A pointer to the namespace symbol on success, a null pointer on failure.
cc_symbol* cc_syms_get_or_create_namespace(cc_syms *self, cc_symbol* enclosing, cc_cstring* name);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A symbol representing a module.
CC_DECLARE_CLASS(cc_syms_module, cc_symbol)

struct cc_syms_module
{
  
  cc_symbol parent;

  /// @brief The path of the module.
  cc_cstring* module_path;

};

/**
 * @brief Ensure a module symbol of the specified name exists.
 * @param self The symbols.
 * @param enclosing A pointer to the enclosing symbol.
 * @param name A pointer to the qualified name of the module.
 * @return A pointer to the module symbol on success, a null pointer on failure.
 * @pre The enclosing symbol must be a program symbol.
 */
cc_symbol* cc_syms_get_or_create_module(cc_syms* self, cc_symbol* enclosing, cc_cstring* name);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A symbol representing a member variable.
CC_DECLARE_CLASS(cc_syms_member_variable, cc_symbol)

struct cc_syms_member_variable
{
  
  cc_symbol parent;

  /// @brief The initializer of the member variable or null.
  cc_tree* initializer;

};

/**
 * @brief Ensure a member variable symbol of the specified unqualified name exists in the specified enclosing symbol.
 * @param self The symbols.
 * @param enclosing A pointer to the enclosing symbol.
 * @param name A pointer to the unqualified name of the variable.
 * @remark The specified enclosing symbol must be a class or enumeration symbol.
 * @return A pointer to the member variable symbol on success, a null pointer on failure.
 */
cc_symbol* cc_syms_make_member_variable(cc_syms* self, cc_symbol* enclosing, cc_cstring* name);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A symbol representing a parameter variable.
CC_DECLARE_CLASS(cc_syms_parameter_variable, cc_symbol)

struct cc_syms_parameter_variable
{ cc_symbol parent; };

/**
 * @brief Ensure a parameter variable symbol of the specified unqualified name exists in the specified enclosing symbol.
 * @param self The symbols.
 * @param enclosing A pointer to the enclosing symbol.
 * @param name A pointer to the unqualified name of the variable.
 * @remark The specified enclosing symbol must be a constructor, destructor, or method symbol.
 * @return A pointer to the parameter variable symbol on success, a null pointer on failure.
 */
cc_symbol* cc_syms_make_parameter_variable(cc_syms *self, cc_symbol* enclosing, cc_cstring* name);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// @brief Symbol representing scalar type.
CC_DECLARE_CLASS(cc_syms_scalar_type, cc_symbol)

struct cc_syms_scalar_type
{ cc_symbol _parent; };

/// @brief Ensure a scalar type symbol NAME of the specified unqualified name eixsts in the specified enclosing symbol.
/// @param self The symbols.
/// @param enclosing A pointer to the enclosing symbol.
/// @param name A pointer to the unqualified name of the scalar type.
/// @remark
/// - The specified enclosing symbol must be a namespace symbol.
/// - No namespace and no type of the same name may exist in the specified enclosing symbol.
/// - The created symbol is a builtin symbol.
/// @return A pointer to the scalar type symbol.
cc_symbol* cc_syms_make_scalar_type(cc_syms *self, cc_symbol* enclosing, cc_name* name);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Symbol representing array type.
CC_DECLARE_CLASS(cc_syms_array_type, cc_symbol)

struct cc_syms_array_type
{
  cc_symbol _parent;

  /// @brief The inner type of this array type.
  cc_symbol* inner_type;
};

/// @brief Add an array type <code>[T]</code> symbol with the specified inner type <code>T</code> in the specified enclosing symbol.
/// @param self This symbol factory.
/// @param enclosing The enclosing symbol.
/// @param inner_type The inner type <code>T</code>.
/// @return A pointer to the array type.
/// @pre The specified enclosing symbol must be a namespace symbol.
cc_symbol* cc_syms_get_or_create_array_type(cc_syms* self, cc_symbol* enclosing, cc_symbol* inner_type);

#endif // CC_SYM_H_INCLUDED
