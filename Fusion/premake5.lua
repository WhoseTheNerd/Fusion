project "Fusion"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fpch.h"
	pchsource "src/fpch.cpp"

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp"
	}

	includedirs
	{
		"src",
		"%{IncludeDir.SPDLOG}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.ogg}",
		"%{IncludeDir.vorbis}",
		"%{IncludeDir.openal}"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	libdirs "C:\\Program Files (x86)\\OpenAL 1.1 SDK\\libs\\Win64"

	links
	{
		"glfw3",
		"glad",
		"ogg",
		"vorbis",
		"OpenAL32.lib"
	}

	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines "F_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "F_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "F_DIST"
		optimize "on"