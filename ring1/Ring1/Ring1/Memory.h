// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Memory.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_MEMORY_H_INCLUDED)
#define RING1_MEMORY_H_INCLUDED

#include "Ring1/Memory/Configuration.h"
#include "Ring1/Module.h"
#include "Ring1/Memory/recomputeSize.h"

#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring1/Result.h"

Ring1_Module_Declare(Memory)

// https://preview.primordialmachine.com/ring1-library/memory-library/Ring1_Memory_allocate
Ring1_CheckReturn() Ring1_Result
Ring1_Memory_allocate
  (
    void **result,
    size_t n
  );

// https://preview.primordialmachine.com/ring1-library/memory-library/Ring1_Memory_allocateArray
Ring1_CheckReturn() Ring1_Result
Ring1_Memory_allocateArray
  (
    void **result,
    size_t numberOfElements,
    size_t elementSize
  );

// https://preview.primordialmachine.com/ring1-library/memory-library/Ring1_Memory_reallocate
Ring1_CheckReturn() Ring1_Result
Ring1_Memory_reallocate
  (
    void **result,
    void *p,
    size_t n
  );

// https://preview.primordialmachine.com/ring1-library/memory-library/Ring1_Memory_reallocateArray
Ring1_CheckReturn() Ring1_Result
Ring1_Memory_reallocateArray
  (
    void **result,
    void* p,
    size_t numberOfElements,
    size_t elementSize
  );

// https://preview.primordialmachine.com/ring1-library/memory-library/Ring1_Memory_deallocate
Ring1_Result
Ring1_Memory_deallocate
  (
    void *p
  );

// https://preview.primordialmachine.com/ring1-library/memory-library/Ring1_Memory_zeroFill
Ring1_CheckReturn()Ring1_Result
Ring1_Memory_zeroFill
  (
    void *p,
    size_t n
  );

// https://preview.primordialmachine.com/ring1-library/memory-library/Ring1_Memory_zeroFillArray
Ring1_CheckReturn() Ring1_Result
Ring1_Memory_zeroFillArray
  (
    void* p,
    size_t numberOfElements,
    size_t elementSize
  );

// https://documentation.primordialmachine.com/ring1-libraries/memory-library/Ring1_Memory_copyFast
Ring1_CheckReturn() int
Ring1_Memory_copyFast
  (
    void* p,
    const void* q,
    size_t n
  );

// https://documentation.primordialmachine.com/ring1-libraries/memory-library/Ring1_Memory_copyArrayFast
Ring1_CheckReturn() int
Ring1_Memory_copyArrayFast
  (
    void* target,
    const void* source,
    size_t numberOfElements,
    size_t elementSize
  );
  
// https://documentation.primordialmachine.com/ring1-library/memory-library/Ring1_Memory_copySlow
Ring1_CheckReturn() Ring1_Result
Ring1_Memory_copySlow
  (
    void *p,
    const void *q,
    size_t n
  );

// https://documentation.primordialmachine.com/ring1-library/memory-library/Ring1_Memory_copyArraySlow
Ring1_CheckReturn() Ring1_Result
Ring1_Memory_copyArraySlow
  (
    void* p,
    const void* q,
    size_t numberOfElements,
    size_t elementSize
  );

// https://preview.primordialmachine.com/ring1-library/memory-library/Ring1_Memory_getPageSize
Ring1_CheckReturn() Ring1_Result
Ring1_Memory_getPageSze
  (
    size_t *result
  );

#endif  // RING1_MEMORY_H_INCLUDED
