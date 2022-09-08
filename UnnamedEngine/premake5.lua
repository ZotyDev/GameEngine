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
		"src/**.cpp",
        "vendor/ImGuizmo/ImGuizmo.cpp",
        "vendor/ImGuizmo/ImGuizmo.h",
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
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImPlot}",
		"%{IncludeDir.fmt}"
	}

	links
	{
		"LUA"
	}

	filter "files:vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

	------------------------------------------------------------------------------------
	-- Windows configuration
	------------------------------------------------------------------------------------
	filter {"system:windows"}
		systemversion "latest"

		pchheader "uepch.h"
		pchsource "src/uepch.cpp"

		files
		{
			"platform/Windows/**.h",
			"platform/Windows/**.cpp",
			"platform/FreeType/**.h",
			"platform/FreeType/**.cpp",
		}

		includedirs
		{
			"vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.STB}",
			"%{IncludeDir.FreeType}"
		}

		links
		{
			"GLFW",
			"FreeType",
			"ImGui",
			"ImPlot"
		}

	------------------------------------------------------------------------------------
	-- Web configuration
	------------------------------------------------------------------------------------
	filter {"system:linux"}
	
	------------------------------------------------------------------------------------
	-- OpenGL configuration
	------------------------------------------------------------------------------------
	filter {"options:gfxapi=opengl"}
		defines 
		{
			"UE_PLATFORM_OPENGL",
		}

		files
		{
			"platform/OpenGL/**.h",
			"platform/OpenGL/**.cpp",
		}

		includedirs
		{
			"%{IncludeDir.GLAD}",
		}

		links
		{
			"GLAD",
			"opengl32.lib",
		}

	------------------------------------------------------------------------------------
	-- DirectX11 configuration
	------------------------------------------------------------------------------------
	filter {"options:gfxapi=dx11"}
		defines
		{
			"UE_PLATFORM_DIRECTX11",
		}

	------------------------------------------------------------------------------------
	-- DirectX12 configuration
	------------------------------------------------------------------------------------
	filter {"options:gfxapi=dx12"}
		defines
		{
			"UE_PLATFORM_DIRECTX12",
		}

	------------------------------------------------------------------------------------
	-- Metal configuration
	------------------------------------------------------------------------------------
	filter {"options:gfxapi=metal"}
		defines
		{
			"UE_PLATFORM_METAL",
		}

	------------------------------------------------------------------------------------
	-- Vulkan configuration
	------------------------------------------------------------------------------------
	filter {"options:gfxapi=vulkan"}
		defines
		{
			"UE_PLATFORM_VULKAN",
		}

		files
		{
			"platform/Vulkan/**.h",
			"platform/Vulkan/**.cpp",
		}

		includedirs
		{
			"%{IncludeDir.VulkanSDK}",
		}

		links
		{
			"%{Library.Vulkan}"
		}

	------------------------------------------------------------------------------------
	-- OpengGL-ES configuration
	------------------------------------------------------------------------------------
	filter {"options:gfxapi=opengles"}
		defines
		{
			"UE_PLATFORM_OPENGLES"
		}

	------------------------------------------------------------------------------------
	-- OpenAL-Soft configuration
	------------------------------------------------------------------------------------
	filter {"options:sndapi=openal"}
		defines
		{
			"UE_PLATFORM_OPENAL"
		}

		files 
		{
			"platform/OpenAL/**.h",
			"platform/OpenAL/**.cpp",
		}

		libdirs
		{
			"%{LibraryDir.OpenAL}",
		}

		includedirs
		{
			"%{IncludeDir.OpenAL}",
		}

		links
		{
			"OpenAL32.lib",
		}

	------------------------------------------------------------------------------------
	-- Winsock configuration
	------------------------------------------------------------------------------------
	filter {"options:netapi=winsock"}
		defines
		{
			"UE_PLATFORM_WINSOCK"
		}

		files
		{
			"platform/Winsock/**.h",
			"platform/Winsock/**.cpp",
		}

	------------------------------------------------------------------------------------
	-- Debug-Only configuration
	------------------------------------------------------------------------------------
	filter "configurations:Debug"
		defines "UE_DEBUG"
		
		runtime "Debug"
		optimize "Off"
		symbols "On"

		links
		{
			"%{Library.ShaderC_Debug}",
			"%{Library.SPIRV_Cross_Debug}",
			"%{Library.SPIRV_Cross_GLSL_Debug}"
		}
		
	------------------------------------------------------------------------------------
	-- Release-Only configuration
	------------------------------------------------------------------------------------
	filter "configurations:Release"
		defines "UE_RELEASE"

		runtime "Release"
		optimize "Speed"
		symbols "Off"

		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}

	------------------------------------------------------------------------------------
	-- Distribuition-Only configuration
	------------------------------------------------------------------------------------
	filter "configurations:Distribuition"
		defines "UE_DISTRIBUITION"
		
		runtime "Release"
		optimize "Full"
		symbols "Off"

		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}

	filter {}