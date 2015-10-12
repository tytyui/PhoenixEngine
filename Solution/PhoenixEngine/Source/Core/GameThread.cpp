#include "Core/GameThread.h"

#include "Utility/Debug/Assert.h"
#include "Utility/Debug/Debug.h"
#include "Utility/Misc/Allocator.h"
#include "Utility/Misc/Timer.h"

using namespace Phoenix;

bool FGameThread::FInitParams::IsValid() const
{
	const bool IsWindowValid = Window != nullptr;
	const bool AreOutgoingEventsValid = OutgoingEvents != nullptr;
	const bool AreIncomingEventsValid = IncomingEvents != nullptr;
	const bool IsUpdateCallbackValid = UpdateCallback != nullptr;

	const bool Result =
		IsWindowValid &&
		AreOutgoingEventsValid &&
		AreIncomingEventsValid &&
		IsUpdateCallbackValid;

	return Result;
}

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

void FGameThread::Init(const FInitParams& InitParams)
{
	F_Assert(InitParams.IsValid(), "Initialization parameters must be valid.");
	F_Assert(!IsRunning, "Game Thread is already running.");
	F_LogTrace("GameThread::Init()");

	InitData = InitParams;
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
	F_LogWarning("Subsystems may not have been shut down properly.");
	IsRunning = false;
}

void FGameThread::ThreadRun()
{
	ThreadInit();
	F_LogTrace("GameThread::ThreadRun()");

	// #FIXME: This low value is simply for demonstration purposes.
	const Float32 FramesPerSec = .125f;
	const Float32 MaxDeltaTime = 1.f / FramesPerSec;

	TThreadSafeVector<UInt32>::ContainerT ReceivedEvents;
	Float32 AccumulatedTime = 0.f;
	UInt32 UpdateCount = 0;

	FHighResTimer Timer;
	Timer.Reset();

	while (IsRunning)
	{
		Timer.Update();
		const Float32 DeltaSeconds = Timer.GetDeltaSeconds<Float32>();

		AccumulatedTime += DeltaSeconds;
		UpdateCount = 0;

		while (AccumulatedTime >= MaxDeltaTime)
		{
			AccumulatedTime -= MaxDeltaTime;
			const Float32 CurrentTime = Timer.GetTimeInSeconds<Float32>() - AccumulatedTime;

			// #FIXME: Receive and process messages from Engine.cpp here.
			InitData.IncomingEvents->GetDataAndClear(ReceivedEvents);

			for (const auto& ReceivedEvent : ReceivedEvents)
			{
				// #FIXME: Handle received events.
			}

			ReceivedEvents.clear();

			// #FIXME: Update
			InitData.UpdateCallback(MaxDeltaTime);

			// #FIXME: Dispatch any messages to Engine.cpp here.
			InitData.OutgoingEvents->AddEntry(1);

			++UpdateCount;
			static const UInt32 MinFramesBeforeWarning = 2;
			if (UpdateCount == MinFramesBeforeWarning)
			{
				F_LogWarning("Two or more updates occurred.  AccT: " << AccumulatedTime);
			}
		}

		RenderEngine.Draw();
	}

	ThreadDeInit();
}

void FGameThread::ThreadInit()
{
	{
		AudioEngine.Init();
		F_Assert(AudioEngine.IsValid(), "Audio Engine failed to initialize.");
	}

	{	// #FIXME: Init Physics

	}

	{
		F_Assert(InitData.Window, "Window is null.");
		RenderEngine.Init(*InitData.Window);
		F_Assert(RenderEngine.IsValid(), "Render Engine failed to initialize.");
	}

	F_LogTrace("GameThread::ThreadInit()\n");
}

void FGameThread::ThreadDeInit()
{
	F_LogTrace("GameThread::ThreadDeInit()");
	InitData = FInitParams();

	{
		RenderEngine.DeInit();
	}

	{	// #FIXME: DeInit Physics

	}

	{
		AudioEngine.DeInit();
	}
}
