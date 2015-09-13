#include "TestGame.h"

#include "Utility/Debug/Debug.h"
#include "input/Input.h"

using namespace Phoenix;

void FTestGame::Init()
{
	GetInput()->RegisterKeyPressCallback([this](const FKeyboardEvent& KeyEvent)
	{
		OnKeyPress(KeyEvent);
	});
}

void FTestGame::Update(float dt)
{
	F_Log("TestGame::Update()\n");
}

void FTestGame::OnKeyPress(const FKeyboardEvent& KeyEvent)
{
	F_Log(__FUNCTION__);
}

