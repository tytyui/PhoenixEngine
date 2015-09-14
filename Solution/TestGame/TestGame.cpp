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

	GetInput()->RegisterMouseClickCallback([this](const FMouseClickEvent& MouseClickEvent)
	{
		OnMouseClick(MouseClickEvent);
	});
}

void FTestGame::Update(float dt)
{
	F_Log("TestGame::Update()\n");
}

void FTestGame::OnKeyPress(const FKeyboardEvent& KeyEvent)
{
	F_Log(__FUNCTION__);
	if (KeyEvent.KeyCode == EKeyCode::Esc)
	{
		ShutDown();
	}
}

void FTestGame::OnMouseClick(const FMouseClickEvent& MouseClickEvent)
{
	F_Log(__FUNCTION__);
}

