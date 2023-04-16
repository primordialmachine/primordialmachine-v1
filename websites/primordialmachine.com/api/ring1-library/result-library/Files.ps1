# Copyright (c) 2022 Michael Heilmann. All rights reserved.
$prefix = './api/ring1-library/result-library/';
$jobs +=
  @(
    # Ring 1 - Result Library.
    @(-join($prefix,'index.html.t'),
      -join($prefix,'index.html')),
    @(-join($prefix,'Ring1_Result.html.t'),
      -join($prefix,'Ring1_Result.html')),
    @(-join($prefix,'result-codes.html.t'),
      -join($prefix,'result-codes.html'))
  );
