/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#if !defined(CC_C99_NAMES_H_INCLUDED)
#define CC_C99_NAMES_H_INCLUDED

#include "./../../cc_names.h"

BEGIN_DECLARE_COMPONENT(cc_c99_names)

  cc_names* names;

#define DEFINE(NAME, STRING) \
  cc_name* NAME;

#include "spectre/c99/names.i"

#undef DEFINE

END_DECLARE_COMPONENT(cc_c99_names)

/// @brief Get or create the name for a given string.
/// @param self A pointer to this names.
/// @param string A pointer to the string.
/// @return The name.
cc_name* cc_c99_names_get_or_create(cc_c99_names* self, const char *string);

#endif // CC_C99_NAMES_H_INCLUDED
