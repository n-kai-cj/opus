@echo off

set TARGET=win32-x86-64
set NAME=libopus_%TARGET%

mkdir %TARGET%



copy /Y ..\build\lib\Release\libopus.dll %TARGET%

copy /Y ..\build\lib\Release\jnilibopus.dll %TARGET%

copy /Y ..\libs\opus.dll %TARGET%

jar -cvf %NAME%.jar %TARGET%

rd /S /Q %TARGET%

pause
