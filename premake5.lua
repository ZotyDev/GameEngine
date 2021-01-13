workspace "GameEngine"
	architecture "x64"
	startproject "VoxelGame"

	configurations
	{
		"Debug",
		"Release",
		"Distribuition"
	}

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
		"UnnamedEngine/src"
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
		"UnnamedEngine/src"
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