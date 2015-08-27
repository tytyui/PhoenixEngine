#include "PTestGame.h"
#include <iostream>

using namespace phoenix;

void PTestGame::Update(float dt)
{
	//Don't need to call BaseGame::Update because of NVI

	std::cout << "TestGame::Update()\n";
}
