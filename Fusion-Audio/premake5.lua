project "Fusion-Audio"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
	{
		"src/**.h",
        "src/**.hpp",
		"src/**.cpp"
	}

    includedirs
    {
        "src",
        "%{IncludeDir.ogg}",
        "%{IncludeDir.vorbis}",
        "%{IncludeDir.openal}"
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

    libdirs "C:\\Program Files (x86)\\OpenAL 1.1 SDK\\libs\\Win64"

    links
    {
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