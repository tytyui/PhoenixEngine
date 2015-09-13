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
	MainWindow = new FWin32Window(800, 600, "PhoenixEngine");

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
