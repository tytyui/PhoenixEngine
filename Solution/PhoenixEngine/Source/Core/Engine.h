#ifndef PHOENIX_ENGINE_H
#define PHOENIX_ENGINE_H

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
	};
}

#endif

