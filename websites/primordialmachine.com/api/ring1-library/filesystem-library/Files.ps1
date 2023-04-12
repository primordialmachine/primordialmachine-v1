# Copyright (c) 2022 Michael Heilmann. All rights reserved.
$prefix = './api/ring1-library/filesystem-library/';
$jobs +=
  @(
    # Ring 1 - FileSystem Library.
    @(-join($prefix,'index.html.t'),
      -join($prefix,'index.html')),
    @(-join($prefix,'Ring1_FileSystem_setFileContents.html.t'),
      -join($prefix,'Ring1_FileSystem_setFileContents.html')),
    @(-join($prefix,'Ring1_FileSystem_getFileContents.html.t'),
      -join($prefix,'Ring1_FileSystem_getFileContents.html')),

    @(-join($prefix,'Ring1_FileSystem_AllocateCallback.html.t'),
      -join($prefix,'Ring1_FileSystem_AllocateCallback.html')),
    @(-join($prefix,'Ring1_FileSystem_DeallocateCallback.html.t'),
      -join($prefix,'Ring1_FileSystem_DeallocateCallback.html')),

    @(-join($prefix,'Ring1_FileSystem_FileAccessMode.html.t'),
      -join($prefix,'Ring1_FileSystem_FileAccessMode.html')),
    @(-join($prefix,'Ring1_FileSystem_ExistingFilePolicy.html.t'),
      -join($prefix,'Ring1_FileSystem_ExistingFilePolicy.html')),
    @(-join($prefix,'Ring1_FileSystem_NonExistingFilePolicy.html.t'),
      -join($prefix,'Ring1_FileSystem_NonExistingFilePolicy.html'))
  );
