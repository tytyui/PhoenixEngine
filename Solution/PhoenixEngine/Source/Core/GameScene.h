#ifndef PHOENIX_GAME_SCENE_H
#define PHOENIX_GAME_SCENE_H

#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	class FGameScene
	{
	public:
		FGameScene() = default;

		FGameScene(const FGameScene&) = delete;
		FGameScene& operator=(const FGameScene&) = delete;

		FGameScene(FGameScene&&) = delete;
		FGameScene& operator=(FGameScene&&) = delete;

		virtual ~FGameScene();

		void Init();

		void Update(const Float32 DeltaTimeSec);

		void DeInit();

	protected:
		virtual void OnInit() = 0;

		virtual void OnUpdate(const Float32 DeltaTimeSec) = 0;

		virtual void OnDeInit() = 0;

	private:
	};
}

#endif
