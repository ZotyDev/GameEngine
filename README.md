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

## To do:
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

## Compiling:
Go to `Scripts/` and select the target platform.

## Compiling Notes:
### Web:
The folder `YourGame/assets/` is where all data that is going to be used should be. At compilation, this folder will be compiled into a `.data` file that is basically a virtual folder.