#include "Rendering/Handles/GFXHandles.h"

using namespace Phoenix;

FModelHandles& FGFXHandles::GetModelHandles()
{
	return ModelHandles;
}

const FModelHandles& FGFXHandles::GetModelHandles() const
{
	return ModelHandles;
}

FImageHandles& FGFXHandles::GetImageHandles()
{
	return ImageHandles;
}

const FImageHandles& FGFXHandles::GetImageHandles() const
{
	return ImageHandles;
}

FShaderHandles& FGFXHandles::GetShaderHandles()
{
	return ShaderHandles;
}

const FShaderHandles& FGFXHandles::GetShaderHandles() const
{
	return ShaderHandles;
}
