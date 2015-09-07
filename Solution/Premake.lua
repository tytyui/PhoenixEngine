workspace "PhoenixEngine"
	configurations { "Debug", "Release" }
	includedirs { "PhoenixEngine/Source", "Libraries/Include" }
	libdirs { "Libraries/Lib/%{cfg.buildcfg}/GLEW/",
		"Libraries/Lib/%{cfg.buildcfg}/GLFW/",
		"Binaries/%{cfg.buildcfg}"
		os.findlib("glfw"),
		os.findlib("glew"),
		os.findlib("glfw3")
	}
	
project "PhoenixEngine"
	kind "StaticLib"
	language "C++"
	location "PhoenixEngine"
	targetdir "Binaries/%{cfg.buildcfg}"
	
	files { "PhoenixEngine/Source/**.h", "PhoenixEngine/Source/**.cpp", "PhoenixEngine/Source/**.txt" }
	
	vpaths { ["Sources/*"] = { "PhoenixEngine/Source/**.h", "PhoenixEngine/Source/**.cpp", "PhoenixEngine/Source/**.txt" } }

	filter "configurations:Debug"
		defines { "DEBUG" }
		flags { "Symbols" }
		
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
	
	links { "glew", "glfw3", "glfw" }
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
	targetdir "Binaries/%{cfg.buildcfg}"
	
	files { "TestGame/**.h", "TestGame/**.cpp", "TestGame/**.txt" }
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		flags { "Symbols" }
		
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
	
	links { "PhoenixEngine" }
	
	configuration "gmake"
            linkoptions  { "-std=c++1y" }
            buildoptions { "-std=c++1y" }
		
	configuration "xcode4"
            linkoptions  { "-std=c++1y", "-stdlib=libc++" }
            buildoptions { "-std=c++1y", "-stdlib=libc++" }
