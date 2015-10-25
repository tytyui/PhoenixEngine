#include "Game/Game.h"

#include "Utility/Debug/Debug.h"
#include "Core/Engine.h"
#include "Input/Input.h"

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

	//Callback to User Game
	Init();

	Engine->Run();
}

void FGame::InternalUpdate(float DT)
{
	//Callback to User Game
	Update(DT);
}

void FGame::ShutDown()
{
	//#FIXME Establish proper shutdown protocol
	Engine->ShutDown();
}

const TUniquePtr<FInput>& FGame::GetInput() const
{
	return Engine->GetInput();
}

