workspace "PhoenixEngine"
	configurations { "Debug", "Release" }
	platforms{ "x32", "x64" }
	
	includedirs { "PhoenixEngine/Source", "Libraries/Include", "Libraries/Include/FBX/" }
	libdirs {
		"Libraries/Lib/%{cfg.buildcfg}.%{cfg.platform}/**",
		"/usr/local/lib",		
		os.findlib("glfw3"),		
		os.findlib("glew")
	}
	
	links { "glfw3", "irrklang" }
	
	configuration "vs2015"
		links { "glew32s", "opengl32", "libfbxsdk-md", "assimp", "soil" }
	
	configuration "gmake"
		links { "glew", "opengl" }
	
	configuration "xcode4"
		links { "glew", "OpenGL.framework"}
		buildoptions { "-F ./Libraries/Lib/%{cfg.buildcfg}.%{cfg.platform}/IrrKlang -L ./Libraries/Lib/%{cfg.buildcfg}.%{cfg.platform}/IrrKlang" }
		linkoptions { "-F ./Libraries/Lib/%{cfg.buildcfg}.%{cfg.platform}/IrrKlang -L ./Libraries/Lib/%{cfg.buildcfg}.%{cfg.platform}/IrrKlang"  }
	
	filter "configurations:x64"
		debugdir "Libraries/Dll/x64/"

	filter "configurations:x32"
		debugdir "Libraries/Dll/x32/"
	
project "PhoenixEngine"
	kind "StaticLib"
	language "C++"
	location "PhoenixEngine"
	targetdir "Build/%{cfg.buildcfg}"
	
	files { 
		"PhoenixEngine/Source/**.h", 
		"PhoenixEngine/Source/**.hpp",
		"PhoenixEngine/Source/**.cpp", 
		"PhoenixEngine/Source/**.txt"
	}
	
	vpaths { ["Sources/*"] = { 
		"PhoenixEngine/Source/**.h", 
		"PhoenixEngine/Source/**.hpp", 
		"PhoenixEngine/Source/**.cpp", 
		"PhoenixEngine/Source/**.txt" } }

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

project "Game"
	kind "ConsoleApp"
	language "C++"
	location "Game"
	targetdir "Build/%{cfg.buildcfg}"
	links { "PhoenixEngine" }

	files { 
		"Game/**.h", 
		"Game/**.hpp", 
		"Game/**.cpp", 
		"Game/**.txt" 
	}

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
