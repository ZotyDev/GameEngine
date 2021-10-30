cd ..\..
call vendor\.bin\premake\premake5.exe vs2019 --gfxapi=opengl --sndapi=openal --arch=x64 --netapi=winsock
PAUSE