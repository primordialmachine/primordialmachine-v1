#if !defined(CC_C99_AST_EXP_NODE_H_INCLUDED)
#define CC_C99_AST_EXP_NODE_H_INCLUDED

#if !defined(CC_C99_AST_PRIVATE)
#error("Do not include `c99/ast/exp_node.h` directly. Include `c99/ast/_include.h` instead.")
#endif

#include "c99/ast/node.h"

typedef enum cc_c99_exp_node_kind {
  CC_C99_EXP_NODE_KIND_BIN,
  CC_C99_EXP_NODE_KIND_UN,
  CC_C99_EXP_NODE_KIND_CALL,
  CC_C99_EXP_NODE_KIND_CAST,
  CC_C99_EXP_NODE_KIND_STRINGLIT,
  CC_C99_EXP_NODE_KIND_INTLIT,
  CC_C99_EXP_NODE_KIND_NAME,
} cc_c99_exp_node_kind;

CC_DECLARE_CLASS(cc_c99_exp_node, cc_object)

struct cc_c99_exp_node {
  cc_c99_node parent;
  cc_c99_exp_node_kind kind;
};

void
cc_c99_exp_node_construct
  (
    cc_c99_exp_node *self,
    cc_c99_exp_node_kind kind
  );

#endif // CC_C99_AST_EXP_NODE_H_INCLUDED
