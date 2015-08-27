#pragma comment (lib, "PhoenixEngine.lib")

#include <memory>
#include <iostream>
#include "PTestGame.h"

int main()
{
	using namespace phoenix;

	auto game = std::make_unique<PTestGame>();
	game->StartGame();

	getchar();
	return 0;
}