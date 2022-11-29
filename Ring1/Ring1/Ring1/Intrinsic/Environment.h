// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Environment.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
/// @brief
/// Provides information on the compilation environment of this library and the execution
/// environment of this library.
/// @detail
/// This file provides information on the compilation environment of this and the execution
/// environment. The compilation environment comprises the compiler used to compile this libary and
/// - subsequently - the C language dialect and the C standard library./// <br/>
/// The execution environment comprises the target operating system and the
/// target architecture this library is compiled for.
/// <br/>
/// The following functionality is provided:
/// - This file includes <inttypes.h> and <stdbool.h>.
/// <br/>
/// - This file detects the operating system of the execution environment:
///   It defines the symbolic constants
///   - Ring1_Intrinsic_OperatingSystem_Linux,
///   - Ring1_Intrinsic_OperatingSystem_Osx, and
///   - Ring1_Intrinsic_OperatingSystem_Windows
///   of which each evaluates to a unique non-negative integer.
///   The operating system is determined by defining the symbolic constant 
///   The symbolic constant Ring1_Intrinsic_OperatingSystem is defined to evaluate to one of the symbolic constants above
///   denoting the operating system of the execution environment:
///   - Ring1_Intrinsic_OperatingSystem_Linux if the operating system is Linux.
///   - Ring1_Intrinsic_OperatingSystem_Os if the operating system is OSX.
///   - Ring1_Intrinsic_OperatingSystem_Windows of if operating system is Windows.
///   If detection of the operating system of the execution environment fails, compilation fails.
///   If Ring1_Intrinsic_OperatingSystem is already defined (e.g. through the compiler),
///   then this file neither attempts to detect the operating system nor it does redefine Ring1_Intrinsic_OperatingSystem.
///   However, it checks that the definition evaluates to a value of one of the symbolic constants above.
///   If the check fails, compilation fails.
/// <br/>
/// - This file detects the architecture of the execution environment:
///   It defines the symbolic constants
///   - Ring1_Intrinsic_Architecture_X86,
///   - Ring1_Intrinsic_Architecture_X64, and
///   - Ring1_Intrinsic_Architecture_Arm
///   of which each evaluates to a unique non-negative integer.
///   The symbolic constant Ring1_Intrinsic_Architecture is defined to evaluate to one of the symbolic constants above
///   denoting the architecture of the execution environment:
///   - Ring1_Intrinsic_Architecture_X86 if the architecture is x86.
///   - Ring1_Intrinsic_Architecture_X64 if the architecture is x64.
///   - Ring1_Intrinsic_Architecture_Arm if the architecture is ARM.
///   If detection of the architecture of the execution environment fails, compilation fails.
///   If Ring1_Intrinsic_Architecture is already defined (e.g. through the compiler),
///   then this file neither attempts to detect the architecture nor it does redefine Ring1_Intrinsic_Architecture.
///   However, it checks that the definition evaluates to a value of one of the symbolic constants above.
///   If the check fails, compilation fails.
/// <br/>
/// - This file detects the compiler of the compilation environment:
///   It defines the symbolic constants
///   - Ring1_Intrinsic_Compiler_Msvc,
///   - Ring1_Intrinsic_Compiler_Gcc, and
///   - Ring1_Intrinsic_Compiler_Clang
///   of which each evaluates to a unique non-negative integer.
///   The symbolic constant Ring1_Intrinsic_Architecture is defined to evaluate to one of the symbolic constants above
///   denoting the compiler of the compilation environment:
///   - Ring1_Intrinsic_Compiler_Msvc if the compiler is MSVC.
///   -  Ring1_Intrinsic_Compiler_Gcc if the compiler is GCC.
///   - Ring1_Intrinsic_Compiler_Clang if the compiler is CLANG.
///   If detection of the compiler of the compilation environment fails, compilation fails.
///   If Ring1_Intrinsic_Compiler is already defined (e.g. through the compiler),
///   then this file neither attempts to detect the compiler nor it does redefine Ring1_Intrinsic_Compiler.
///   However, it checks that the definition evaluates to a value of one of the symbolic constants above.
///   If the check fails, compilation
///   fails.
/// <br/>
/// - This file defines symbolic constants UINTx_MIN (where x is 8, 16, 32, or 64) denoting the minimum values of the uintx_t types.
///   These values are obviously UINTx_C(0). If UINTx_MIN is already defined, then this file does not redefine UINTx_MIN.
/// - Ths file defines the symbolic constant SIZE_MIN constant denoting the minimum value of the size_t type.
///   This value is obviously (0). If UINTx_MIN is already defined, then this file does not redefine UINTx_MIN.
/// - bool, true, false are not defined if they are not defined in <stdbool.h> already.

#if !defined(RING1_INTRINSIC_ENVIRONMENT_H_INCLUDED)
#define RING1_INTRINSIC_ENVIRONMENT_H_INCLUDED

#include "Ring1/Intrinsic/Configuration.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

/// @brief Operating system "Windows".
#define Ring1_Intrinsic_OperatingSystem_Windows (1)

/// @brief Operating system "Linux".
#define Ring1_Intrinsic_OperatingSystem_Linux (2)

/// @brief Operating system "OSX".
#define Ring1_Intrinsic_OperatingSystem_Osx (3)

// Try to detect the operating system if it is not specified.
#if !defined(Ring1_Intrinsic_OperatingSystem)

  #if defined(_WIN32)
    #define Ring1_Intrinsic_OperatingSystem Ring1_Intrinsic_OperatingSystem_Windows
  #else
    #error("unable to detect operating system")
  #endif

