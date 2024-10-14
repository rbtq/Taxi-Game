workspace "Engine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

group "Engine"

project "Engine"
	location "engine"
	kind "StaticLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")
	
	pchheader "engine_pch.h"
	pchsource "engine/precompiled/engine_pch.cpp"
	
	files
	{
		"%{prj.name}/enginecode/**.h",
		"%{prj.name}/enginecode/**.cpp",
		"engine/precompiled/engine_pch.h",
		"engine/precompiled/engine_pch.cpp"
	}

	includedirs
	{
		"%{prj.name}/enginecode/",
		"%{prj.name}/enginecode/include/independent",
		"%{prj.name}/enginecode/include/",
		"%{prj.name}/precompiled/",
		"vendor/spdlog/include",
		"vendor/glfw/include",
		"vendor/Glad/include",
		"vendor/glm/",
		"vendor/STBimage",
		"vendor/freetype2/include",
		"vendor/json/single_include/nlohmann",
		"vendor/enTT/single_include/",
		"vendor/luaBridge/Source",
		"vendor/assimp/include",
		"vendor/lua",
		"vendor/react3D/include"
	}
	
	links 
	{
		"GLFW",
		"Glad",
		"Freetype",
		"assimp",
		"ReactPhysics3d"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/include",
		"engine/enginecode/",
		"engine/enginecode/include/independent",
		"engine/enginecode/include/",
		"engine/precompiled/",
		"vendor/glfw/include",
		"vendor/glm/",
		"vendor/spdlog/include",
		"vendor/json/single_include/nlohmann",
		"vendor/enTT/single_include/",
		"vendor/luaBridge/Source",
		"vendor/assimp/include",
		"vendor/lua",
		"vendor/react3D/include",
		"vendor/Glad/include"
	}

	links
	{
		"Engine",
		"Glad"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "On"



project "Spike"
	location "spike"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"engine/enginecode/",
		"engine/enginecode/include/independent",
		"engine/enginecode/include/platform",
		"engine/precompiled/",
		"%{prj.name}/include",
		"vendor/spdlog/include",
		"vendor/STBimage",
		"vendor/freetype2/include",
		"vendor/glm/",
		"vendor/Glad/include",
		"vendor/glfw/include",
		"vendor/json/single_include/nlohmann",
		"vendor/enTT/single_include/",
		"vendor/luaBridge/Source",
		"vendor/assimp/include",
		"vendor/lua",
		"vendor/react3D/include"
	}
	
	links 
	{
		"Engine",
		"Freetype",
		"Glad",
		"GLFW"
	}
	

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

group "Vendor"



	include "vendor/glfw"
	include "vendor/Glad"
	include "vendor/freetype2"
	include "vendor/assimp"
	include "vendor/react3D"

