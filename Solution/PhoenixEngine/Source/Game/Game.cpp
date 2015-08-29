#include "Game/Game.h"

#include "Utility/Debug.h"
#include "Core/Engine.h"

using namespace Phoenix;

FGame::FGame()
{
}

FGame::~FGame()
{
}

void FGame::StartGame()
{
	Engine = std::make_unique<FEngine>();
	Engine->Init([this](float DT)
	{
		InternalUpdate(DT);
	});
	Engine->Run();
}

void FGame::InternalUpdate(float DT)
{
	F_LogTrace("Game::InternalUpdate()");

	Update(DT);
}
