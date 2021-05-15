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
IncludeDir["stb_image"] = "%{wks.location}/Fusion/vendor/stb_image"
IncludeDir["ogg"] = "%{wks.location}/Fusion-Audio/vendor/ogg/include"
IncludeDir["vorbis"] = "%{wks.location}/Fusion-Audio/vendor/vorbis/include"
IncludeDir["openal"] = "C:\\Program Files (x86)\\OpenAL 1.1 SDK\\include"

group "Dependencies"
	include "Fusion/vendor/glfw"
	include "Fusion/vendor/glad"
	include "Fusion-Audio/vendor/ogg"
	include "Fusion-Audio/vendor/vorbis"
group ""

include "Fusion"
include "Fusion-Audio"
include "Sandbox"