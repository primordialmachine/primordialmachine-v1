/// @file Eel/Compiler.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_EAL_COMPILER_H_INCLUDED)
#define MACHINE_EAL_COMPILER_H_INCLUDED



#if !defined(MACHINE_EAL_PRIVATE)
#error("Do not include this file directly, include `_Eal.h` instead.")
#endif

#include <stddef.h>



#if defined(INLINE)
  #error('INLINE already defined')
#endif
/// @brief Function annotation. Annotate a function as an inline function.
/// Use as
/// @code
/// INLINE void f() { ... }
/// @endcode
#define INLINE static inline

#if defined(NORETURN)
  #error('NORETURN already defined')
#endif
/// @brief Function annotation. Annotate a function as not returning function.
/// Use as
/// @code
/// NORETURN void f() { ... }
/// @endcode
#define NORETURN __declspec(noreturn)

#if defined(DEPRECATED)
  #error('DEPRECATED already defined')
#endif
/// @brief Function, structure, field, and variable annotation. Annotate a function, structure, field, or variable as deprecated.
/// Use as
/// @code
/// DEPRECATED
/// static int v = 0;
/// @endcode
#define DEPRECATED



#endif // MACHINE_EAL_COMPILER_H_INCLUDED
