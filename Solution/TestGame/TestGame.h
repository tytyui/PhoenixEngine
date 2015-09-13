#ifndef GAME_TEST_GAME_H
#define GAME_TEST_GAME_H

#include "Game/Game.h"

namespace Phoenix
{
	struct FKeyboardEvent;
}

class FTestGame : public Phoenix::FGame
{
public:
	FTestGame() = default;

protected:

	virtual void Init() override;
	virtual void Update(float DT) override;

private:
	void FTestGame::OnKeyPress(const Phoenix::FKeyboardEvent& KeyEvent);
};

#endif
