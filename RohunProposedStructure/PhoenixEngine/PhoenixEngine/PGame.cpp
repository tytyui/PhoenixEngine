#include "PGame.h"
#include <iostream>

using namespace phoenix;

void PGame::StartGame()
{
	std::cout << "Game::StartGame\n";

	Engine = std::make_unique<PEngine>();
	Engine->Initialize([this](float DT) {InternalUpdate(DT);});
	Engine->Run();
}

void PGame::InternalUpdate(float DT)
{
	std::cout << "Game::InternalUpdate\n";
	//NVI
	Update(DT);
}
