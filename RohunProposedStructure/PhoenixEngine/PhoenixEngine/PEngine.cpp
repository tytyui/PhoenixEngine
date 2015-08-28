#include "PEngine.h"
#include <iostream>

using namespace phoenix;

void PEngine::Initialize(const UpdateCallback& OnUpdateCallback)
{
	std::cout << "Engine::Initialize\n";
	this->OnUpdateCallback = OnUpdateCallback;
}

void PEngine::Run()
{
	std::cout << "\nEngine::Run\n";

	//Game Loop
	{
		Update(0.016f);
		Update(0.016f);
		Update(0.016f);
	}
}

void PEngine::Update(float DT)
{
	std::cout << "\nEngine::Update\n";
	//Goes to PGame::InternalUpdate
	OnUpdateCallback(DT);
}
