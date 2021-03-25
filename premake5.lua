workspace "Fusion"
	architecture "x86_64"
	startproject "Sandbox"


	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SPDLOG"] = "%{wks.location}/Fusion/vendor/spdlog/include"

include "Fusion"
include "Sandbox"