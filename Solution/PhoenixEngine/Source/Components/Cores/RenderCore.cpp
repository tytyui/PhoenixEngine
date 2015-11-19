#include "Components/Cores/RenderCore.h"
#include "Components/Transform.h"
#include "Components/ComponentFilter.h"

using namespace Phoenix;

FRenderCore::FRenderCore() : Base(ComponentFilter().Requires<Transform>())
{
	F_Log("TestCore created.");
}

void FRenderCore::Init()
{

}

void FRenderCore::Update(float dt)
{
}

FRenderCore::~FRenderCore()
{
}

void FRenderCore::Render()
{
	auto Renderables = GetEntities();
	for (auto& InEntity : Renderables)
	{
		auto& TransformComponent = InEntity.GetComponent<Transform>();
		TransformComponent.SetPosition(FVector3D(0, 1, 2));
	}
}
