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

include "Fusion"
include "Sandbox"