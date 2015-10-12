#include "Core/Engine.h"

#include "ExternalLib/LibIncludes.h"
#include "Input/Input.h"
#include "Math/Math.h"
#include "Utility/Debug/Debug.h"
#include "Utility/FileIO/Endian.h"
#include "Utility/Misc/Allocator.h"
#include "Utility/Misc/Primitives.h"
#include "Utility/Misc/Timer.h"
#include "Utility/Threading/Thread.h"

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
	
	Input = std::make_unique<FInput>();
	Input->Init(MainWindow);

	IsRunning = true;
}

void FEngine::DeInit()
{
	F_LogClose();
}

void FEngine::Run()
{
	F_LogTrace("Engine::Run()\n");

	const Float32 FramesPerSec = 60.f;
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
			MainWindow->ProcessEvents();
			
			// #FIXME: Dispatch events here.

			//OutgoingEvents.AddEntry(0);
			IncomingEvents.GetDataAndClear(ReceivedEvents);

			for (const auto& ReceivedEvent : ReceivedEvents)
			{
				// #FIXME: Handle received events here.
			}

			ReceivedEvents.clear();
		}
		
		NThread::SleepThread(0);
	}

	DeInit();
}

void FEngine::ShutDown()
{
	//#FIXME Establish proper shutdown protocol
	F_Log("Engine::ShutDown()");
	GameThread.ForceShutDown();
	IsRunning = false;
}

const TUniquePtr<FInput>& FEngine::GetInput() const
{
	return Input;
}
