#include "Game/Game.h"

#include "Utility/Debug.h"
#include "Core/Engine.h"

using namespace Phoenix;

FGame::FGame() {}

FGame::~FGame() {}

void FGame::StartGame()
{
	F_LOG_OPEN("Log.txt");
	F_LOG_TRACE("Game::StartGame()\n");

	Engine = std::make_unique<FEngine>();
	Engine->Initialize([this](float DT) {InternalUpdate(DT);});
	Engine->Run();
}

void FGame::InternalUpdate(float DT)
{
	F_LOG_TRACE("Game::InternalUpdate()");

	Update(DT);
}
