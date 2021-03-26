include "./vendor/premake/solution_items.lua"

workspace "Fusion"
	architecture "x86_64"
	startproject "Sandbox"


	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SPDLOG"] = "%{wks.location}/Fusion/vendor/spdlog/include"
IncludeDir["GLFW"] = "%{wks.location}/Fusion/vendor/glfw/include"
IncludeDir["Glad"] = "%{wks.location}/Fusion/vendor/glad/include"
IncludeDir["GLM"] = "%{wks.location}/Fusion/vendor/glm"

group "Dependencies"
	include "Fusion/vendor/glfw"
	include "Fusion/vendor/glad"
group ""

include "Fusion"
include "Sandbox"