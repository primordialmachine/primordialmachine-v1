# Copyright (c) 2022 Michael Heilmann. All rights reserved.
$prefix = './api/ring1-library/collections-library/';

$temporary =
  @(
    # Ring 1 - PointerHashMap Library.
    @(-join($prefix, 'PointerHashMap/Ring1_PointerHashMap.html.t'),
      -join($prefix, 'Ring1_PointerHashMap.html')),
    #
    @(-join($prefix, 'PointerHashMap/Ring1_PointerHashMap_Capacity_Default.html.t'),
      -join($prefix, 'Ring1_PointerHashMap_Capacity_Default.html')),
    @(-join($prefix, 'PointerHashMap/Ring1_PointerHashMap_Capacity_Least.html.t'),
      -join($prefix, 'Ring1_PointerHashMap_Capacity_Least.html')),
    @(-join($prefix, 'PointerHashMap/Ring1_PointerHashMap_Capacity_Greatest.html.t'),
      -join($prefix, 'Ring1_PointerHashMap_Capacity_Greatest.html'))
  );
$jobs += $temporary;
