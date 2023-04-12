// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Assertions.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_ASSERTIONS_H_INCLUDED)
#define RING1_ASSERTIONS_H_INCLUDED

void _Ring1_onAssertionFailed(char const *file, int line, char const *expression);

#define Ring1_assert(EXPRESSION) \
  if (!(EXPRESSION)) { \
    _Ring1_onAssertionFailed(__FILE__, __LINE__, #EXPRESSION); \
  }

#endif // RING1_ASSERT_H_INCLUDED
