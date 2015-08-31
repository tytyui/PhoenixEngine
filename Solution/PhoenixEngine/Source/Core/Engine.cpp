#include "Core/Engine.h"

#include "Utility/Debug.h"
#include "Utility/Endian.h"
#include "Utility/Primitives.h"
#include "Utility/Thread.h"
#include "Utility/Timer.h"

#include <GLFW/glfw3.h>

//TODO: Move somewhere better
#ifdef _DEBUG
	#pragma comment (lib, "glew32sd.lib")
#else
	#pragma comment (lib, "glew32s.lib")
#endif

#pragma comment (lib, "glu32.lib")
#pragma comment (lib, "opengl32.lib")

#pragma comment (lib, "glfw3.lib")

using namespace Phoenix;

FEngine::FEngine()
{
}

void FEngine::Init(const FGameThread::FUpdateCallback& OnUpdateCallback)
{
	F_LogOpen("Log.txt");
	F_LogTrace("Engine::Init()\n");

	FEndian::Init();
	GameThread.Init(OnUpdateCallback);

	F_Assert(GameThread.IsValid(), "Game Thread failed to initialize.");

	// FIXME: For whoever is doing the window stuff.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Test", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	int status = glewInit();
	// END FIXME

	IsRunning = true;
}

void FEngine::DeInit()
{
	F_LogClose();
}

void FEngine::Run()
{
	F_LogTrace("Engine::Run()\n");

	FHighResTimer Timer;
	Timer.Reset();

	while (IsRunning)
	{
		Timer.Update();
		const Float32 DeltaSeconds = Timer.GetDeltaSeconds<Float32>();





		// FIXME: Remove this when everyone has seen the game loop.
		F_LogTrace("Engine::Run() - Tick.  Poll, Dispatch, Receive.\n");
		FThr::SleepThread(5000);
		// END FIXME
	}
}

// FIXME: Remove this when it is no longer needed.
// Main Thread
//while (true)
//{
	// Poll events
	// Dispatch events to game thread

	// If game thread sent events to main thread
		// Retrieve events
		// Process events
//}


// FIXME: Remove this when it is no longer needed.
// Game Thread
/*
	while running
			
		update game timer
		get delta time
		add to accumulated time

		while accumulated time >= max delta time
			reduce accumulated time
			get current time

			if main thread sent events to game thread
				retrieve events
				process events
				
			dispatch events to main thread

			update audio
			update physics
			update c++ scripts

			if multiple updates occured this frame
				display a warning
				potentially reduce target frame rate
			
		draw graphics

	end while loop
*/