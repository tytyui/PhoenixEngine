#ifndef PHOENIX_GAME_H
#define PHOENIX_GAME_H

#include "Utility/FMemory.h"

namespace Phoenix
{
	class FEngine;

	class FGame
	{
	public:
		FGame();
		FGame(const FGame&) = delete;
		FGame(FGame&&) = default;
		FGame& operator = (const FGame&) = delete;
		FGame& operator = (FGame&&) = default;
		virtual ~FGame();

		void StartGame();

	protected:
		virtual void Update(float DT) = 0;

	private:
		TUnique<FEngine> Engine;

		//NVI pattern
		void InternalUpdate(float DT);
	};
}

#endif // PHOENIX_GAME_H_
