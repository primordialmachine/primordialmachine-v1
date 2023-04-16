# Copyright (c) 2022 Michael Heilmann. All rights reserved.
$prefix = './api/ring1-library/pointerlist-library/';
$temporary =
  @(
    # Ring 1 - Pointer List Library.
    @(-join($prefix, 'index.html.t'),
      -join($prefix, 'index.html')),
    @(-join($prefix, 'Ring1_PointerList.html.t'),
      -join($prefix, 'Ring1_PointerList.html')),
    @(-join($prefix, 'Ring1_PointerList_initialize.html.t'),
      -join($prefix, 'Ring1_PointerList_initialize.html')),
    @(-join($prefix, 'Ring1_PointerList_uninitialize.html.t'),
      -join($prefix, 'Ring1_PointerList_uninitialize.html')),
    @(-join($prefix, 'Ring1_PointerList_Capacity_Greatest.html.t'),
      -join($prefix, 'Ring1_PointerList_Capacity_Greatest.html')),
    @(-join($prefix, 'Ring1_PointerList_Capacity_Least.html.t'),
      -join($prefix, 'Ring1_PointerList_Capacity_Least.html')),
    @(-join($prefix, 'Ring1_PointerList_Capacity_Default.html.t'),
      -join($prefix, 'Ring1_PointerList_Capacity_Default.html')),
    @(-join($prefix, 'Ring1_PointerList_clear.html.t'),
      -join($prefix, 'Ring1_PointerList_clear.html'))
  );
$jobs += $temporary;
