// Representation of C99 enum types.
#if !defined(C99_TYPE_ENUM_TYPE_H_INCLUDED)
#define C99_TYPE_ENUM_TYPE_H_INCLUDED

#include "c99/type/type.h"

CC_DECLARE_CLASS(cc_c99_enum_type, cc_c99_type)

struct cc_c99_enum_type {
  cc_c99_type _parent;
  // Can be null for anonymous structs.
  cc_cstring* name;
};

/// @param name A pointer to the name or a null pointer.
cc_c99_enum_type*
cc_c99_enum_type_create
  (
    cc_cstring* name
  );

#endif // C99_TYPE_ENUM_TYPE_H_INCLUDED
