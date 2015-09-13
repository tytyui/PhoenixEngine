#include "Core/Engine.h"

#include "ExternalLib/LibIncludes.h"
#include "Utility/Debug/Debug.h"
#include "Utility/FileIO/Endian.h"
#include "Utility/Misc/Allocator.h"
#include "Utility/Misc/Primitives.h"
#include "Utility/Misc/Timer.h"
#include "Utility/Threading/Thread.h"
#include "Math/Math.h"

using namespace Phoenix;

FEngine::FEngine()
{
}

void FEngine::Init(const FGameThread::FUpdateCallback& OnUpdateCallback)
{
	F_LogOpen("Log.txt");
	F_LogTrace("Engine::Init()\n");

	FEndian::Init();

	// This will change, calm your horses
	MainWindow = new FWin32Window(1024, 768, "PhoenixEngine");

	{
		FGameThread::FInitParams InitParams;

		InitParams.Window = MainWindow;
		InitParams.OutgoingEvents = &IncomingEvents;
		InitParams.IncomingEvents = &OutgoingEvents;
		InitParams.UpdateCallback = OnUpdateCallback;

		GameThread.Init(InitParams);
		F_Assert(GameThread.IsValid(), "Game Thread failed to initialize.");
	}
	
	IsRunning = true;
}

void FEngine::DeInit()
{
	F_LogClose();
}

void FEngine::Run()
{
	F_LogTrace("Engine::Run()\n");

	// #FIXME: This low value is simply for demonstration purposes.
	const Float32 FramesPerSec = 0.25f;
	const Float32 MaxDeltaTime = 1.f / FramesPerSec;

	TThreadSafeVector<UInt32>::ContainerT ReceivedEvents;
	Float32 AccumulatedTime = 0.f;

	FHighResTimer Timer;
	Timer.Reset();

	while (IsRunning)
	{
		Timer.Update();
		const Float32 DeltaSeconds = Timer.GetDeltaSeconds<Float32>();
		AccumulatedTime += DeltaSeconds;

		if (AccumulatedTime >= MaxDeltaTime)
		{
			AccumulatedTime = FMathf::Modulo(AccumulatedTime, MaxDeltaTime);
			
			// #FIXME: Dispatch events here.

			OutgoingEvents.AddEntry(0);
			IncomingEvents.GetDataAndClear(ReceivedEvents);

			for (const auto& ReceivedEvent : ReceivedEvents)
			{
				// #FIXME: Handle received events here.
			}

			ReceivedEvents.clear();
		}

		// #FIXME Probably will be moved. But we need window control for now.
		MainWindow->ProcessEvents();

		// #FIXME: Calculate an appropriate time to 
		// sleep in order to prevent a busy wait.
	}
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
