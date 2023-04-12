# Copyright (c) 2022 Michael Heilmann. All rights reserved.
$prefix = './api/ring1-library/collections-library/';

$temporary =
  @(
    # Ring 1 - PointerDeque Library.
    @(-join($prefix, 'PointerDeque/Ring1_PointerDeque.html.t'),
      -join($prefix, 'Ring1_PointerDeque.html')),
    @(-join($prefix, 'PointerDeque/Ring1_PointerDeque_clear.html.t'),
      -join($prefix, 'Ring1_PointerDeque_clear.html')),
    @(-join($prefix, 'PointerDeque/Ring1_PointerDeque_getSize.html.t'),
      -join($prefix, 'Ring1_PointerDeque_getSize.html')),
    #
    @(-join($prefix, 'PointerDeque/Ring1_PointerDeque_initialize.html.t'),
      -join($prefix, 'Ring1_PointerDeque_initialize.html')),
    @(-join($prefix, 'PointerDeque/Ring1_PointerDeque_uninitialize.html.t'),
      -join($prefix, 'Ring1_PointerDeque_uninitialize.html')),
    #
    @(-join($prefix, 'PointerDeque/Ring1_PointerDeque_Capacity_Default.html.t'),
      -join($prefix, 'Ring1_PointerDeque_Capacity_Default.html')),
    @(-join($prefix, 'PointerDeque/Ring1_PointerDeque_Capacity_Least.html.t'),
      -join($prefix, 'Ring1_PointerDeque_Capacity_Least.html')),
    @(-join($prefix, 'PointerDeque/Ring1_PointerDeque_Capacity_Greatest.html.t'),
      -join($prefix, 'Ring1_PointerDeque_Capacity_Greatest.html'))
  );
$jobs += $temporary;
