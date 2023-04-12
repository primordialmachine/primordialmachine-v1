# Copyright (c) 2022 Michael Heilmann. All rights reserved.
$prefix = './api/ring1-library/bytebuffer-library/';
$temporary =
  @(
    # Ring 1 - Byte Buffer Library.
    @(-join($prefix,'index.html.t'),
      -join($prefix,'index.html')),
    @(-join($prefix,'Ring1_ByteBuffer.html.t'),
      -join($prefix,'Ring1_ByteBuffer.html')),
    @(-join($prefix,'Ring1_ByteBuffer_Capacity_Default.html.t'),
      -join($prefix,'Ring1_ByteBuffer_Capacity_Default.html')),
    @(-join($prefix,'Ring1_ByteBuffer_Capacity_Greatest.html.t'),
      -join($prefix,'Ring1_ByteBuffer_Capacity_Greatest.html')),
    @(-join($prefix,'Ring1_ByteBuffer_Capacity_Least.html.t'),
      -join($prefix,'Ring1_ByteBuffer_Capacity_Least.html')),
    @(-join($prefix,'Ring1_ByteBuffer_initialize.html.t'),
      -join($prefix,'Ring1_ByteBuffer_initialize.html')),
    @(-join($prefix,'Ring1_ByteBuffer_uninitialize.html.t'),
      -join($prefix,'Ring1_ByteBuffer_uninitialize.html')),
  
    @(-join($prefix,'Ring1_ByteBuffer_appendByte.html.t'),
      -join($prefix,'Ring1_ByteBuffer_appendByte.html')),
    @(-join($prefix,'Ring1_ByteBuffer_appendBytes.html.t'),
      -join($prefix,'Ring1_ByteBuffer_appendBytes.html')),
      
    @(-join($prefix,'Ring1_ByteBuffer_prependByte.html.t'),
      -join($prefix,'Ring1_ByteBuffer_prependByte.html')),
    @(-join($prefix,'Ring1_ByteBuffer_prependBytes.html.t'),
      -join($prefix,'Ring1_ByteBuffer_prependBytes.html')),
      
    @(-join($prefix,'Ring1_ByteBuffer_insertByteAt.html.t'),
      -join($prefix,'Ring1_ByteBuffer_insertByteAt.html')),
    @(-join($prefix,'Ring1_ByteBuffer_insertBytesAt.html.t'),
      -join($prefix,'Ring1_ByteBuffer_insertBytesAt.html')),
      
    @(-join($prefix,'Ring1_ByteBuffer_clear.html.t'),
      -join($prefix,'Ring1_ByteBuffer_clear.html')),
    @(-join($prefix,'Ring1_ByteBuffer_getBytes.html.t'),
      -join($prefix,'Ring1_ByteBuffer_getBytes.html')),
    @(-join($prefix,'Ring1_ByteBuffer_getNumberOfBytes.html.t'),
      -join($prefix,'Ring1_ByteBuffer_getNumberOfBytes.html'))
  );
$jobs +=
  @(
    # Ring 1 - Byte Buffer Library.
    @(-join($prefix,'index.html.t'),
      -join($prefix,'index.html')),
    @(-join($prefix,'Ring1_ByteBuffer.html.t'),
      -join($prefix,'Ring1_ByteBuffer.html')),
    @(-join($prefix,'Ring1_ByteBuffer_initialize.html.t'),
      -join($prefix,'Ring1_ByteBuffer_initialize.html')),
    @(-join($prefix,'Ring1_ByteBuffer_uninitialize.html.t'),
      -join($prefix,'Ring1_ByteBuffer_uninitialize.html')),
  
    @(-join($prefix,'Ring1_ByteBuffer_appendByte.html.t'),
      -join($prefix,'Ring1_ByteBuffer_appendByte.html')),
    @(-join($prefix,'Ring1_ByteBuffer_appendBytes.html.t'),
      -join($prefix,'Ring1_ByteBuffer_appendBytes.html')),
      
    @(-join($prefix,'Ring1_ByteBuffer_prependByte.html.t'),
      -join($prefix,'Ring1_ByteBuffer_prependByte.html')),
    @(-join($prefix,'Ring1_ByteBuffer_prependBytes.html.t'),
      -join($prefix,'Ring1_ByteBuffer_prependBytes.html')),
      
    @(-join($prefix,'Ring1_ByteBuffer_insertByteAt.html.t'),
      -join($prefix,'Ring1_ByteBuffer_insertByteAt.html')),
    @(-join($prefix,'Ring1_ByteBuffer_insertBytesAt.html.t'),
      -join($prefix,'Ring1_ByteBuffer_insertBytesAt.html')),
      
    @(-join($prefix,'Ring1_ByteBuffer_clear.html.t'),
      -join($prefix,'Ring1_ByteBuffer_clear.html')),
    @(-join($prefix,'Ring1_ByteBuffer_getBytes.html.t'),
      -join($prefix,'Ring1_ByteBuffer_getBytes.html')),
    @(-join($prefix,'Ring1_ByteBuffer_getNumberOfBytes.html.t'),
      -join($prefix,'Ring1_ByteBuffer_getNumberOfBytes.html'))
  );
$jobs += $temporary;
