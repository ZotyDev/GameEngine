<p align="center">
    <img src="Resource/Branding/unnamed_engine.png?raw=true" alt="Unnamed Engine">
</p>

[![Windows](https://github.com/ZotyDev/GameEngine/actions/workflows/Windows.yml/badge.svg?branch=refactor)](https://github.com/ZotyDev/GameEngine/actions/workflows/Windows.yml)
[![Ubuntu](https://github.com/ZotyDev/GameEngine/actions/workflows/Ubuntu.yml/badge.svg)](https://github.com/ZotyDev/GameEngine/actions/workflows/Ubuntu.yml)
[![MacOS](https://github.com/ZotyDev/GameEngine/actions/workflows/MacOS.yml/badge.svg)](https://github.com/ZotyDev/GameEngine/actions/workflows/MacOS.yml)
[![Emscripten](https://github.com/ZotyDev/GameEngine/actions/workflows/Emscripten.yml/badge.svg)](https://github.com/ZotyDev/GameEngine/actions/workflows/Emscripten.yml)

This Game Engine is the base of all ZotyDev games. The main objectives are customization and performance, allowing me to create complex stuff without restrictions. (Learning is the second main goal)

## Supported Platforms
- [x] Windows 10/11
- [x] Linux
- [x] MacOS
- [x] Web
- [ ] Android
- [ ] IOS

## Current Features
- [x] Async Logger
- [x] Event System
- [ ] Config System
- [ ] Object Parsing
- [ ] Network System
- [ ] Entity Component System
- [ ] Hot-Reloading Scripting
- [ ] Graphics Renderer
  - [ ] OpenGL
  - [ ] Vulkan
  - [ ] DirectX
- [ ] Audio Renderer
  - [ ] OpenAL-Soft

# Compiling

Go to `./Scripts/` and select the target platform.

- Config`<Configuration>` will create the build files
- Build`<Configuration>` will build the project

Available configurations are:

- Debug

# License

This project includes or depends on the following projects:

| Project                                            | License                 |
|----------------------------------------------------|-------------------------|
| [spdlog](https://github.com/gabime/spdlog)         | [MIT License](https://github.com/gabime/spdlog/blob/v1.x/LICENSE)             |
| [yaml-cpp](https://github.com/jbeder/yaml-cpp)     | [MIT License](https://github.com/jbeder/yaml-cpp/blob/master/LICENSE)         |

Currently, UnnamedEngine does not have a license, which means you are better not using the source code until it gets a proper license.

### Thanks

- [The Cherno](https://www.youtube.com/@TheCherno), for his game engine series
