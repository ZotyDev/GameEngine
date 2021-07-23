project "UnnamedEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "uepch.h"
	pchsource "src/uepch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.LUA}",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.Nochyis}"
	}
	
	libdirs
	{
		"%{LibDir.Vulkan}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"LUA",
		"AudioEngine",
		"opengl32.lib",
		"vulkan-1.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "UE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "UE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribuition"
		defines "UE_DISTRIBUITION"
		runtime "Release"
		optimize "on"