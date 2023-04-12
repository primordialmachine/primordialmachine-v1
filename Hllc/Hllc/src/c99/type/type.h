// Representation of C99 types.
#if !defined(C99_TYPE_TYPE_H_INCLUDED)
#define C99_TYPE_TYPE_H_INCLUDED

#include "cc_os.h"
#include "cc_context.h"
#include "cc_os_arraylist.h"

typedef enum cc_c99_type_kind {
  CC_C99_TYPE_KIND_INTEGER,
  CC_C99_TYPE_KIND_FLOATING_POINT,
  CC_C99_TYPE_KIND_BOOL,
  CC_C99_TYPE_KIND_POINTER,
  CC_C99_TYPE_KIND_STRUCT,
  CC_C99_TYPE_KIND_ENUM,
  CC_C99_TYPE_KIND_ARRAY,
  CC_C99_TYPE_KIND_TYPEDEF,
} cc_c99_type_kind;

CC_DECLARE_CLASS(cc_c99_type, cc_object)

struct cc_c99_type {
  cc_object parent;
  cc_c99_type_kind kind;
};


BEGIN_DECLARE_COMPONENT(cc_c99_types)

// List of known types.
cc_arraylist *types;

// "bool".
cc_c99_type* BOOL;
// "int". Same as "signed int".
cc_c99_type* INT;
// "float".
cc_c99_type* FLOAT;
// "double".
cc_c99_type* DOUBLE;

END_DECLARE_COMPONENT(cc_c99_types)

#endif // C99_TYPE_TYPE_H_INCLUDED
