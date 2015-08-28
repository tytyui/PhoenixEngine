#include "FEngine.h"
#include <iostream>

using namespace Phoenix;

void FEngine::Initialize(const UpdateCallback& OnUpdateCallback)
{
	std::cout << "Engine::Initialize\n";
	this->OnUpdateCallback = OnUpdateCallback;
}

void FEngine::Run()
{
	std::cout << "\nEngine::Run\n";

	//Game Loop
	{
		Update(0.016f);
		Update(0.016f);
		Update(0.016f);
	}
}

void FEngine::Update(float DT)
{
	std::cout << "\nEngine::Update\n";
	//Goes to PGame::InternalUpdate
	OnUpdateCallback(DT);
}
