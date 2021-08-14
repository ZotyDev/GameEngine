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
		"%{IncludeDir.OpenAL}",
		"%{IncludeDir.FreeType}"
	}
	
	libdirs
	{
		"%{LibDir.Vulkan}",
		"%{LibDir.OpenAL}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"LUA",
		"opengl32.lib",
		"vulkan-1.lib",
		"OpenAL32.lib",
		"FreeType"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "UE_DEBUG"
		runtime "Debug"
		symbols "on"
		
		--postbuildcommands
		--{
		--	"{COPY} %{wks.location}/UnnamedEngine/vendor/Nochyis/bin/Debug/AudioEngine/AudioEngine.dll %{wks.location}/VoxelGame/"
		--}

	filter "configurations:Release"
		defines "UE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribuition"
		defines "UE_DISTRIBUITION"
		runtime "Release"
		optimize "on"