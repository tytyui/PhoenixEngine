#ifndef PHOENIX_GAME_THREAD_H
#define PHOENIX_GAME_THREAD_H

#include "Audio/AudioEngine.h"
#include "Rendering/GFXEngine.h"
#include "Utility/Misc/Function.h"
#include "Utility/Misc/Memory.h"
#include "Utility/Misc/Primitives.h"
#include "Utility/Threading/Atomic.h"
#include "Utility/Threading/Thread.h"
#include "Utility/Threading/ThreadSafeVector.h"
#include "Core/GameScene.h"

namespace Phoenix
{
	class FGameThread
	{
	public:
		typedef TUniquePtr<FGameScene>(*FCreateGameSceneFunc)();

		struct FInitParams
		{
			TSharedPtr<class IWindow> Window;
			TThreadSafeVector<UInt32>* OutgoingEvents{ nullptr };
			TThreadSafeVector<UInt32>* IncomingEvents{ nullptr };
			FCreateGameSceneFunc CreateGameSceneFunc{ nullptr };

			bool IsValid() const;
		};

		FGameThread() = default;

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
		FGFXEngine GFXEngine;
		TUniquePtr<FGameScene> GameScene;

		TAtomic<bool> IsRunning{ false };

		void ThreadRun();

		void ThreadInit();

		void ThreadDeInit();
	};
}

#endif
