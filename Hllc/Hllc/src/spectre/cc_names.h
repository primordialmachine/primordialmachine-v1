/* Copyright (c) 2020 Michael Heilmann. All rights reserved. */
#if !defined(CC_SPECTRE_NAMES_H_INCLUDED)
#define CC_SPECTRE_NAMES_H_INCLUDED

#include "./../cc_names.h"

BEGIN_DECLARE_COMPONENT(cc_spectre_names)

  cc_names *names;

#define DEFINE(NAME, STRING) \
  cc_name* NAME;

#include "spectre/cc_names.i"

#undef DEFINE

END_DECLARE_COMPONENT(cc_spectre_names)

/// @brief Get or create the name for a given string.
/// @param self A pointer to this names.
/// @param string A pointer to the string.
/// @return The name.
cc_name* cc_spectre_names_get_or_create(cc_spectre_names* self, const char *string);

#endif // CC_SPECTRE_NAMES_H_INCLUDED
