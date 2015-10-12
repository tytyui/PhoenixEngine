#ifndef PHOENIX_GAME_THREAD_H
#define PHOENIX_GAME_THREAD_H

#include "Audio/AudioEngine.h"
#include "Rendering/RenderEngine.h"
#include "Platform/Windowing/IWindow.h"
#include "Utility/Misc/Function.h"
#include "Utility/Misc/Primitives.h"
#include "Utility/Threading/Atomic.h"
#include "Utility/Threading/Thread.h"
#include "Utility/Threading/ThreadSafeVector.h"

namespace Phoenix
{
	class FGameThread
	{
	public:
		typedef TFunction<void(Float32)> FUpdateCallback;

		struct FInitParams
		{
			IWindow* Window{ nullptr };
			TThreadSafeVector<UInt32>* OutgoingEvents{ nullptr };
			TThreadSafeVector<UInt32>* IncomingEvents{ nullptr };
			FUpdateCallback UpdateCallback;

			bool IsValid() const;
		};

		FGameThread();

		FGameThread(const FGameThread&) = delete;
		FGameThread& operator=(const FGameThread&) = delete;

		FGameThread(FGameThread&&) = delete;
		FGameThread& operator=(FGameThread&&) = delete;

		~FGameThread();

		void Init(const FInitParams& InitParams);

		bool IsValid() const;

		void ForceShutDown();

	protected:
	private:
		FSafeThread Thread;
		FInitParams InitData;
		FAudioEngine AudioEngine;
		FRenderEngine RenderEngine;

		TAtomic<bool> IsRunning{ false };

		void ThreadRun();

		void ThreadInit();

		void ThreadDeInit();
	};
}

#endif
