project "Fusion-Audio"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

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
		"_CRT_SECURE_NO_WARNINGS",
        "F_BUILD_DLL"
	}

    postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} \"%{wks.location}/bin/" .. outputdir .. "/Sandbox/\"")
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