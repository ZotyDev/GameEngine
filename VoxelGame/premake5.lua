project "VoxelGame"
	kind "ConsoleAPP"
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

	includedirs
	{
		"%{wks.location}/UnnamedEngine/vendor/spdlog/include",
		"%{wks.location}/UnnamedEngine/src",
		"%{wks.location}/UnnamedEngine/vendor",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.LUA}"
	}

	links
	{
		"UnnamedEngine"
	}

	filter "system:windows"
		systemversion "latest"

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