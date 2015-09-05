#include "Core/GameThread.h"

#include "Utility/Assert.h"
#include "Utility/Debug.h"
#include "Utility/Timer.h"

using namespace Phoenix;

FGameThread::FGameThread()
{
}

FGameThread::~FGameThread()
{
	F_Assert(!IsRunning, "Game Thread should have already been deinitialized.");
	F_Assert(Thread.Get().joinable(), "Game Thread should not have been detached.");

	IsRunning = false;
	Thread.Join();
}

void FGameThread::Init(const FUpdateCallback& OnUpdateCallback)
{
	F_Assert(OnUpdateCallback, "UpdateCallback must not be null.");
	F_Assert(!IsRunning, "Game Thread is already running.");
	F_LogTrace("GameThread::Init()");

	UpdateCallback = OnUpdateCallback;
	IsRunning = true;

	Thread = FThread(&FGameThread::ThreadRun, this);
}

bool FGameThread::IsValid() const
{
	const bool LocalIsRunning = IsRunning.load();
	return LocalIsRunning;
}

void FGameThread::ForceShutDown()
{
	F_LogWarning("Subsystems may not have been shut down properly.")
	IsRunning = false;
}

void FGameThread::ThreadRun()
{
	ThreadInit();
	F_LogTrace("GameThread::ThreadRun()");

	FHighResTimer Timer;
	Timer.Reset();

	const Float32 FPS = 60.f;
	Float32 AccumulatedTime = 0.f;
	Float32 MaxDeltaTimePerFrame = 1.f / FPS;
	UInt32 UpdateCount = 0;

	while (IsRunning)
	{
		Timer.Update();
		const Float32 DeltaSeconds = Timer.GetDeltaSeconds<Float32>();

		AccumulatedTime += DeltaSeconds;
		UpdateCount = 0;

		while (AccumulatedTime >= MaxDeltaTimePerFrame)
		{
			AccumulatedTime -= MaxDeltaTimePerFrame;
			const Float32 CurrentTime = Timer.GetDeltaSeconds<Float32>() - AccumulatedTime;

			// FIXME: Receive and process messages from Engine.cpp here.

			// #FIXME: Update

			// #FIXME: Dispatch any messages to Engine.cpp here.

			++UpdateCount;
			static const UInt32 MinFramesBeforeWarning = 2;
			if (UpdateCount == MinFramesBeforeWarning)
			{
				F_LogWarning("Two or more updates occurred.  AccT: " << AccumulatedTime);
			}
		}

		// #FIXME: Render

		// #FIXME: Remove this when everyone has seen the game loop.
		F_LogTrace("GameThread::ThreadRun() - Tick.  Do Lots Of Stuff.");
		UpdateCallback(0);
		FThr::SleepThread(10000);
		// END #FIXME		
	}

	ThreadDeInit();
}

void FGameThread::ThreadInit()
{
	F_LogTrace("GameThread::ThreadInit()\n");
}

void FGameThread::ThreadDeInit()
{
	F_LogTrace("GameThread::ThreadDeInit()");
	UpdateCallback = nullptr;
}

// #FIXME: Remove this when it is no longer needed.
// Main Thread
//while (true)
//{
	// Poll events
	// Dispatch events to game thread

	// If game thread sent events to main thread
		// Retrieve events
		// Process events
//}


// #FIXME: Remove this when it is no longer needed.
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