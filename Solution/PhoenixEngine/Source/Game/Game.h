#ifndef PHOENIX_GAME_H
#define PHOENIX_GAME_H

#include "Utility/Misc/Memory.h"

namespace Phoenix
{
	class FEngine;
	class FInput;

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
		void ShutDown();

	protected:
		const TUniquePtr<FInput>& GetInput() const;

		//Callbacks to the UserGame class
		virtual void Init() {};
		virtual void Update(float DT) {};

	private:
		TUniquePtr<FEngine> Engine;

		void InternalUpdate(float DT);
	};
}

#endif
