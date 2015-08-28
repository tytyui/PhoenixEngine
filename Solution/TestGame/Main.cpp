#pragma comment (lib, "PhoenixEngine.lib")

#include <memory>
#include <iostream>
#include "FTestGame.h"

int main()
{
	using namespace Phoenix;

	auto game = std::make_unique<FTestGame>();
	game->StartGame();

	getchar();
	return 0;
}