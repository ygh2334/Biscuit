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

--把依赖放到一个组里面
group "Dependencies"
		include "Biscuit/vendor/GLFW"
		include "Biscuit/vendor/Glad"
		include "Biscuit/vendor/ImGui"
group ""

project "Biscuit"
	location "Biscuit"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bcpch.h"
	pchsource "Biscuit/src/bcpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
		
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"dwmapi.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"BC_BUILD_DLL",
			"BC_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

		filter "configurations:Debug"
			defines "BC_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "BC_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "BC_DIST"
			runtime "Release"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"Biscuit/src"
	}

	links
	{
		"Biscuit"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"BC_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "BC_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "BC_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "BC_DIST"
			runtime "Release"
			optimize "On"