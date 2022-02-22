# UnnamedEngine
![Logo Image](/Resource/Branding/unnamed_engine.png?raw=true "Unnamed Engine")

This Engine is the base of all ZotyDev games.
Its main goal is performance, allowing me to create crazy and complex stuff without restrictions.
(learning is the second main goal)

## Supported Platforms:
- Windows 10/11


## Current Features:
- Async Logger 
- Event System
- Graphics Renderer
    - Opengl
- Audio Renderer
    - OpenAL-Soft
- Basic Lua Wrapper

# To do:
- Vulkan Renderer
- DirectX Renderer
- Network System
- Web Compiling
- Object Importing
- Engine Editor
- 2D Animation System
- 3D Animation System
- Particle System
- 3D Rendering Optimization

# Compiling:
Go to `Scripts/` and select the target platform.

## Compiling Notes:
### Web:
The folder `YourGame/assets/` is where all data that is going to be used should be. At compilation, this folder will be compiled into a `.data` file that is basically a virtual folder.

# License

This project includes or depends on these following projects:

| Project                                            | License                 |
|----------------------------------------------------|-------------------------|
| [freetype](https://github.com/freetype/freetype)   | GPL v2                  |
| [glad](https://github.com/Dav1dde/glad)            | MIT License             |
| [glfw](https://github.com/glfw/glfw)               | zlib License            |
| [glm](https://github.com/g-truc/glm)               | The Happy Bunny License |
| [lua](https://github.com/lua/lua)                  | MIT License             |
| [openal-soft](https://github.com/kcat/openal-soft) | GPL v2                  |
| [stb](https://github.com/nothings/stb)             | MIT License             |
| [fmt](https://github.com/fmtlib/fmt)               | [fmt License](https://github.com/fmtlib/fmt/blob/master/LICENSE.rst)
| [imgui](https://github.com/ocornut/imgui)          | MIT License             |
| [spdlog](https://github.com/gabime/spdlog)         | MIT License             |

The links of the above projects point to the original repository of the project, but the source used inside this project is a fork made by me that contains a premake5 file to help building projects. The used source can be found at `UnnamedEngine/vendor/`.