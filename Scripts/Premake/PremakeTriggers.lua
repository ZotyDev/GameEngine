newoption
{
    trigger = "gfxapi",
    value = "API",
    description = "Select a renderer",
    allowed = 
    {
        {"opengl", "OpenGL 4.6 (Windows)"},
        --{"dx9", "DirectX 9 (Windows only"},
        --{"dx11", "DirectX 11 (Windows only)"},
        --{"dx12", "DirectX 12 (Windows only)"},
        --{"metal", "Metal (macOS, iOS only)"},
        {"vulkan", "Vulkan (Windows, linux, iOS, macOS, android)"},
        --{"opengles", "OpenGL-ES (Web, android only)"}
    }
}

newoption
{
    trigger = "sndapi",
    value = "API",
    description = "Select a sound provider",
    allowed =
    {
        {"openal", "OpenAL-Soft (Windows, linux, macOs)"},
    }
}

newoption
{
    trigger = "netapi",
    value = "API",
    description = "Select a network provider",
    allowed =
    {
        {"winsock", "Winsock (Windows only)"},
    }
}

newoption
{
    trigger = "arch",
    value = "ARC",
    description = "Select a target architecture",
    allowed =
    {
        --{"x86", "x86"},
        {"x64", "x64"},
        --{"arm", "arm"},
        --{"arm64", "arm64"}
    }
}

newaction
{
    trigger = "clean",
    description = "Clean the binaries",
    execute = function()
            print("Clean the binaries...")
            os.rmdir("./bin")
            os.rmdir("./bin-int")
            print("Done.")
    end
}