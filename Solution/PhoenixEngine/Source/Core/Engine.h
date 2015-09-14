#ifndef PHOENIX_ENGINE_H
#define PHOENIX_ENGINE_H

#include "Utility/Threading/ThreadSafeVector.h"
#include "Utility/Misc/Memory.h"
#include "Core/GameThread.h"
#include "Platform/Windowing/Win32Window.h"

namespace Phoenix
{
	class FInput;

	class FEngine
	{
	public:
		FEngine();

		FEngine(const FEngine&) = delete;
		FEngine& operator=(const FEngine&) = delete;

		FEngine(FEngine&&) = delete;
		FEngine& operator=(FEngine&&) = delete;
		
		~FEngine() = default;

		void Init(const FGameThread::FUpdateCallback& UpdateCallback);
		void DeInit();

		const TUniquePtr<FInput>& GetInput() const;

		void Run();
		void ShutDown();

	private:
		
		//Engine SubSystems
		FWin32Window* MainWindow{ nullptr };
		FGameThread GameThread;

		//#FIXME Determine which thread this should be on
		TUniquePtr<FInput> Input;

		// #FIXME: Change UInt32 to the Event structure.
		TThreadSafeVector<UInt32> OutgoingEvents;
		TThreadSafeVector<UInt32> IncomingEvents;
		

		bool IsRunning{ false };
	};
}

#endif
