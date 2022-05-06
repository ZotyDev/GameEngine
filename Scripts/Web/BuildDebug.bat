cd ..\..
call vendor\.bin\premake\premake5.exe emcc --gfxapi=opengl --sndapi=openal --arch=x64 --netapi=winsock
PAUSE