project "UnnamedEditor"
    kind "ConsoleAPP"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp",
        "res/**"
    }

    includedirs
    {
        "src",
        "%{wks.location}/UnnamedEngine/src",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.LUA}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.ImPlot}",
        "%{IncludeDir.ImGuizmo}"
    }

    links
    {
        "UnnamedEngine"
    }

    ------------------------------------------------------------------------------------
	-- Windows-Only configuration
	------------------------------------------------------------------------------------
	filter "system:windows"
        systemversion "latest"

        includedirs
		{
			"%{wks.location}/UnnamedEngine/vendor/spdlog/include",
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
    filter {}