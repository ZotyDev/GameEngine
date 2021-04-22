workspace "GameEngine"
	architecture "x64"
	startproject "VoxelGame"

	configurations
	{
		"Debug",
		"Release",
		"Distribuition"
	}

IncludeDir = {}
IncludeDir["GLFW"] = "UnnamedEngine/vendor/GLFW/include"
IncludeDir["GLAD"] = "UnnamedEngine/vendor/GLAD/include"
IncludeDir["GLM"] = "UnnamedEngine/vendor/GLM"
IncludeDir["Vulkan"] = "C:/VulkanSDK/1.2.170.0/Include"
IncludeDir["STB"] = "UnnamedEngine/vendor/STB"
IncludeDir["LUA"] = "UnnamedEngine/vendor/LUA"

LibraryDir = {}
LibraryDir["Vulkan"] = "C:/VulkanSDK/1.2.170.0/Lib"

include "UnnamedEngine/vendor/GLFW"
include "UnnamedEngine/vendor/GLAD"
include "UnnamedEngine/vendor/LUA"

project "UnnamedEngine"
	location "UnnamedEngine"
	kind "SharedLib"
	language "C++"

	targetdir "bin/%{cfg.buildcgf}/%{prj.name}"
	objdir "bin-int/%{cfg.buildcgf}/%{prj.name}"

	files
	{
		"UnnamedEngine/src/**.h",
		"UnnamedEngine/src/**.cpp"
	}

	includedirs
	{
		"UnnamedEngine/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.LUA}"
	}

	libdirs
	{
		"%{LibraryDir.Vulkan}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"LUA",
		"opengl32.lib",
		"vulkan-1.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"UE_PLATFORM_WINDOWS",
			"UE_BUILD_DLL"
		}

		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} ../bin/%{cfg.buildcgf}/VoxelGame"
		}

	filter "configurations:Debug"
		defines 
		{
			"_DEBUG",
			"UE_DEBUG"
		}
		symbols "On"

	filter "configurations:Release"
		defines "UE_RELEASE"
		optimize "On"

	filter "configurations:Distribuition"
		defines "UE_DISTRIBUITION"
		optimize "On"

project "VoxelGame"
	location "VoxelGame"
	kind "ConsoleApp"
	language "C++"

	targetdir "bin/%{cfg.buildcgf}/%{prj.name}"
	objdir "bin-int/%{cfg.buildcgf}/%{prj.name}"

	files
	{
		"VoxelGame/src/**.h",
		"VoxelGame/src/**.cpp"
	}

	includedirs
	{
		"UnnamedEngine/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.LUA}"
	}

	links
	{
		"UnnamedEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"UE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines 
		{
			"_DEBUG",
			"UE_DEBUG"
		}
		symbols "On"

	filter "configurations:Release"
		defines "UE_RELEASE"
		optimize "On"

	filter "configurations:Distribuition"
		defines "UE_DISTRIBUITION"
		optimize "On"