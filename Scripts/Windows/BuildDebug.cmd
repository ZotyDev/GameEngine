@echo off
cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=E:/Projects/UnnamedEngine/Scripts/Windows/Windows.cmake ../../CMakeLists.txt -B ../../build/Windows