@echo off
cmake --build ../../build/Windows/
robocopy ../../UnnamedClient/env ../../out/Windows/UnnamedClient /E >NUL