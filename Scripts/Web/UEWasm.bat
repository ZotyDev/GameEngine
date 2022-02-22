@echo off
setlocal enabledelayedexpansion enableextensions

:: Location of Emscripten SDK
set EMSDK="c:\emsdk"

:: Debug output folder
set DEBUGOUT="..\..\bin\Debug-web"

:: Release output folder
set RELEASEOUT="..\..\bin\Release-web"

:: Distribuition output folder
set DISTRIBUITIONOUT="..\..\bin\Distribuition-web"

:: FreeType folders
set FREETYPE_DIR="..\..\UnnamedEngine\vendor\FreeType"
set FREETYPE_SRC=%FREETYPE_DIR%\src
set FREETYPE_INCLUDES=                                 ^
    -I %FREETYPE_DIR%\include                          ^
    -I %FREETYPE_DIR%\subprojects\dlg\include          ^
    -I %FREETYPE_DIR%\subprojects\dlg\src\dlg          

set FREETYPE_FILES=               ^
    "src/autofit/autofit.c"       ^
	 "src/bdf/bdf.c"               ^
	 "src/cff/cff.c"               ^
	 "src/dlg/dlgwrap.c"           ^
	 "src/base/ftbase.c"           ^                    
	 "src/base/ftbbox.c"           ^
	 "src/base/ftbdf.c"            ^
	 "src/base/ftbitmap.c"         ^
	 "src/cache/ftcache.c"         ^
	 "src/base/ftcid.c"            ^
	 "src/base/ftgasp.c"           ^
	 "src/base/ftglyph.c"          ^
	 "src/base/ftgxval.c"          ^
	 "src/gzip/ftgzip.c"           ^
	 "src/base/ftinit.c"           ^
	 "src/lzw/ftlzw.c"             ^
	 "src/base/ftmm.c"             ^
	 "src/base/ftotval.c"          ^
	 "src/base/ftpatent.c"         ^
	 "src/base/ftpfr.c"            ^
	 "src/base/ftstroke.c"         ^
	 "src/base/ftsynth.c"          ^
	 "src/base/fttype1.c"          ^
	 "src/base/ftwinfnt.c"         ^
	 "src/pcf/pcf.c"               ^
	 "src/pfr/pfr.c"               ^
	 "src/psaux/psaux.c"           ^
	 "src/pshinter/pshinter.c"     ^
	 "src/psnames/psmodule.c"      ^
	 "src/raster/raster.c"         ^
	 "src/sdf/sdf.c"               ^
	 "src/sfnt/sfnt.c"             ^
	 "src/smooth/smooth.c"         ^
	 "src/truetype/truetype.c"     ^
	 "src/type1/type1.c"           ^
	 "src/cid/type1cid.c"          ^
	 "src/type42/type42.c"         ^
	 "src/winfonts/winfnt.c"       

set FREETYPE_DEFINES=             ^
    -D FT_DEBUG_LEVEL_ERROR       ^
    -D FT_DEBUG_LEVEL_TRACE       ^
    -D FT_DEBUG_LOGGING           ^
    -D FT2_BUILD_LIBRARY

:: GLAD folders

:: GLFW folders

:: Lua folders
set LUA_DIR="..\..\UnnamedEngine\vendor\LUA"
set LUA_SRC=%LUA_DIR%
set LUA_INCLUDES=                 ^
    -I %LUA_DIR%                  

set LUA_FILES=        ^
    "lapi.c"          ^
    "luaxlib.c"       ^
    "lbaselib.c"      ^
    "lcode.c"         ^
    "lcorolib.c"      ^
    "lcype.c"         ^
    "ldblib.c"        ^
    "ldebug.c"        ^
    "ldo.c"           ^
    "ldump.c"         ^
    "lfunc.c"         ^
    "lgc.c"           ^
    "linit.c"         ^
    "liolib.c"        ^
    "llex.c"          ^
    "lmathlib.c"      ^
    "lmem.c"          ^
    "loadlib.c"       ^
    "lmem.c"          ^
    "lobject.c"       ^
    "lopcodes.c"      ^
    "loslib.c"        ^
    "lparser.c"       ^
    "lstate.c"        ^
    ""


:: Engine folders
set ENGINEDIR="..\..\UnnamedEngine"
set ENGINESRC="..\..\UnnamedEngine\src"
set ENGINEPLATFORM="..\..\UnnamedEngine\platform"

:: Game folders
set GAMEDIR="..\..\VoxelGame"
set GAMESRC="..\..\VoxelGame\src"

:: Engine include folders
set INCLUDE_GLFW=%ENGINEDIR%\vendor\GLFW\include              
set INCLUDE_GLAD=%ENGINEDIR%\vendor\GLAD\include              
set INCLUDE_GLM=%ENGINEDIR%\vendor\GLM                       
set INCLUDE_STB=%ENGINEDIR%\vendor\STB                       
set INCLUDE_LUA=%ENGINEDIR%\vendor\LUA                       
set INCLUDE_FREETYPE=%ENGINEDIR%\vendor\FreeType\include          
set INCLUDE_OPENAL=%ENGINEDIR%\vendor\OpenAL-Soft\include    
set INCLUDE_FMT=%ENGINEDIR%\vendor\fmt\include
set INCLUDE_VULKAN=C:\VulkanSDK\1.2.189.2\Include               
set INCLUDE_EMSCRIPTEN=C:\emsdk\upstream\emscripten\system\include 

