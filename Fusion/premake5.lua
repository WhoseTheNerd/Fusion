project "Fusion"
	kind "SharedLib"
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
		"src",
		"%{IncludeDir.SPDLOG}"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"F_BUILD_DLL",
			"F_PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox\"")
		}
	
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