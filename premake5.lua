
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
        "app/**.h",
        "app/**.hpp",
        "app/**.cpp",

        "cpu/**.h",
        "cpu/**.hpp",
        "cpu/**.cpp",

        "io/**.h",
        "io/**.hpp",
        "io/**.cpp",

        "utils/**.h",
        "utils/**.hpp",
        "utils/**.cpp",

        "*.cpp",
        "*.hpp",
        "*.h"
    }

    includedirs {
        Deps.GLFW.IncludeDir,
        Deps.ImGui.Root,
        Deps.ImGui.Backends,
        "cpu",
        "io",
        "utils",
        "app"
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