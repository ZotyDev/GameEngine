-- Required utilities
require "Scripts/Premake/PremakeTriggers"

-- Include Directories
IncludeDir = {}
	IncludeDir["GLFW"] = "%{wks.location}/UnnamedEngine/vendor/GLFW/include"
	IncludeDir["GLAD"] = "%{wks.location}/UnnamedEngine/vendor/GLAD/include"
	IncludeDir["GLM"] = "%{wks.location}/UnnamedEngine/vendor/GLM"
	IncludeDir["STB"] = "%{wks.location}/UnnamedEngine/vendor/STB"
	IncludeDir["LUA"] = "%{wks.location}/UnnamedEngine/vendor/LUA"
	IncludeDir["FreeType"] = "%{wks.location}/UnnamedEngine/vendor/FreeType/include"
	IncludeDir["ImGui"] = "%{wks.location}/UnnamedEngine/vendor/ImGui"
	IncludeDir["Vulkan"] = "C:/VulkanSDK/1.2.189.2/Include"
	IncludeDir["OpenAL"] = "%{wks.location}/UnnamedEngine/vendor/OpenAL-Soft/include"
	IncludeDir["Emscripten"] = "C:/emsdk/upstream/emscripten/system/include"
	IncludeDir["fmt"] = "%{wks.location}/UnnamedEngine/vendor/fmt/include"
	
	IncludeDir["ImPlot"] = "%{wks.location}/UnnamedEngine/vendor/ImPlot"
	IncludeDir["ImGuizmo"] = "%{wks.location}/UnnamedEngine/vendor/ImGuizmo"

-- Library Directories
LibDir = {}
	LibDir["OpenAL"] = "%{wks.location}/UnnamedEngine/vendor/OpenAL-Soft/libs/Win64"
	LibDir["Vulkan"] = "C:/VulkanSDK/1.2.189.2/Lib"
	LibDir["Emscripten"] = "C:/emsdk/upstream/emscripten/system/lib"

workspace "GameEngine"
	startproject "UnnamedEditor"
	
	filter {"options:arch=x64"}
		architecture "x64"
	filter {"options:arch=ARM"}
		architecture "ARM"
	filter {}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	configurations
	{
		"Debug",
		"Release",
		"Distribuition"
	}

	group "Dependencies"
		include "UnnamedEngine/vendor/GLAD"
		include "UnnamedEngine/vendor/LUA"
		include "UnnamedEngine/vendor/FreeType"
		include "UnnamedEngine/vendor/GLFW"
		include "UnnamedEngine/vendor/imgui"
	group ""

	include "UnnamedEngine"
	include "UnnamedEditor"
	include "VoxelGame"