#if !defined(CC_EMIT_DISPATCH_H_INCLUDED)
#define CC_EMIT_DISPATCH_H_INCLUDED

#include "spectre/cc_emit-protected.h"
#include "spectre/cc_c99_node.h"

/// @brief Enumeration of strategies of computing the dispatch declarations for a symbol.
/// @detail

/// Let N.X be a class and let N.X.m(...) N.R be a method which is non-sealed, non-static, and not an override of a method.
/// ƒ is the translation function.
/// 
/// THE WRAPPER DECLARATION:
/// If m is public then a function ƒ(N.R) N_X_m(ƒ(...)) is declared in the public header.
/// If m is protected then a function ƒ(N.R) N_X_m(ƒ(...)) is declared in the protected header.
/// 
/// THE WRAPPER DEFINITION:
/// The function ƒ(N.R) N_X_m(ƒ(...)) (either declared in the public header or the protected header) is defined in the footer.
/// 
/// THE IMPLEMENTATION DECLARATION:
typedef enum cc_emit_dispatch_generation_strategy
{
  /// @brief Compute the dispatch WRAPPER DECLARATIONS (see cc_emit_dispatch_generation_strategy) for the public header file of a symbol.
  CC_EMIT_DISPATCH_GENERATION_STRATEGY_DECLARATIONS_PUBLIC_HEADER,

  /// @brief Compute the dispatch WRAPPER DECLARATIONS (see cc_emit_dispatch_generation_strategy) for the public header file of a symbol.
  CC_EMIT_DISPATCH_GENERATION_STRATEGY_DECLARATIONS_PROTECTED_HEADER,

  /// @brief Compute the dispatch implementation declarations for the header inlay file of a symbol.
  /// @detail
  /// For each non-static non-abstract abstract method which is b) non-sealed OR the override of a method:
  /// Declare a static C function in the header inlay file. These are the functions the user has to implemented.
  /// @example
  /// <code>
  /// override g.void m()
  /// </code>
  /// yields
  /// <code>
  /// static g_void m();
  /// </code>
  CC_EMIT_DISPATCH_GENERATION_STRATEGY_DECLARATIONS_HEADER_INLAY,

  /// @brief Compute the dispatch declarations for the footer inlay file of a symbol.
  /// For each method considered by CC_EMIT_DISPATCH_GENERATION_STRATEGY_DECLARATIONS_PUBLIC_HEADER and
  /// CC_EMIT_DISPATCH_GENERATION_STRATEGY_DECLARATIONS_PROTECTED_HEADER, emit the definition of the
  /// corresponding C function.
  CC_EMIT_DISPATCH_GENERATION_STRATEGY_DEFINITIONS_FOOTER_INLAY,

  /// @brief Compute the dispatch declarations for the class struct of a class symbol.
  /// @detail
  /// For each method which is non-static and non-sealed nor an override.
  /// Define a variable in the class struct.
  /// The type of that variable is a pointer to an implementation function of the method.
  /// @example
  /// <code>
  /// g.C.m(T) g.void
  /// </code>
  /// yields
  /// <code>
  /// struct g_C_struct
  /// { 
  ///   ...
  ///   g_void (*m)(T *); 
  ///   ... 
  /// }
  /// </code>
  /// if <code>T</code> is a class type.
  CC_EMIT_DISPATCH_GENERATION_STRATEGY_DEFINITIONS_CLASS_STRUCT,

} cc_emit_dispatch_generation_strategy;

cc_c99_group_node*
cc_emit_get_dispatch_declarations
  (
    cc_emit* self,
    cc_emit_dispatch_generation_strategy strategy,
    cc_symbol* symbol
  );

#endif // CC_EMIT_DISPATCH_H_INCLUDED
