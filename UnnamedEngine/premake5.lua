project "UnnamedEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"platform",
		"src",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.LUA}",
	}

	links
	{
		"LUA"
	}

	------------------------------------------------------------------------------------
	-- Windows-Only configuration
	------------------------------------------------------------------------------------
	filter "system:windows"
		systemversion "latest"

		pchheader "uepch.h"
		pchsource "src/uepch.cpp"

		defines
		{
			"GLFW_INCLUDE_NONE"
		}

		files
		{
			"platform/Windows/**.h",
			"platform/Windows/**.cpp",
			"platform/Winsock/**.h",
			"platform/Winsock/**.cpp",
			"platform/FreeType/**.h",
			"platform/FreeType/**.cpp",
			"platform/OpenAL/**.h",
			"platform/OpenAL/**.cpp",
			"platform/OpenGL/**.h",
			"platform/OpenGL/**.cpp",
			"platform/Vulkan/**.h",
			"platform/Vulkan/**.cpp"
		}

		libdirs
		{
			"%{LibDir.Vulkan}",
			"%{LibDir.OpenAL}"
		}

		includedirs
		{
			"vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLAD}",
			"%{IncludeDir.STB}",
			"%{IncludeDir.Vulkan}",
			"%{IncludeDir.OpenAL}",
			"%{IncludeDir.FreeType}"
		}

		links
		{
			"GLFW",
			"GLAD",
			"opengl32.lib",
			"vulkan-1.lib",
			"OpenAL32.lib",
			"FreeType"
		}

	------------------------------------------------------------------------------------
	-- Linux-Only configuration
	------------------------------------------------------------------------------------
	filter "system:linux"

	------------------------------------------------------------------------------------
	-- Debug-Only configuration
	------------------------------------------------------------------------------------
	filter "configurations:Debug"
		defines "UE_DEBUG"
		
		runtime "Debug"
		optimize "Off"
		symbols "On"
		
	------------------------------------------------------------------------------------
	-- Release-Only configuration
	------------------------------------------------------------------------------------
	filter "configurations:Release"
		defines "UE_RELEASE"

		runtime "Release"
		optimize "Speed"
		symbols "Off"

	------------------------------------------------------------------------------------
	-- Distribuition-Only configuration
	------------------------------------------------------------------------------------
	filter "configurations:Distribuition"
		defines "UE_DISTRIBUITION"
		
		runtime "Release"
		optimize "Full"
		symbols "Off"