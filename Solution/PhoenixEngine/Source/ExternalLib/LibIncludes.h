#ifndef PHOENIX_LIB_INCLUDES_H
#define PHOENIX_LIB_INCLUDES_H

#ifdef _DEBUG
#	pragma comment (lib, "glew32sd.lib")
#else
#	pragma comment (lib, "glew32s.lib")
#endif

#pragma comment (lib, "glfw3.lib")
#pragma comment (lib, "opengl32.lib")

#endif