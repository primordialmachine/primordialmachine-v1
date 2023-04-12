# Copyright (c) 2022 Michael Heilmann. All rights reserved.
$prefix = './api/ring1-library/collections-library/';

$temporary =
  @(
    # Ring 1 - Collection Library.
    @(-join($prefix, 'index.html.t'),
      -join($prefix, 'index.html')),
    @(-join($prefix, 'Ring1_AddedCallback.html.t'),
      -join($prefix, 'Ring1_AddedCallback.html')),
    @(-join($prefix, 'Ring1_GetHashCallback.html.t'),
      -join($prefix, 'Ring1_GetHashCallback.html')),
    @(-join($prefix, 'Ring1_IsEqualToCallback.html.t'),
      -join($prefix, 'Ring1_IsEqualToCallback.html')),
    @(-join($prefix, 'Ring1_RemovedCallback.html.t'),
      -join($prefix, 'Ring1_RemovedCallback.html'))
  );
$jobs += $temporary;

. "$PSScriptRoot\PointerDeque\Files.ps1"
. "$PSScriptRoot\PointerHashMap\Files.ps1"
