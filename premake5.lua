workspace "Zote"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- Include directories   
	IncludeDir = {}

	IncludeDir["ZOTE_SRC"] = "Zote/src"
	IncludeDir["ZOTE_ENV"] = "Zote/src/Zote"
	IncludeDir["GLFW"] = "dependencies/glfw/include"
	IncludeDir["GLEW"] = "dependencies/glew/include"
	IncludeDir["GLM"] = "submodules/glm"
	IncludeDir["ENTT"] = "dependencies/entt/include"
	IncludeDir["BOX2D"] = "dependencies/box2d/include"
	IncludeDir["STBIMG"] = "dependencies/stb_image/include"

	-- Library directories
	LibDir = {}

	LibDir["GLFW"] = "dependencies/glfw/lib"
	LibDir["GLEW"] = "dependencies/glew/lib"
	LibDir["BOX2D"] = "dependencies/box2d/lib"

	-- Library files
	LibFile = {}

	LibFile["GLFW"] = "glfw3.lib"
	LibFile["GLEW"] = "glew32.lib"
	LibFile["OPENGL"] = "opengl32.lib"
	LibFile["BOX2D"] = "box2d.lib"

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
			"%{IncludeDir.ZOTE_SRC}",
			"%{IncludeDir.ZOTE_ENV}",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLEW}",
			"%{IncludeDir.GLM}",
			"%{IncludeDir.ENTT}",
			"%{IncludeDir.BOX2D}",
			"%{IncludeDir.STBIMG}"
		}

		libdirs
		{
			"%{LibDir.GLFW}",
			"%{LibDir.GLEW}",
			"%{LibDir.BOX2D}"
		}

		links
		{
			"%{LibFile.GLFW}",
			"%{LibFile.GLEW}",
			"%{LibFile.OPENGL}",
			"%{LibFile.BOX2D}"
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
			"%{prj.name}/src",
			"%{IncludeDir.ZOTE_SRC}",
			"%{IncludeDir.ZOTE_ENV}",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLEW}",
			"%{IncludeDir.GLM}",
			"%{IncludeDir.ENTT}",
			"%{IncludeDir.BOX2D}",
			"%{IncludeDir.STBIMG}"
		}

		libdirs
		{
			"%{LibDir.GLFW}",
			"%{LibDir.GLEW}",
			"%{LibDir.BOX2D}"
		}

		links
		{
			"Zote",
			"%{LibFile.GLFW}",
			"%{LibFile.GLEW}",
			"%{LibFile.OPENGL}",
			"%{LibFile.BOX2D}"
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