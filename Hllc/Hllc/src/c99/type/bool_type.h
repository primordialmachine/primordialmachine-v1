// Representation of the C99 bool type.
#if !defined(C99_TYPE_BOOL_TYPEH_INCLUDED)
#define C99_TYPE_BOOL_INCLLUDED_H_INCLUDED

#include "c99/type/type.h"

CC_DECLARE_CLASS(cc_c99_bool_type, cc_c99_type)

struct cc_c99_bool_type {
  cc_c99_type _parent;
  // Must not be null.
  cc_cstring* name;
};

/// @param name A pointer to the name.
cc_c99_bool_type*
cc_c99_bool_type_create
  (
    cc_cstring* name
  );

#endif // C99_TYPE_BOOL_INCLLUDED_H_INCLUDED
