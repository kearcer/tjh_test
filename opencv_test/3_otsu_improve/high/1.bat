@echo off
setlocal EnableDelayedExpansion

set /a count=1

for %%f in (*.*) do (
    set "filename=%%f"
    set "extension=%%~xf"
    ren "!filename!" "!count!!extension!"
    set /a count+=1
)

echo Renamed !count! files.
