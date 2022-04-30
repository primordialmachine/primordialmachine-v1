# Copyright (c) 2021 Michael Heilmann. All rights reserved.
#
# @author    Michael Heilmann <michaelheilmann@primordialmachine.com>
# @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
# @file      clean.ps1
# @brief     Perform cleanup of the project directory.
# @detail    Perform cleanup of the project directory. This involves
#            - Removal of the 'intermediates' and 'products' as well as '.vs' directories of all solutions.
#            - Removal of all empty directories.

# @brief Ensure a directory does not exist.
# @param $path The path to the directory.
function RemoveDirIfExists {
    param (
        [string[]] $path
    )
  Write-Host -NoNewline ('  removing ''' + $path + '''')
  if (test-path $path) {
    Remove-Item $path -Force -Recurse
    Write-Host (' ... found and deleted')
  } else {
    Write-Host('... not found')
  }
}

# @brief Cleanup a solution.
# @param $solutionDir The path to the solution directory.
function ClearSolution {
    param (
      [string[]] $solutionDir
    )
  Write-Host('cleaning solution ''' + $solutionDir + '''')

  RemoveDirIfExists("$solutionDir\.vs")
  RemoveDirIfExists("$solutionDir\intermediates")
  RemoveDirIfExists("$solutionDir\products")
  
  $dirs = gci $solutionDir -directory -recurse | Where { (gci $_.fullName).count -eq 0 } | select -expandproperty FullName
  $dirs | Foreach-Object { RemoveDirIfExists $_ }    
}

$d = '.\machine-mk1'
ClearSolution($d)

$d = '.\ring1'
ClearSolution($d)

$d = '.\ring2'
ClearSolution($d)
