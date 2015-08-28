#ifndef GAME_TEST_GAME_H_
#define GAME_TEST_GAME_H_

#include "PGame.h"

class PTestGame : public phoenix::PGame
{
public:
	PTestGame() = default;

protected:
	virtual void Update(float dt) override;
};

#endif // GAME_TEST_GAME_H_
