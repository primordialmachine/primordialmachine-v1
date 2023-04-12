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

$configuration='./website.configuration'
$executable='./../../scribe/products/x64/release/Scribe/Scribe.exe'
$tool='template'

# Initially empty list of mappings.
$jobs = @()

. "$PSScriptRoot\reference\Files.ps1"
. "$PSScriptRoot\api\ring1-library\Files.ps1"

$jobs +=
@(
  #
  @('./index.thtml',                                                                       './index.html'),
  @('./my.css.template',                                                                   './my.css'),
  @('./my.js.template',                                                                    './my.js'),
  @('./sitemap.xml.template',                                                              './sitemap.xml'),

  # About us page.
  @('./about-primordial-machine.html.template',                                            './about-primordial-machine.html'),

  # Landing page.
  @('./landingpage-sitemap.xml.template',                                                  './landingpage-sitemap.xml'),

  # Gaming.
  @('./gaming/azur-lane.thtml',                                                            './gaming/azur-lane.html'),

  # Intermediate language specification.
  @('./intermediate-language-specification/index.thtml',                                   './intermediate-language-specification/index.html'),
  @('./intermediate-language-specification/1-introduction.thtml',                          './intermediate-language-specification/1-introduction.html'),
  @('./intermediate-language-specification/2-method-of-description-and-notation.thtml',    './intermediate-language-specification/2-method-of-description-and-notation.html'),
  @('./intermediate-language-specification/3-types-and-values.thtml',                      './intermediate-language-specification/3-types-and-values.html'),
  @('./intermediate-language-specification/4-instructions.thtml',                          './intermediate-language-specification/4-instructions.html'),
  @('./intermediate-language-specification/5-lexical-grammar.thtml',                       './intermediate-language-specification/5-lexical-grammar.html')
)

#
foreach($job in $jobs) {
  if (Test-Path -Path $($job[1]) -PathType Leaf) {
    Write-Host "removing $($job[1])"
    Remove-Item "$($job[1])"
  }
}
