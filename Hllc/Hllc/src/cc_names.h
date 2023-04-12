#if !defined(CC_NAMES_H_INCLUDED)
#define CC_NAMES_H_INCLUDED

#include "cc_context.h"

CC_DECLARE_CLASS(cc_name, cc_object)

struct cc_name
{
  cc_object parent;
  cc_name* next;
  size_t hash_value;
  cc_cstring* string;
};

BEGIN_DECLARE_COMPONENT(cc_names)
  
  cc_name** buckets;
  size_t size;
  size_t capacity;

END_DECLARE_COMPONENT(cc_names)

/// @brief Get or create the name for a given string.
/// @param self A pointer to this names.
/// @param string A pointer to the string.
/// @return The name.
cc_name* cc_names_get_or_create(cc_names* self, const char *string);

#endif // CC_NAMES_H_INCLUDED
