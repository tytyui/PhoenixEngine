#include "Core/Engine.h"

#include "Utility/Debug.h"
#include "Utility/Endian.h"

using namespace Phoenix;

void FEngine::Initialize(const UpdateCallback& OnUpdateCallback)
{
	F_LOG_OPEN("Log.txt");
	F_LOG_TRACE("Engine::Initialize()\n");
	FEndian::Init();

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
