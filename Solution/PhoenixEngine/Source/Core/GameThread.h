#ifndef PHOENIX_GAME_THREAD_H
#define PHOENIX_GAME_THREAD_H

#include "Utility/Atomic.h"
#include "Utility/Function.h"
#include "Utility/Thread.h"

namespace Phoenix
{
	class FGameThread
	{
	public:
		typedef TFunction<void(float)> FUpdateCallback;
		
		FGameThread();

		FGameThread(const FGameThread&) = delete;
		FGameThread& operator=(const FGameThread&) = delete;

		FGameThread(FGameThread&&) = delete;
		FGameThread& operator=(FGameThread&&) = delete;

		~FGameThread();

		void Init(const FUpdateCallback& OnUpdateCallback);

		bool IsValid() const;

		void ForceShutDown();

	protected:
	private:
		FThread Thread;
		FUpdateCallback UpdateCallback;

		TAtomic<bool> IsRunning{ false };

		void ThreadRun();

		void ThreadInit();

		void ThreadDeInit();
	};
}

#endif
