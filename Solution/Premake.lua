workspace "PhoenixEngine"
	configurations { "Debug", "Release" }
	platforms{ "x32", "x64" }
	
	includedirs { "PhoenixEngine/Source", "Libraries/Include" }
	libdirs { "Libraries/Lib/%{cfg.buildcfg}.%{cfg.platform}/**" }
	
	links { "glfw3", "irrklang" }
	
	configuration "vs2015"
		links { "glew32s", "opengl32" }
	
	configuration "gmake"
		links { "glew", "opengl" }
	
	configuration "xcode4"
		links { "glew", "OpenGL.framework"}
		buildoptions { "-F ./Libraries/Lib/%{cfg.buildcfg}.%{cfg.platform}/IrrKlang -L ./Libraries/Lib/%{cfg.buildcfg}.%{cfg.platform}/IrrKlang" }
		linkoptions { "-F ./Libraries/Lib/%{cfg.buildcfg}.%{cfg.platform}/IrrKlang -L ./Libraries/Lib/%{cfg.buildcfg}.%{cfg.platform}/IrrKlang"  }
	
	configuration { "x32" }
		debugdir "Libraries/Dll/x32/"
	
	configuration { "x64" }
		debugdir "Libraries/Dll/x64/"

project "PhoenixEngine"
	kind "StaticLib"
	language "C++"
	location "PhoenixEngine"
	targetdir "Build/%{cfg.buildcfg}"
	
	files { "PhoenixEngine/Source/**.h", "PhoenixEngine/Source/**.cpp", "PhoenixEngine/Source/**.txt" }
	
	vpaths { ["Sources/*"] = { "PhoenixEngine/Source/**.h", "PhoenixEngine/Source/**.cpp", "PhoenixEngine/Source/**.txt" } }

	filter "configurations:Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

	configuration "gmake"
		linkoptions  { "-std=c++1y" }
		buildoptions { "-std=c++1y" }

	configuration "xcode4"
		linkoptions  { "-std=c++1y", "-stdlib=libc++" }
		buildoptions { "-std=c++1y", "-stdlib=libc++" }	

project "TestGame"
	kind "ConsoleApp"
	language "C++"
	location "TestGame"
	targetdir "Build/%{cfg.buildcfg}"
	links { "PhoenixEngine" }

	files { "TestGame/**.h", "TestGame/**.cpp", "TestGame/**.txt" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

	configuration "gmake"
		linkoptions  { "-std=c++1y" }
		buildoptions { "-std=c++1y" }

	configuration "xcode4"
		linkoptions  { "-std=c++1y", "-stdlib=libc++" }
		buildoptions { "-std=c++1y", "-stdlib=libc++" }
