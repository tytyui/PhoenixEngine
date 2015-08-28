#include "FGame.h"
#include <iostream>
#include "Core/FEngine.h"

using namespace Phoenix;

FGame::FGame() {};

FGame::~FGame() {};

void FGame::StartGame()
{
	std::cout << "Game::StartGame\n";

	Engine = std::make_unique<FEngine>();
	Engine->Initialize([this](float DT) {InternalUpdate(DT);});
	Engine->Run();
}

void FGame::InternalUpdate(float DT)
{
	std::cout << "Game::InternalUpdate\n";
	//NVI
	Update(DT);
}
