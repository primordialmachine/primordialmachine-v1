// Representation of C99 types.
#if !defined(C99_TYPE__INCLLUDED_H_INCLUDED)
#define C99_TYPE__INCLLUDED_H_INCLUDED

#include "c99/type/bool_type.h"
#include "c99/type/enum_type.h"
#include "c99/type/struct_type.h"
#if 0
#include "cc_os.h"

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

CC_DECLARE_CLASS(cc_c99_enum_type, cc_c99_type)

struct cc_c99_enum_type {
  cc_c99_type _parent;
  // Can be null for anonymous enumerations.
  cc_cstring *name;
};

/// @param name A pointer to the name or a null pointer.
cc_c99_enum_type*
cc_c99_enum_type_create
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

#endif // C99_TYPE__INCLLUDED_H_INCLUDED
