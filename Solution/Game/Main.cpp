#pragma comment (lib, "PhoenixEngine.lib")

#include "Core/Engine.h"
#include "Components/Transform.h"

using namespace Phoenix;

class FStartScene : public FGameScene
{
public:
protected:
	virtual void OnInit() override
	{
		auto& myObj = this->CreateGameObject();
		myObj.AddComponent<Transform>();
		
	}

	virtual void OnUpdate(const Float32 DeltaTimeSec) override
	{
	}

	virtual void OnDeInit() override
	{

	}

private:
};

static TUniquePtr<FGameScene> CreateGameSceneFunc()
{
	return std::make_unique<FStartScene>();
}

int main()
{
	FEngine Engine;
	Engine.Run(CreateGameSceneFunc);
	return 0;
}
