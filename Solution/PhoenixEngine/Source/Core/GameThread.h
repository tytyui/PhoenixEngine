#ifndef PHOENIX_GAME_THREAD_H
#define PHOENIX_GAME_THREAD_H

#include "Utility/Misc/Function.h"
#include "Utility/Threading/Atomic.h"
#include "Utility/Threading/Thread.h"

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
		FThreadRAII Thread;
		FUpdateCallback UpdateCallback;

		TAtomic<bool> IsRunning{ false };

		void ThreadRun();

		void ThreadInit();

		void ThreadDeInit();
	};
}

#endif
