# Copyright (c) 2022 Michael Heilmann. All rights reserved.
$prefix = './api/ring1-library/time-library/';
$jobs +=
  @(
    # Ring 1 - Time Library.
    @(-join($prefix,'index.html.t'),
      -join($prefix,'index.html')),
    @(-join($prefix,'Ring1_Time_getNowMilliseconds.html.t'),
      -join($prefix,'Ring1_Time_getNowMilliseconds.html')),
    @(-join($prefix,'Ring1_Time_getNowSeconds.html.t'),
      -join($prefix,'Ring1_Time_getNowSeconds.html')),
    @(-join($prefix,'Ring1_Time_getNowMinutes.html.t'),
      -join($prefix,'Ring1_Time_getNowMinutes.html'))
  );
