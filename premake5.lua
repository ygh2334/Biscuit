workspace "GameEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
--设置启动项目
startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder(solutuion directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Biscuit/vendor/GLFW/include"
IncludeDir["Glad"] = "Biscuit/vendor/Glad/include"
IncludeDir["ImGui"] = "Biscuit/vendor/imgui"
IncludeDir["glm"] = "Biscuit/vendor/glm"

--把依赖放到一个组里面
group "Dependencies"
		include "Biscuit/vendor/GLFW"
		include "Biscuit/vendor/Glad"
		include "Biscuit/vendor/ImGui"
group ""

project "Biscuit"
	location "Biscuit"
	kind "StaticLib"
	language "C++"
	staticruntime "on"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bcpch.h"
	pchsource "Biscuit/src/bcpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/vendor/glm/glm/**.hpp"
	}

	defines 
	{		
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BC_BUILD_DLL",
			"BC_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

		filter "configurations:Debug"
			defines "BC_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "BC_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "BC_DIST"
			runtime "Release"
			optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	cppdialect "C++17"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Biscuit/vendor/spdlog/include",
		"Biscuit/src",
		"Biscuit/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Biscuit"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BC_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "BC_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "BC_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "BC_DIST"
			runtime "Release"
			optimize "on"