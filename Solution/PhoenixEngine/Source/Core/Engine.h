#ifndef PHOENIX_ENGINE_H
#define PHOENIX_ENGINE_H

#include "Utility/Misc/Memory.h"
#include "Utility/Threading/ThreadSafeVector.h"
#include "Core/GameThread.h"

namespace Phoenix
{
	class FEngine
	{
	public:
		FEngine() = default;

		FEngine(const FEngine&) = delete;
		FEngine& operator=(const FEngine&) = delete;

		FEngine(FEngine&&) = delete;
		FEngine& operator=(FEngine&&) = delete;
		
		~FEngine() = default;

		void Run(FGameThread::FCreateGameSceneFunc CreateGameSceneFunc);

	private:
		TSharedPtr<class IWindow> MainWindow;
		FGameThread GameThread;

		// #FIXME: Change UInt32 to the Event structure.
		TThreadSafeVector<UInt32> OutgoingEvents;
		TThreadSafeVector<UInt32> IncomingEvents;

		bool IsRunning{ false };

		void Init(FGameThread::FCreateGameSceneFunc CreateGameSceneFunc);

		bool IsValid() const;

		void DeInit();
	};
}

#endif
