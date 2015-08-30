#ifndef PHOENIX_GAME_H
#define PHOENIX_GAME_H

#include "Utility/Memory.h"
#include "Rendering/GLIncludes.h"

namespace Phoenix
{
	class FEngine;

	class FGame
	{
	public:
		FGame();

		FGame(const FGame&) = delete;
		FGame& operator=(const FGame&) = delete;

		FGame(FGame&&) = default;
		FGame& operator=(FGame&&) = default;

		virtual ~FGame();

		void StartGame();

	protected:
		virtual void Update(float DT) = 0;

	private:
		TUniquePtr<FEngine> Engine;

		void InternalUpdate(float DT);
	};
}

#endif
