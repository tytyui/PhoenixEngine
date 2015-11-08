#include "Rendering/Caches/GFXCaches.h"

using namespace Phoenix;

FModelCache& FGFXCaches::GetModelCache()
{
	return ModelCache;
}

const FModelCache& FGFXCaches::GetModelCache() const
{
	return ModelCache;
}

FImageCache& FGFXCaches::GetImageCache()
{
	return ImageCache;
}

const FImageCache& FGFXCaches::GetImageCache() const
{
	return ImageCache;
}

FShaderCache& FGFXCaches::GetShaderCache()
{
	return ShaderCache;
}

const FShaderCache& FGFXCaches::GetShaderCache() const
{
	return ShaderCache;
}
