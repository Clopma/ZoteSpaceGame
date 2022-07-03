workspace "Zote"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}

	IncludeDir["GLFW"] = "dependencies/glfw/include"
	IncludeDir["GLEW"] = "dependencies/glew/include"
	IncludeDir["GLM"] = "submodules/glm"
	IncludeDir["ENTT"] = "dependencies/entt/include"
	IncludeDir["BOX2D"] = "dependencies/box2d/include"
	IncludeDir["STBIMG"] = "dependencies/stb_image/include"

	project "Zote"
		location "Zote"
		kind "SharedLib"
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
			"Zote/src",
			"Zote/src/Zote",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLEW}",
			"%{IncludeDir.GLM}",
			"%{IncludeDir.ENTT}",
			"%{IncludeDir.BOX2D}",
			"%{IncludeDir.STBIMG}"
		}

		libdirs
		{
			"dependencies/glfw/lib",
			"dependencies/glew/lib",
			"dependencies/box2d/lib"
		}

		links
		{
			"box2d.lib",
			"opengl32.lib",
			"glew32.lib",
			"glew32s.lib",
			"glfw3.lib"
		}

		filter "system:windows"
			cppdialect "C++17"
			systemversion "10.0"

			defines 
			{
				"ZOTE_PLATFORM_WINDOWS",
				"ZOTE_BUILD_DLL"
			}

			postbuildcommands
			{
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
			}			

		filter "configurations:Debug"
			defines "ZOTE_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "ZOTE_RELEASE"
			symbols "On"
			optimize "On"

		filter "configurations:Dist"
			defines "ZOTE_DIST"
			symbols "On"
			optimize "On"

	project "Game"
		location "Game"
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
			"Zote/src/Zote",
			"Zote/src",
			"%{prj.name}/src",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLEW}",
			"%{IncludeDir.GLM}",
			"%{IncludeDir.ENTT}",
			"%{IncludeDir.BOX2D}",
			"%{IncludeDir.STBIMG}"
		}

		libdirs
		{
			"dependencies/glfw/lib",
			"dependencies/glew/lib",
			"dependencies/box2d/lib"
		}

		links
		{
			"Zote",
			"box2d.lib",
			"opengl32.lib",
			"glew32.lib",
			"glew32s.lib",
			"glfw3.lib"
		}

		filter "system:windows"
			cppdialect "C++17"
			systemversion "10.0"

			defines 
			{
				"ZOTE_PLATFORM_WINDOWS"
			}

		filter "configurations:Debug"
			defines "ZOTE_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "ZOTE_RELEASE"
			symbols "On"
			optimize "On"

		filter "configurations:Dist"
			defines "ZOTE_DIST"
			symbols "On"
			optimize "On"