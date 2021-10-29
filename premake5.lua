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
	IncludeDir["Vulkan"] = "C:/VulkanSDK/1.2.182.0/Include"
	IncludeDir["OpenAL"] = "%{wks.location}/UnnamedEngine/vendor/OpenAL-Soft/include"

-- Library Directories
LibDir = {}
	LibDir["OpenAL"] = "%{wks.location}/UnnamedEngine/vendor/OpenAL-Soft/libs/Win64"
	LibDir["Vulkan"] = "C:/VulkanSDK/1.2.182.0/Lib"

workspace "GameEngine"
	startproject "VoxelGame"
	
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
	group ""

	include "UnnamedEngine"
	include "VoxelGame"