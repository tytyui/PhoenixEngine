#ifndef GAME_TEST_GAME_H
#define GAME_TEST_GAME_H

#include "Game/Game.h"

namespace Phoenix
{
	struct FKeyboardEvent;
	struct FMouseClickEvent;
}

class FTestGame : public Phoenix::FGame
{
public:
	FTestGame() = default;

protected:

	virtual void Init() override;
	virtual void Update(float DT) override;

private:

	void OnKeyPress(const Phoenix::FKeyboardEvent& KeyEvent);
	void OnMouseClick(const Phoenix::FMouseClickEvent& MouseClickEvent);
};

#endif
