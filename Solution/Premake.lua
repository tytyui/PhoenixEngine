workspace "PhoenixEngine"
	configurations { "Debug", "Release" }
	includedirs { "PhoenixEngine/Source", "Libraries/Include" }
	libdirs { "Libraries/Lib/%{cfg.buildcfg}/GLEW/",
		"Libraries/Lib/%{cfg.buildcfg}/GLFW/",
		"Libraries/Lib/%{cfg.buildcfg}/IrrKlang/",
		"/usr/local/lib",
		"Build/%{cfg.buildcfg}",
		os.findlib("glfw3"),
		os.findlib("glew")
	}
	
project "PhoenixEngine"
	kind "StaticLib"
	language "C++"
	location "PhoenixEngine"
	targetdir "Build/%{cfg.buildcfg}"

	links { "glew", "glfw3", "IrrKlang", "ikpMP3", "ikpFLAC" }
	
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
		links { "glfw3", "glew" } 
