// Representation of C99 integer types.
#if !defined(C99_TYPE_INTEGER_TYPE_H_INCLUDED)
#define C99_TYPE_INTEGER_TYPE_H_INCLUDED

#include "c99/type/type.h"

CC_DECLARE_CLASS(cc_c99_integer_type, cc_c99_type)

struct cc_c99_integer_type {
  cc_c99_type _parent;
  // Must not be null.
  cc_cstring* name;
};

/// @param name A pointer to the name.
cc_c99_integer_type*
cc_c99_integer_type_create
  (
    cc_cstring* name
  );

#endif // C99_TYPE_INTEGER_TYPE_H_INCLUDED
