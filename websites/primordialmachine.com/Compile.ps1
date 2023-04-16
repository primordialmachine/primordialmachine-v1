# Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

# Powershell script used to compile this website under Windows 10.
#
# INSTRUCTIONS:
# The working directory of the script must be the directory this file is located in.
# Invoke the script by switching to that directory and enter `./Compile.ps`.
#
# By default, this script compiles this website for the hostname specified in the file `website.configuration`.
# You can override the hostname by passing the parameter `hostname` when invoking the script.
#
# `./Compile.ps1` compilee the website for the hostname specified in `website.configuration`.
# `./Compile.ps1 -hostname 'https://localhost:449/'` compiles this website for the hostname `https://localhost:449/`.
#
param (
  [Parameter(Mandatory=$false)] [string] $hostname = $null
)

# Architecture. Must be 'x64' or 'x86'.
$arch = 'x86'

# Assert $arch is either 'x64' or 'x86'.
if (($arch -ne 'x64') -and ($arch -ne 'x86')) {
  $msg = '$arch is "' + $arch + '", must be either "x64" or "x86"'
  throw $msg
}


$configuration='./website.configuration'

# When invoking this script in a console window, the executable's paths should be prepended to the path of that console window.
# To prepend the executable's path to the path of the console window, enter
# `$env:Path = "<executable's path>;" + $env:Path`
# in the console window where
# `<executable's path>`
# is the executable's path.
$executable='PrimordialMachine.Scribe.exe'

$tool='template'

# Initially empty list of jobs.
$jobs = @()

. "$PSScriptRoot\reference\Files.ps1"
. "$PSScriptRoot\api\ring1-library\Files.ps1"

$jobs +=
@(
  #
  @('./index.html.t',
    './index.html'),
  @('./my.css.t',
    './my.css'),
  @('./my.js.t',
    './my.js'),
  @('./sitemap.xml.t',
    './sitemap.xml'),

  # About us page.
  @('./about-primordial-machine.html.template',
    './about-primordial-machine.html'),

  # Landing page.
  @('./_landingpage-sitemap.xml.t',
    './_landingpage-sitemap.xml'),

  # Gaming.
  @('./gaming/azur-lane.thtml',
    './gaming/azur-lane.html'),

  # Intermediate language specification.
  @('./intermediate-language-specification/index.html.t',
    './intermediate-language-specification/index.html'),
  @('./intermediate-language-specification/1-introduction.html.t',
    './intermediate-language-specification/1-introduction.html'),
  @('./intermediate-language-specification/2-method-of-description-and-notation.html.t',
    './intermediate-language-specification/2-method-of-description-and-notation.html'),
  @('./intermediate-language-specification/3-types-and-values.html.t',
    './intermediate-language-specification/3-types-and-values.html'),
  @('./intermediate-language-specification/4-instructions.html.t',
    './intermediate-language-specification/4-instructions.html'),
  @('./intermediate-language-specification/5-lexical-grammar.html.t',
    './intermediate-language-specification/5-lexical-grammar.html')
)

#
foreach($job in $jobs) {
  if ($PSBoundParameters.ContainsKey('hostname')) {
    try {
      Invoke-Expression "$executable $tool --hostname=""(\""""$hostname\"""")"" $configuration '$($job[0])' '$($job[1])'"
    } catch {
      Write-Host "failed to process '$($job[0])'" 
      exit
    }
  } else {
    try {
      Invoke-Expression "$executable $tool $configuration '$($job[0])' '$($job[1])'"
    } catch {
      Write-Host "failed to process '$($job[0])'" 
      exit
    }
  }
}
