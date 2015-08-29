#include "Core/Engine.h"

#include "Utility/Debug.h"

using namespace Phoenix;

void FEngine::Initialize(const UpdateCallback& OnUpdateCallback)
{
	F_LOG_TRACE("Engine::Initialize()\n");
	this->OnUpdateCallback = OnUpdateCallback;
}

void FEngine::DeInit()
{
	F_LOG_CLOSE();
}

void FEngine::Run()
{
	F_LOG_TRACE("Engine::Run()\n");

	//Game Loop
	{
		Update(0.016f);
		Update(0.016f);
		Update(0.016f);
	}
}

void FEngine::Update(float DT)
{
	F_LOG_TRACE("Engine::Update()");

	//Goes to PGame::InternalUpdate
	OnUpdateCallback(DT);
}
