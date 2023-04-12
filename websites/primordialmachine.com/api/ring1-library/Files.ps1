# Copyright (c) 2022 Michael Heilmann. All rights reserved.
$prefix = './api/ring1-library/';
$jobs +=
  @(
    # Ring 1.
    @(-join($prefix,'index.html.template'),
      -join($prefix,'index.html')),
    @(-join($prefix,'sitemap.xml.template'),
      -join($prefix,'sitemap.xml')),
    @(-join($prefix,'concepts.html.template'),
      -join($prefix,'concepts.html')),
    @(-join($prefix,'design-rational.html.template'),
      -join($prefix,'design-rational.html'))

    # Ring 1 - Atom Library.
    #@('./ring1-library/atom-library.html.template',
    #  './ring1-library/atom-library.html'),

    # Ring 1 - Collections Commons Library.
    #@('./ring1-library/collections-commons-library.html.template',
    #  './ring1-library/collections-commons-library.html'),

    # Ring 1 - Log Library.
    #@('./ring1-library/log-library.html.template',
    #  './ring1-library/log-library.html'),

    # Ring 1 - Object Library.
    #@('./ring1-library/object-library.html.template',
    #  './ring1-library/object-library.html'),

    # Ring 1 - Pointer Deque Library.
    #@('./ring1-library/pointerdeque-library.html.template',
    #  './ring1-library/pointerdeque-library.html'),

    # Ring 1 - Pointer Hash Map Library.
    #@('./ring1-library/pointerhashmap-library.html.template',
    #  './ring1-library/pointerhashmap-library.html'),
  );

. "$PSScriptRoot\bytebuffer-library\Files.ps1"
. "$PSScriptRoot\collections-library\Files.ps1"
. "$PSScriptRoot\filesystem-library\Files.ps1"
. "$PSScriptRoot\hash-library\Files.ps1"
. "$PSScriptRoot\intrinsic-library\Files.ps1"
. "$PSScriptRoot\memory-library\Files.ps1"
. "$PSScriptRoot\result-library\Files.ps1"
. "$PSScriptRoot\status-library\Files.ps1"
. "$PSScriptRoot\time-library\Files.ps1"
. "$PSScriptRoot\pointerlist-library\Files.ps1"
