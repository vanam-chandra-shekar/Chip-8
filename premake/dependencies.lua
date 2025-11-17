Deps = {}

-- Root of the project (where premake5.lua is)
Deps.Root = _MAIN_SCRIPT_DIR

-- Vendor directory
Deps.Vendor = path.join(Deps.Root, "vendor")

-- GLFW
Deps.GLFW = {}
Deps.GLFW.Root = path.join(Deps.Vendor, "glfw")
Deps.GLFW.IncludeDir = path.join(Deps.GLFW.Root, "include")
Deps.GLFW.SrcDir = path.join(Deps.GLFW.Root, "src")

-- ImGui
Deps.ImGui = {}
Deps.ImGui.Root = path.join(Deps.Vendor, "imgui")
Deps.ImGui.Backends = path.join(Deps.ImGui.Root, "backends")

-- Output folders
Deps.BinDir    = path.join(Deps.Root, "bin")
Deps.ObjDir    = path.join(Deps.Root, "bin-int")
