#ifndef PHOENIX_GAME_H_
#define PHOENIX_GAME_H_

#include <memory>

namespace phoenix
{
	class PEngine;

	class PGame
	{
	public:
		PGame();

		PGame(const PGame& RHS) = delete;
		PGame& operator = (const PGame& RHS) = delete;

		PGame(PGame&& RHS) = default;
		PGame& operator = (PGame&& RHS) = default;

		virtual ~PGame();

		void StartGame();

	protected:
		virtual void Update(float DT) = 0;

	private:
		std::unique_ptr<PEngine> Engine;
		
		//NVI pattern
		void InternalUpdate(float DT);
	};
}

#endif // PHOENIX_GAME_H_
