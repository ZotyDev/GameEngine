workspace "GameEngine"
	architecture "x64"
	startproject "VoxelGame"

	configurations
	{
		"Debug",
		"Release",
		"Distribuition"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/UnnamedEngine/vendor/GLFW/include"
IncludeDir["GLAD"] = "%{wks.location}/UnnamedEngine/vendor/GLAD/include"
IncludeDir["GLM"] = "%{wks.location}/UnnamedEngine/vendor/GLM"
IncludeDir["STB"] = "%{wks.location}/UnnamedEngine/vendor/STB"
IncludeDir["LUA"] = "%{wks.location}/UnnamedEngine/vendor/LUA"

group "Dependencies"
	include "UnnamedEngine/vendor/GLFW"
	include "UnnamedEngine/vendor/GLAD"
	include "UnnamedEngine/vendor/LUA"
group ""

include "UnnamedEngine"
include "VoxelGame"