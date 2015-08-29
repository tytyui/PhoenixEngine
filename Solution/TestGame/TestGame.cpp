#include "TestGame.h"
#include <iostream>

using namespace Phoenix;

void FTestGame::Update(float dt)
{
	//Don't need to call BaseGame::Update because of NVI

	std::cout << "TestGame::Update\n";
}
