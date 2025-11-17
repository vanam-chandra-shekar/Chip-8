
workspace "C8"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "Main"

-- Load dependency paths
include "premake/dependencies.lua"

-- Load modules
include "premake/glfw.lua"
include "premake/imgui.lua"

project "Main"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}")
    objdir    (path.join(Deps.ObjDir, "%{cfg.buildcfg}", "%{prj.name}"))


    files {
        "src/**.h",
        "src/**.cpp",
        "*.cpp",
        "*.hpp",
        "*.h"
    }

    includedirs {
        "src",
        Deps.GLFW.IncludeDir,
        Deps.ImGui.Root,
        Deps.ImGui.Backends
    }

    links {
        "GLFW",
        "ImGui",
        "opengl32",
        "gdi32"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"