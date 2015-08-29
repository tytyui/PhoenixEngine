#ifndef GAME_TEST_GAME_H
#define GAME_TEST_GAME_H

#include "Game/Game.h"

class FTestGame : public Phoenix::FGame
{
public:
	FTestGame() = default;

protected:
	virtual void Update(float dt) override;
};

#endif
