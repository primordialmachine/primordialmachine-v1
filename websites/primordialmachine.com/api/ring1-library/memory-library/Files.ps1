# Copyright (c) 2022 Michael Heilmann. All rights reserved.
$prefix = './api/ring1-library/memory-library/';
$jobs +=
  @(
    # Ring 1 - Memory Library.
    @(-join($prefix,'index.html.t'),
      -join($prefix,'index.html')),
    @(-join($prefix,'Ring1_Memory_recomputeSize.html.t'),
      -join($prefix,'Ring1_Memory_recomputeSize.html')),
    @(-join($prefix,'Ring1_Memory_allocate.html.t'),
      -join($prefix,'Ring1_Memory_allocate.html')),
    @(-join($prefix,'Ring1_Memory_allocateArray.html.t'),
      -join($prefix,'Ring1_Memory_allocateArray.html')),
    @(-join($prefix,'Ring1_Memory_deallocate.html.t'),
      -join($prefix,'Ring1_Memory_deallocate.html')),
    @(-join($prefix,'Ring1_Memory_getPageSize.html.t'),
      -join($prefix,'Ring1_Memory_getPageSize.html'))
    @(-join($prefix,'Ring1_Memory_reallocate.html.t'),
      -join($prefix,'Ring1_Memory_reallocate.html')),
    @(-join($prefix,'Ring1_Memory_reallocateArray.html.t'),
      -join($prefix,'Ring1_Memory_reallocateArray.html')),
    @(-join($prefix,'Ring1_Memory_zeroFill.html.t'),
      -join($prefix,'Ring1_Memory_zeroFill.html')),
    @(-join($prefix,'Ring1_Memory_zeroFillArray.html.t'),
      -join($prefix,'Ring1_Memory_zeroFillArray.html')),
      
    @(-join($prefix,'Ring1_Memory_copyArrayFast.html.t'),
      -join($prefix,'Ring1_Memory_copyArrayFast.html')),
    @(-join($prefix,'Ring1_Memory_copyArraySlow.html.t'),
      -join($prefix,'Ring1_Memory_copyArraySlow.html')),
    @(-join($prefix,'Ring1_Memory_copyFast.html.t'),
      -join($prefix,'Ring1_Memory_copyFast.html')),
    @(-join($prefix,'Ring1_Memory_copySlow.html.t'),
      -join($prefix,'Ring1_Memory_copySlow.html'))
  );
