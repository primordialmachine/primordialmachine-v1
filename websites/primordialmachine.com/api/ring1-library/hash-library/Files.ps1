# Copyright (c) 2022 Michael Heilmann. All rights reserved.
$prefix = './api/ring1-library/hash-library/';
$jobs +=
  @(
    # Ring 1 - Hash Library.
    @(-join($prefix,'index.html.t'),
      -join($prefix,'index.html')),
    @(-join($prefix,'Ring1_Hash_toI64.html.t'),
      -join($prefix,'Ring1_Hash_toI64.html')),
    @(-join($prefix,'Ring1_Hash_toSz.html.t'),
      -join($prefix,'Ring1_Hash_toSz.html'))
  );
