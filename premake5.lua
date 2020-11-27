-- ========================
-- Workspace
-- ========================

workspace "ClanTagRank"
	location "./build"
	objdir "%{wks.location}/obj/%{cfg.buildcfg}"
	targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
	targetname "%{prj.name}"

	language "C++"

	architecture "x86"

	buildoptions "/std:c++latest"
	systemversion "latest"

	flags
	{
		"NoIncrementalLink",
		"MultiProcessorCompile",
	}

	configurations { "debug", "release", }

	symbols "On"
	
	configuration "release"
		optimize "Full"
		defines { "NDEBUG" }
	configuration{}

	configuration "debug"
		optimize "Debug"
		defines { "DEBUG", "_DEBUG" }
	configuration {}

	startproject "ClanTagRank"

-- ========================
-- Projects
-- ========================

    project "ClanTagRank"
        kind "SharedLib"
        language "C++"

        pchheader "stdinc.hpp"
		pchsource "src/stdinc.cpp"

        includedirs
        {
       		"src"
    	}
        
        files
        {
            "src/**.h",
            "src/**.hpp",
            "src/**.cpp"
        }
