/// @file Eel/Zts.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_EAL_ZTS_H_INCLUDED)
#define MACHINE_EAL_ZTS_H_INCLUDED



#if !defined(MACHINE_EAL_PRIVATE)
#error("Do not include this file directly, include `_Eal.h` instead.")
#endif

#include "Eal/Compiler.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <setjmp.h>



/// @brief Clone a zero terminated string.
/// @param s A pointer to the zero terminated string.
/// @return The cloned string.
char* c_strzt_clone(char const* s);

/// @brief Get the length of a zero terminaed string.
/// @param s A pointer to the zero terminated string.
/// @return The length of the zero terminated string.
size_t c_strzt_length(char const* s);



#endif // MACHINE_EAL_ZTS_H_INCLUDED
