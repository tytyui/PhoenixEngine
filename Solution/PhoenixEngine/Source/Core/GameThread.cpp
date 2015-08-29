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
}

void FGameThread::Init(const FUpdateCallback& OnUpdateCallback)
{
	F_Assert(OnUpdateCallback, "UpdateCallback must not be null.");
	F_Assert(!IsRunning, "Game Thread is already running.");
	F_LogTrace("GameThread::Init()");

	UpdateCallback = OnUpdateCallback;
	IsRunning = true;

	Thread = FThread(&FGameThread::ThreadRun, this);
	Thread.detach();
}

bool FGameThread::IsValid() const
{
	const bool LocalIsRunning = IsRunning.load();
	return LocalIsRunning;
}

void FGameThread::ThreadRun()
{
	ThreadInit();
	F_LogTrace("GameThread::ThreadRun()");

	FHighResTimer Timer;
	Timer.Reset();

	while (true)
	{
		Timer.Update();
		const Float32 DeltaSeconds = Timer.GetDeltaSeconds<Float32>();

		F_LogTrace("GameThread::ThreadRun() - Tick.  Do Lots Of Stuff.");

		UpdateCallback(0);
		FThr::SleepThread(10000);
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
	IsRunning = false;
}

// Main Thread
//while (true)
//{
	// Poll events
	// Dispatch events to game thread

	// If game thread sent events to main thread
		// Retrieve events
		// Process events
//}

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