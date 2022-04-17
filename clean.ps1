# Copyright (c) 2021 Michael Heilmann. All rights reserved.
#
# @author    Michael Heilmann <michaelheilmann@primordialmachine.com>
# @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
# @file      clean.ps1
# @brief     Remove 'intermediates' and 'products' as well as '.vs' directories from all projects.

# @brief Ensure a directory does not exist.
# @param $path The path to the directory.
function Remove {
    param (
        [string[]]$path
    )
  Write-Host -NoNewline ('removing ''' + $path + '''')
  if (test-path $path) {
    Remove-Item $path -Force -Recurse
    Write-Host (' ... found and deleted')
  } else {
    Write-Host('... not found')
  }
}

Remove '.\machine-mk1\.vs'
Remove '.\machine-mk1\intermediates'
Remove '.\machine-mk1\products'

Remove '.\ring1\.vs'
Remove '.\ring1\intermediates'
Remove '.\ring1\products'
