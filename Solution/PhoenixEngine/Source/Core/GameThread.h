#ifndef PHOENIX_GAME_THREAD_H
#define PHOENIX_GAME_THREAD_H

#include "Utility/Misc/Function.h"
#include "Utility/Misc/Memory.h"
#include "Utility/Misc/Primitives.h"
#include "Utility/Threading/Atomic.h"
#include "Utility/Threading/Thread.h"
#include "Utility/Threading/ThreadSafeVector.h"
#include "Platform/Event/Event.h"
#include "Audio/AudioEngine.h"
#include "Rendering/GFXEngine.h"
#include "Core/GameScene.h"
#include "Components/Cores/RenderCore.h"

namespace Phoenix
{
	class FGameThread
	{
	public:
		typedef TUniquePtr<FGameScene>(*FCreateGameSceneFunc)();

		struct FInitParams
		{
			TSharedPtr<class IWindow> Window;
			TThreadSafeVector<FEvent>* OutgoingEvents{ nullptr };
			TThreadSafeVector<FEvent>* IncomingEvents{ nullptr };
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
		FRenderCore RenderCore;
		TUniquePtr<FGameScene> GameScene;

		TAtomic<bool> IsRunning{ false };

		void ThreadRun();

		void ThreadInit();

		void ThreadDeInit();

		void ThreadHandleEvent(const FEvent& Event);
	};
}

#endif
