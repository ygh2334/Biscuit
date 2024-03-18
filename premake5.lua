workspace "GameEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder(solutuion directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Biscuit/vendor/GLFW/include"
IncludeDir["Glad"] = "Biscuit/vendor/Glad/include"
IncludeDir["ImGui"] = "Biscuit/vendor/imgui"

include "Biscuit/vendor/GLFW"
include "Biscuit/vendor/Glad"
include "Biscuit/vendor/ImGui"

project "Biscuit"
	location "Biscuit"
	kind "SharedLib"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"BC_BUILD_DLL",
			"BC_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "BC_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "BC_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "BC_DIST"
			buildoptions "/MD"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"BC_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "BC_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "BC_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "BC_DIST"
			buildoptions "/MD"
			optimize "On"