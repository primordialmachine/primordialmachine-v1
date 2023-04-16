$Env:Path+=';C:\Program Files\7-Zip'

# Remove old website.zip if it exists.
Remove-Item './website.zip' -Force -Recurse -ErrorAction SilentlyContinue
# Remove old temporary if it exists.
Get-ChildItem -Path './temporary' -Recurse | Remove-Item -force -recurse
Remove-Item './temporary' -force -Recurse -ErrorAction SilentlyContinue
# Create new temporary.
robocopy '.' './temporary' /S /XF *.ps1 *.thtml *.ihtml *.zip *.exe /XD temporary
# Zip temporary/* to website.zip.
7z.exe a website.zip .\temporary\*
# Remove new temporary if it exists.
Get-ChildItem -Path './temporary' -Recurse | Remove-Item -force -recurse
Remove-Item './temporary' -force -recurse -ErrorAction SilentlyContinue