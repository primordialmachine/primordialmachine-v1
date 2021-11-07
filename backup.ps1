# @file backup.ps
#
# @brief Create a backup of this directory in this directory.
#
# @details 
# Create a backup of this directory within(!) this directory.
# Old backups in this directory are not included in new backups.
# A backup is a ZIP file plus checksum files for the checksums of the zip file.
#
# The name of the ZIP file (without path and without extension) is of the form
# 'PrimordialMachine-<Time>' where <Time> denotes the the year, month, and day of the
# backup in ISO 8601 format.
#
# Two checksum files are created for an archive file, the MD5 checksum file and the SHA256 checksum file.
# Their file names (without path) are 'ARCHIVE.zip.md5' and 'ARCHIVE.zip.sha256' if the the archive file name (without path) is 'ARCHIVE.zip'.
#
# @author Michael Heilmann <michaelheilmann@primordialmachine.com>
# @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.



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


$ARCHIVE_EXTENSION = '.zip'
$ARCHIVE_PATH = '.\'
$ARCHIVE_NAME = 'PrimordialMachine-' + (Get-Date -format "yyyy-MM-dd").toString()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #

# If the archive or any checksum file for this backup exist, terminate with error.
if (test-path ($ARCHIVE_PATH + $ARCHIVE_NAME + $ARCHIVE_EXTENSION)) {
  Write-Host ('aborting: ''' + $ARCHIVE_NAME + $ARCHIVE_EXTENSION + ''' already exists.')
  exit 1
}
if (test-path ($ARCHIVE_PATH + $ARCHIVE_NAME + $ARCHIVE_EXTENSION + '.sha256')) {
  Write-Host ('aborting: ''' + $ARCHIVE_NAME + $ARCHIVE_EXTENSION + '.sha256' + ''' already exists.')
  exit 1
}
if (test-path ($ARCHIVE_PATH + $ARCHIVE_NAME + $ARCHIVE_EXTENSION + '.md5')) {
  Write-Host ('aborting: ''' + $ARCHIVE_NAME + $ARCHIVE_EXTENSION + '.md5' + ''' already exists.')
  exit 1
}

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #

# Create temporary directory.
If (!(test-path '.\.backup')) {
  Write-Host ('creating temporary directory')
  New-Item -Path '.' -Name '.backup' -ItemType 'directory' | Out-Null
}

Write-Host ('copying files')
Copy-Item -Path (Get-Item -Force -Path '.\*' -Exclude ('.backup')).FullName -Destination '.\.backup' -Recurse -Force

Remove '.\.backup\machine-mk1\.vs'
Remove '.\.backup\machine-mk1\intermediates'
Remove '.\.backup\machine-mk1\products'
Remove '.\.backup\.git'
Remove '.\.backup\PrimordialMachine-*.zip'

Compress-Archive -CompressionLevel 'Optimal' -Path '.\.backup\*' -DestinationPath ('.\' + $ARCHIVE_NAME + $ARCHIVE_EXTENSION)

$hash = Get-FileHash -Path ('.\' + $ARCHIVE_NAME + $ARCHIVE_EXTENSION) -Algorithm 'SHA256'
Set-Content -Path ($ARCHIVE_PATH + $ARCHIVE_NAME + $ARCHIVE_EXTENSION + '.sha256') -Value ($hash.Hash.toString() + ' *' + ($ARCHIVE_NAME + $ARCHIVE_EXTENSION))

$hash = Get-FileHash -Path ($ARCHIVE_PATH + $ARCHIVE_NAME + $ARCHIVE_EXTENSION) -Algorithm 'MD5'
Set-Content -Path ($ARCHIVE_PATH + $ARCHIVE_NAME + $ARCHIVE_EXTENSION +  '.md5') -Value ($hash.Hash.toString() + ' *' + ($ARCHIVE_NAME + $ARCHIVE_EXTENSION))

# Remove the temporary directory.
Remove ('.\.backup')

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #