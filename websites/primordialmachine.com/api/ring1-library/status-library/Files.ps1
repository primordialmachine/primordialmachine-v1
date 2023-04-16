# Copyright (c) 2022 Michael Heilmann. All rights reserved.
$prefix = './api/ring1-library/status-library/';
$jobs +=
  @(
    # Ring 1 - Status Library.
    @(-join($prefix,'index.html.t'),
      -join($prefix,'index.html')),
    @(-join($prefix,'Ring1_Status.html.t'),
      -join($prefix,'Ring1_Status.html')),
    @(-join($prefix,'Ring1_Status_get.html.t'),
      -join($prefix,'Ring1_Status_get.html')),
    @(-join($prefix,'Ring1_Status_set.html.t'),
      -join($prefix,'Ring1_Status_set.html')),
    @(-join($prefix,'status-codes.html.t'),
      -join($prefix,'status-codes.html'))
  );
