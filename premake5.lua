-- Required utilities
require "Scripts/Premake/PremakeTriggers"
require "Dependencies"

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
		include "UnnamedEngine/vendor/ImPlot"
		include "UnnamedEngine/vendor/imgui-node-editor"
		include "UnnamedEngine/vendor/yaml-cpp"
	group ""

	include "UnnamedEngine"
	include "UnnamedEditor"
	include "UnnamedClient"