// Representation of C99 struct types.
#if !defined(C99_TYPE_STRUCT_TYPE_H_INCLUDED)
#define C99_TYPE_STRUCT_TYPE_H_INCLUDED

#include "c99/type/type.h"

CC_DECLARE_CLASS(cc_c99_struct_type, cc_c99_type)

struct cc_c99_struct_type {
  cc_c99_type _parent;
  // Can be null for anonymous structs.
  cc_cstring* name;
};

/// @param name A pointer to the name or a null pointer.
cc_c99_struct_type*
cc_c99_struct_type_create
  (
    cc_cstring* name
  );

#if 0
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DECLARE_CLASS(cc_c99_int_type, cc_c99_type)

struct cc_c99_int_type {
  cc_c99_type _parent;
  // Must not be null.
  cc_cstring* name;
};

/// @param name A pointer to the name.
cc_c99_int_type*
cc_c99_int_type_create
  (
    cc_cstring* name
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DECLARE_CLASS(cc_c99_floating_point_type, cc_c99_type)

struct cc_c99_floating_point_type {
  cc_c99_type _parent;
  // Must not be null.
  cc_cstring* name;
};

/// @param name A pointer to the name.
cc_c99_struct_type*
cc_c99_floating_point_type_create
  (
    cc_cstring* name
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DECLARE_CLASS(cc_c99_struct_type, cc_c99_type)

struct cc_c99_struct_type {
  cc_c99_type _parent;
  // Can be null for anonymous structs.
  cc_cstring* name;
};

/// @param name A pointer to the name or a null pointer.
cc_c99_struct_type*
cc_c99_struct_type_create
(
  cc_cstring* name
);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#endif

#endif // C99_TYPE_STRUCT_TYPE_H_INCLUDED
