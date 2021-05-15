project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Fusion/src",
		"%{wks.location}/Fusion-Audio/src",
		"%{IncludeDir.SPDLOG}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.GLM}"
	}

	links
	{
		"Fusion",
		"Fusion-Audio"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		systemversion "latest"
		disablewarnings "4251"
	
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