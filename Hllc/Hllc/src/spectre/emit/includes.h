#if !defined(CC_SEMA_H_INCLUDED)
#define CC_SEMA_H_INCLUDED

#include "spectre/cc_emit-protected.h"
#include "spectre/cc_c99_node.h"

/// @brief Enumeration of strategies of computing the additional includes for a symbol.
typedef enum cc_emit_additional_includes_strategy
{
  /// @brief Compute the additional includes for the public header file of a symbol.
  CC_EMIT_ADDITIONAL_INCLUDES_STRATEGY_PUBLIC_HEADER,
  
  /// @brief Compute the additional includes for the protected header file of a symbol.
  CC_EMIT_ADDITIONAL_INCLUDES_STRATEGY_PROTECTED_HEADER,
  
  /// @brief Compute the additional includes for the header inlay file of a symbol.
  CC_EMIT_ADDITIONAL_INCLUDES_STRATEGY_HEADER_INLAY,
  
  /// @brief Compute the additional includes for the footer inlay file of a symbol.
  CC_EMIT_ADDITIONAL_INCLUDES_STRATEGY_FOOTER_INLAY,
  
} cc_emit_additional_includes_strategy;

/// @brief
/// @return C99 group node containing containing the additional includes.
/// @remarks
/// - include directives for the runtime are included
/// - classes are included using forward typedefs
/// - enumerations are included using include directives
cc_c99_group_node *
cc_emit_get_additional_includes_for
  (
    cc_emit* self,
    cc_emit_additional_includes_strategy strategy,
    cc_symbol *symbol
  );

#endif
