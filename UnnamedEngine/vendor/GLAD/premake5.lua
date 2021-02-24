project "GLAD"
	location "GLAD"
	kind "StaticLib"
	language "C"

	targetdir "bin/%{cfg.buildcgf}/%{prj.name}"
	objdir "bin-int/%{cfg.buildcgf}/%{prj.name}"

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"