include "premake/dependencies.lua"

project "ImGui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir (path.join(Deps.BinDir, "%{cfg.buildcfg}"))
    objdir    (path.join(Deps.ObjDir, "%{cfg.buildcfg}", "%{prj.name}"))

    files {
        path.join(Deps.ImGui.Root, "*.cpp"),
        path.join(Deps.ImGui.Backends, "imgui_impl_glfw.cpp"),
        path.join(Deps.ImGui.Backends, "imgui_impl_opengl3.cpp")
    }

    includedirs {
        Deps.ImGui.Root,
        Deps.ImGui.Backends,
        Deps.GLFW.IncludeDir
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
