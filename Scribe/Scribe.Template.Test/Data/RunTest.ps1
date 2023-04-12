# Copyright (c) 2020-2021 Michael Heilmann. All rights reserved.

# Powershell script used to run tests for Scribe Template.
#
# INSTRUCTIONS:
# The working directory of the script must be the directory this file is located in.
# Invoke the script by switching to that directory and enter `./RunTests.ps`.
# The script will exit at the first test failing with exit code -1.
# If all tests succeed, it will exit with exit code 0.

try {
  # Must be $TRUE or $FALSE.
  # Cleanup on successful exit if $TRUE.
  $cleanupOnSuccess = $TRUE

  # Exits the script, performing required cleanup and reporting.
  # if $tests is specified, the tests are cleaned up.
  # if $message is specified, the mesage is printed.
  # $exitCode must be 0 (indicating success) or -1 (indicating failure).
  function doExit {
      param (
        $tests,
        [String]$message,
        [Int]$exitCode
      )
      if ($message) {
        Write-Host $message
      }
      if ($tests) {
        if (($exitCode -eq 0) -and ($cleanupOnSuccess -eq $TRUE)) {
          foreach($test in $tests) {
            $folder = $($test[0]);
            $file = "$folder/1.html"
            if (Test-Path $file) {
              Remove-Item $file
            }
          }
        }
      }
      Exit $exitCode
  }

  # Architecture. Must be 'x64' or 'x86'.
  $arch = 'x86'

  # Assert $arch is either 'x64' or 'x86'.
  if (($arch -ne 'x64') -and ($arch -ne 'x86')) {
    $msg = 'internal error: $arch is "' + $arch + '", must be either "x64" or "x86"'
    doExit -exitCode -1 -message $msg
  }

  # Path to executable. Executable must exist.
  $executable="./../../../scribe/products/$arch/release/Scribe/Scribe.exe"
  
  # Assert $executable exists.
  if (-not(Test-Path -Path $executable -PathType Leaf)) {
    $msg = 'internal error: "' + $executable + '" does not exist'
    doExit -exitCode -1 -message $msg
  }

  # The tool of Scribe to invoke. Must be 'template'.
  $tool='template'

  # Assert $tool is 'template'.
  if ($tool -ne 'template') {
    $msg = 'internal error: $tool is "' + $tool + '", must be "template"'
    doExit -exitCode -1 -message $msg
  }

  $jobs = @(
    @('multiLineComment1', $TRUE),
    @('stringLiteralConcatenation', $TRUE),
    @('stringLiteralEvaluation', $TRUE),
    @('stringVariableEvaluation', $TRUE),
    @('undefinedVariable', $FALSE),
    @('unclosedComment', $FALSE)
  );

  # Clean all tests.
  foreach($job in $jobs) {
    $folder = $($job[0]);
    $file = "$folder/1.html"
    if (Test-Path $file) {
      Remove-Item $file
    }
  }

  # Execute tests.
  foreach($job in $jobs) {
    $name = $($job[0]);
    $folder = "./$name";
    $expectedExitCode = $($job[1])
    [Void](Invoke-Expression "$executable $tool `"$folder/1.configuration`" `"$folder/1.html.template`" `"$folder/1.html`"")
    if (-not($lastexitcode -eq 0) -and ($expectedExitCode -eq $TRUE)) {
      doExit -tests $jobs -exitCode -1 -message "`"$folder`" failed: invalid exit code"
    }
    $file = "$folder/1.html"
    if (-not(Test-Path $file) -and ($expectedExitCode -eq $TRUE)) {
      doExit -tests $jobs -exitCode -1 -message "`"$folder`" failed: invalid output"
    }
    Write-Host "`"$folder`" succeeded"
  }

  # Clean all tests.
  doExit -tests $jobs -exitCode 0 -message "all tests succeeded"

} catch {
  doExit -exitCode -1 -message "internal error: unknown error"
}
