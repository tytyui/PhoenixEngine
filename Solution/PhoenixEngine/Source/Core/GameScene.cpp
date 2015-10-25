#include "Core/GameScene.h"

using namespace Phoenix;

FGameScene::~FGameScene()
{
}

void FGameScene::Init()
{
	OnInit();
}

void FGameScene::Update(const Float32 DeltaTimeSec)
{
	OnUpdate(DeltaTimeSec);
}

void FGameScene::DeInit()
{
	OnDeInit();
}