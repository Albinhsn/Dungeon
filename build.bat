@echo off

set CommonCompilerFlags=-MT -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4505 -wd4456 -wd4201 -wd4100 -wd4189 -FC -Z7 /I "C:\Program Files\dev\sta-lib\platform" -DPLATFORM_WINDOWS=1 -DPLATFORM_GRAPHICS_SOFTWARE=1
set CommonLinkerFlags= -opt:ref user32.lib gdi32.lib winmm.lib

call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"

REM cl %CommonCompilerFlags%  .\src\game.cpp -LD /link -incremental:no -opt:ref -EXPORT:update
cl %CommonCompilerFlags% .\src\main.cpp /link %CommonLinkerFlags%
