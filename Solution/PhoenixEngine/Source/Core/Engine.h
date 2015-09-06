#ifndef PHOENIX_ENGINE_H
#define PHOENIX_ENGINE_H

#include "Utility/Threading/ThreadSafeVector.h"
#include "Rendering/GLIncludes.h"
#include "Core/GameThread.h"

namespace Phoenix
{
	class FEngine
	{
	public:
		FEngine();

		FEngine(const FEngine&) = delete;
		FEngine& operator=(const FEngine&) = delete;

		FEngine(FEngine&&) = delete;
		FEngine& operator=(FEngine&&) = delete;

		void Init(const FGameThread::FUpdateCallback& UpdateCallback);

		void DeInit();

		void Run();

	private:
		FGameThread GameThread;
		// FIXME: Change UInt32 to the Event structure.
		TThreadSafeVector<UInt32> OutgoingEvents;
		TThreadSafeVector<UInt32> IncomingEvents;
		bool IsRunning{ false };
	};
}

#endif
