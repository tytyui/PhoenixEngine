#include "Core/Engine.h"

#include "ExternalLib/LibIncludes.h"
#include "Utility/Debug/Debug.h"
#include "Utility/FileIO/Endian.h"
#include "Utility/Misc/Primitives.h"
#include "Utility/Misc/Timer.h"
#include "Utility/Threading/Thread.h"
#include "Math/Math.h"
#include "Platform/Windowing/GenericWindow.h"

using namespace Phoenix;


void FEngine::Run(FGameThread::FCreateGameSceneFunc CreateGameSceneFunc)
{
	Init(CreateGameSceneFunc);

	F_Assert(IsValid(), "Engine failed to initialize.");

	const Float32 FramesPerSec = 120.f;
	const Float32 MaxDeltaTime = 1.f / FramesPerSec;

	TThreadSafeVector<UInt32>::ContainerT ReceivedEvents;
	Float32 AccumulatedTime = 0.f;

	FHighResolutionTimer Timer;
	Timer.Reset();

	while (IsRunning)
	{
		Timer.Update();
		const Float32 DeltaTimeSec = Timer.GetDeltaSeconds<Float32>();
		AccumulatedTime += DeltaTimeSec;

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

void FEngine::Init(FGameThread::FCreateGameSceneFunc CreateGameSceneFunc)
{
	F_LogOpen("Log.txt");
	F_Assert(CreateGameSceneFunc, "CreateGameSceneFunc is null.");

	FEndian::Init();

	MainWindow = std::make_shared<FGenericWindow>(800, 600, "PhoenixEngine");

	{
		FGameThread::FInitParams InitParams;

		InitParams.Window = MainWindow;
		InitParams.OutgoingEvents = &IncomingEvents;
		InitParams.IncomingEvents = &OutgoingEvents;
		InitParams.CreateGameSceneFunc = CreateGameSceneFunc;

		GameThread.Init(InitParams);
		F_Assert(GameThread.IsValid(), "Game Thread failed to initialize.");
	}

	IsRunning = true;
	F_Assert(IsValid(), "Initialization was successful but this class is not valid.");
}

bool FEngine::IsValid() const
{
	return IsRunning;
}

void FEngine::DeInit()
{
	GameThread.ForceShutDown();
	IsRunning = false;
	F_LogClose();
}