set ENGINE_INCLUDE_MAIN=%ENGINDEDIR%\

set ENGINE_INCLUDE_DEFAULT=             ^
    -I %ENGINESRC%                      ^
    -I %ENGINEPLATFORM%                 ^
    -I %INCLUDE_GLM%                    ^
    -I %INCLUDE_LUA%                    ^
    -I %INCLUDE_FMT%

:: Game include folders
set GAME_INCLUDE_DEFAULT=               ^
    -I %ENGINESRC%                      ^
    -I %GAMESRC%                        ^
    -I %INCLUDE_GLM%                    ^
    -I %INCLUDE_LUA%                    ^
    -I %INCLUDE_FMT%

set WORKINGDIR=%CD%

if not exist %EMSDK% (
   echo Error: Emscripten SDK folder not found!
   goto :fail
)

if "%1"=="build" goto :build
if "%1"=="run" goto :run
if "%1"=="clean" goto :clean
goto :error

:build
    :: Configure path variables
    cd %EMSDK%
    ::call emsdk_env.bat

    :: Create working folder
    cd %WORKINGDIR%

    set TARGET=
    set OPTIMIZATION=
    set ENGINE_DEFINES=
    set GAME_DEFINES=
    :: Select the current build target
    if "%2"=="debug" (
       if not exist %DEBUGOUT% (
          echo Creating %DEBUGOUT% output folder
          mkdir %DEBUGOUT%
       )

       set TARGET=%DEBUGOUT%
       set OPTIMIZATION="-O0"
       set ENGINE_DEFINES=-DUE_DEBUG
       set GAME_DEFINES=-DUE_DEBUG
    )

    if "%2"=="release" (
       if not exist %RELEASEOUT% (
          echo Creating %RELEASEOUT% output folder
          mkdir %RELEASEOUT%
       )
       
       set TARGET=%RELEASEOUT%
       set OPTIMIZATION="-O2"
       set ENGINE_DEFINES=-DUE_RELEASE
       set GAME_DEFINES=-DUE_RELEASE
    )
    
    if "%2"=="distribuition" (
       if not exist %DISTRIBUITIONOUT% (
          echo Creating %DISTRIBUITIONOUT% output folder
          mkdir %DISTRIBUITIONOUT%
       )

       set TARGET=%DISTRIBUITIONOUT%
       set OPTIMIZATION="-O3"
       set ENGINE_DEFINES=-DUE_DISTRIBUITION
       set GAME_DEFINES=-DUE_DISTRIBUITION
    )
    if "%~2"=="" goto :error

    :: Grab all cpp files if no specific file is given
    if "%~3"=="" goto :graball
    set CPP=~3
    goto :embuild

:graball
    echo Gathering *.cpp files from
    echo     %ENGINEPLATFORM%\Web
    set ENGINE_CPP=
    for /R %ENGINEPLATFORM\Web% %%x in (*.cpp, *.c) do (
       set ENGINE_CPP=!ENGINE_CPP! %%x
       echo %%x
    )

    echo Gathering *.cpp files from
    echo     %ENGINEPLATFORM%\FreeType
    for /R %ENGINEPLATFORM\FreeType% %%x in (*.cpp, *.c) do (
       set ENGINE_CPP=!ENGINE_CPP! %%x
       echo %%x
    )

    echo Gathering *.cpp files from
    echo     %ENGINESRC%
    for /R %ENGINESRC% %%x in (*.cpp, *.c) do (
       set ENGINE_CPP=!ENGINE_CPP! %%x
       echo %%x
    )
    set ENGINE_CPP=%ENGINE_CPP:~1%

    echo Gathering *.cpp files from
    echo     %GAMESRC%
    for /R %GAMESRC% %%x in (*.cpp, *.c) do (
       set GAME_CPP=!GAME_CPP! %%x
       echo %%x
    )
    set GAME_CPP=%GAME_CPP:~1%

:embuild

    call em++ -std=c++20 %OPTIMIZATION% -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 %ENGINE_DEFINES% %ENGINE_CPP% -o %TARGET%\UnnamedEngine.a %ENGINE_INCLUDE_DEFAULT%

    if exist "..\..\assets" (
       echo Starting Build with assets
       call em++ -std=c++20 %OPTIMIZATION% -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 %GAME_DEFINES% %GAME_CPP% %TARGET%\UnnamedEngine.a -o %TARGET%\index.html %GAME_INCLUDE_DEFAULT% --preload-file ..\..assets
    ) else (
       echo Starting Build without assets
       call em++ -std=c++20 %OPTIMIZATION% -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 %GAME_DEFINES% %GAME_CPP% %TARGET\UnnamedEngine.a% -o %TARGET%\index.html %GAME_INCLUDE_DEFAULT%
    )

    echo Build Completed
    goto :success

:run
    :: Configure path variables
    cd %EMSDK%
    ::call emsdk_env.bat
    cd %WORKINGDIR%
    call emrun ..\..\bin\Debug-web\index.html
    goto :success

:clean
    if exist %DEBUGOUT% (
       rmdir /s /q %DEBUGOUT%
    )

    if exist %RELEASEOUT% (
       rmdir /s /q %RELEASEOUT%
    )

    if exist %DISTRIBUITIONOUT% (
       rmdir /s /q %DISTRIBUITIONOUT%
    )
    goto :success

:error
    echo Error: Incorrect Input
    goto :fail

:success
    echo Exit with success
    goto :leave

:fail
    echo Exit with failure
    goto :leave

:leave
    exit