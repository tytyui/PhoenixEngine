#include "TestGame.h"

#include "Utility/Debug.h"

using namespace Phoenix;

void FTestGame::Update(float dt)
{
	//Don't need to call BaseGame::Update because of NVI
	F_LogTrace("TestGame::Update()\n");
}
