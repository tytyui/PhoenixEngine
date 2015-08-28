#ifndef GAME_TEST_GAME_H
#define GAME_TEST_GAME_H

#include "FGame.h"

class FTestGame : public Phoenix::FGame
{
public:
	FTestGame() = default;

protected:
	virtual void Update(float dt) override;
};

#endif // GAME_TEST_GAME_H_