#endif // Ring1_Intrinsic_OperatingSystem

static_assert(Ring1_Intrinsic_OperatingSystem == Ring1_Intrinsic_OperatingSystem_Linux ||
              Ring1_Intrinsic_OperatingSystem == Ring1_Intrinsic_OperatingSystem_Osx ||
              Ring1_Intrinsic_OperatingSystem == Ring1_Intrinsic_OperatingSystem_Windows,
              "invalid definition of symbolic constant Ring1_Intrinsic_OperatingSystem");

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

/// @brief Operating system "Microsoft Visual C++".
#define Ring1_Intrinsic_Compiler_Msvc (1)

/// @brief Operating system "Clang".
#define Ring1_Intrinsic_Compiler_Clang (2)

/// @brief Operating system "GCC".
#define Ring1_Intrinsic_Compiler_Gcc (3)

// Try to detect the compiler if it is not specified.
#if !defined(Ring1_Intrinsic_Compiler)

  #if defined(_MSC_VER)
    #define Ring1_Intrinsic_Compiler Ring1_Intrinsic_Compiler_Msvc
  #else
    #error("unable to detect compiler")
  #endif

#endif // Ring1_Intrinsic_Compiler

static_assert(Ring1_Intrinsic_Compiler == Ring1_Intrinsic_Compiler_Clang ||
              Ring1_Intrinsic_Compiler == Ring1_Intrinsic_Compiler_Gcc ||
              Ring1_Intrinsic_Compiler == Ring1_Intrinsic_Compiler_Msvc,
              "invalid definition of symbolic constant Ring1_Intrinsic_Compiler");

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

/// @brief Architecture "x86".
#define Ring1_Intrinsic_Architecture_X86 (1)

/// @brief Architecture "x64".
#define Ring1_Intrinsic_Architecture_X64 (2)

/// @brief Architecture "ARM".
#define Ring1_Intrinsic_Architecture_Arm (3)

// Try to detect the compiler if it is not specified.
#if !defined(Ring1_Intrinsic_Archicteture)

  #if defined(_MSC_VER)
    #if defined(__x86_64__) || defined(_M_X64)
      #define Ring1_Intrinsic_Architecture Ring1_Intrinsic_Architecture_X64
    #elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
      #define Ring1_Intrinsic_Architecture Ring1_Intrinsic_Architecture_X86
    #else
      #error("unable to detect archictecture")
    #endif
  #else
    #error("unable to detect archictecture")
  #endif

#endif // Ring1_Intrinsic_Compiler

static_assert(Ring1_Intrinsic_Architecture == Ring1_Intrinsic_Architecture_Arm ||
              Ring1_Intrinsic_Architecture == Ring1_Intrinsic_Architecture_X64 ||
              Ring1_Intrinsic_Architecture == Ring1_Intrinsic_Architecture_X86,
              "invalid definition of symbolic constant Ring1_Intrinsic_Architecture");

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include <stdbool.h>

#if !defined(__bool_true_false_are_defined)
#error("<stdbool.h> is missing __bool_true_false_are_defined")
#endif

#if 0 == __bool_true_false_are_defined

typedef enum
{
  false,
  true
} bool;

#endif // __bool_true_false_are_defined

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include <inttypes.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

/// @brief Missing symbolic constant SIZE_MIN (always evaluates to 0).
#define SIZE_MIN (0)

/// @brief The number of bits of the unsigned integer type size_t.
#if defined(_MSC_VER)
  #if defined(_WIN64)
    #define SIZE_BITS 64
  #else
    #define SIZE_BITS 32
  #endif
#else
  #error("environment not supported")
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

/// @brief Missing symbolic constant UINT64_MIN (always evaluates to 0).
#define UINT64_MIN UINT64_C(0)

#if defined(_MSC_VER)
  /// @brief The number of bits of the uint64_t type.
  #define UINT64_BITS 64
#else
  #error("environment not supported")
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#if defined(_MSC_VER)
  /// @brief The number of bits of the int64_t type.
  #define INT64_BITS 64
#else
  #error("environment not supported")
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

/// @brief Missing symbolic constant UINT32_MIN (always evaluates to 0).
#define UINT32_MIN UINT32_C(0)

#if defined(_MSC_VER)
  /// @brief The number of bits of the uint32_t type.
  #define UINT32_BITS 32
#else
  #error("environment not supported")
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#if defined(_MSC_VER)
  /// @brief The number of bits of the int32_t type.
  #define INT32_BITS 32
#else
  #error("environment not supported")
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

/// @brief Missing symbolic constant UINT16_MIN (always evaluates to 0).
#define UINT16_MIN UINT16_C(0)

#if defined(_MSC_VER)
  /// @brief The number of bits of the uint16_t type.
  #define UINT16_BITS 16
#else
  #error("environment not supported")
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#if defined(_MSC_VER)
  /// @brief The number of bits of the int16_t type.
  #define INT16_BITS 16
#else
  #error("environment not supported")
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

/// @brief Missing symbolic constant UINT8_MIN (always evaluates to 0).
#define UINT8_MIN UINT8_C(0)

#if defined(_MSC_VER)
  /// @brief The number of bits of the uint8_t type.
  #define UINT8_BITS 8
#else
  #error("environment not supported")
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#if defined(_MSC_VER)
  /// @brief The number of bits of the int8_t type.
  #define INT8_BITS 8
#else
  #error("environment not supported")
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#endif // RING1_INTRINSIC_ENVIRONMENT_H_INCLUDED
