include "premake/dependencies.lua"

project "GLFW"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir (path.join(Deps.BinDir, "%{cfg.buildcfg}"))
    objdir    (path.join(Deps.ObjDir, "%{cfg.buildcfg}", "%{prj.name}"))

    files {
        path.join(Deps.GLFW.SrcDir, "*.c")
    }

    includedirs {
        Deps.GLFW.IncludeDir
    }

    filter "system:windows"
        systemversion "latest"
        defines {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
