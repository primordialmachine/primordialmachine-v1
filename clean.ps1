# Copyright (c) 2021 Michael Heilmann. All rights reserved.
#
# @author    Michael Heilmann <michaelheilmann@primordialmachine.com>
# @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
# @file      clean.ps1
# @brief     Perform cleanup of the project directory.
# @detail    Perform cleanup of the project directory. This involves
#            - Removal of the 'intermediates' and 'products' as well as '.vs' directories of all solutions.
#            - Removal of all empty directories.

param(
   [string] $workingDirectory
)

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

$projects = @(
  '.\machine-mk1',
  '.\Ring1',
  '.\Ring2',
  '.\Ring3',
  '.\Scribe',
  '.\mkx-demos'
);

if (!$workingDirectory) {
  $workingDirectory = Get-Location;
}
Write-Host('working directory: ' + $workingDirectory);

foreach($project in $projects) {
  ClearSolution($workingDirectory + '\' + $project)
}
