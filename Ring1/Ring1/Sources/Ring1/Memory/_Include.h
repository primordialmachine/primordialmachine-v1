// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Memory/_Include.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_MEMORY__INCLUDE_H_INCLUDED)
#define RING1_MEMORY__INCLUDE_H_INCLUDED

#include "Ring1/Memory/Configuration.h"
#include "Ring1/Module.h"
#include "Ring1/Memory/recomputeSize.h"

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"

Ring1_Module_Declare(Ring1, Memory)

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_allocate
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_allocate
  (
    void **result,
    size_t n
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_allocateArray
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_allocateArray
  (
    void **result,
    size_t numberOfElements,
    size_t elementSize
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_reallocate
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_reallocate
  (
    void **result,
    void *p,
    size_t n
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_reallocateArray
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_reallocateArray
  (
    void **result,
    void* p,
    size_t numberOfElements,
    size_t elementSize
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_deallocate
Ring1_Result
Ring1_Memory_deallocate
  (
    void *p
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_zeroFill
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_zeroFill
  (
    void *p,
    size_t n
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_zeroFillArray
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_zeroFillArray
  (
    void* p,
    size_t numberOfElements,
    size_t elementSize
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_compare
#define Ring1_Memory_Compare_Colexicographic (1)

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_compare
#define Ring1_Memory_Compare_Lexicographic (2)

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_compare
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_compare
  (
    int *result,
    const void* p,
    size_t n,
    const void* q,
    size_t m,
    int flags
  );

// https://primordialmachine.com/ring1-libraries/memory-library/Ring1_Memory_copyFast
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_copyFast
  (
    void* p,
    const void* q,
    size_t n
  );

// https://primordialmachine.com/api/ring1-libraries/memory-library/Ring1_Memory_copyArrayFast
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_copyArrayFast
  (
    void* target,
    const void* source,
    size_t numberOfElements,
    size_t elementSize
  );
  
// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_copySlow
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_copySlow
  (
    void *p,
    const void *q,
    size_t n
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_copyArraySlow
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_copyArraySlow
  (
    void* p,
    const void* q,
    size_t numberOfElements,
    size_t elementSize
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_getPageSize
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_getPageSze
  (
    size_t *result
  );

#endif  // RING1_MEMORY__INCLUDE_H_INCLUDED
