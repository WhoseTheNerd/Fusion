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
		"%{IncludeDir.stb_image}"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"GLFW_DLL"
	}

	links
	{
		"GLFW",
		"Glad"
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