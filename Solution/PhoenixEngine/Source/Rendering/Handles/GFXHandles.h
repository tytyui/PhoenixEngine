#ifndef PHOENIX_GFX_HANDLES_H
#define PHOENIX_GFX_HANDLES_H

#include "Rendering/Handles/ModelHandles.h"
#include "Rendering/Handles/ImageHandles.h"
#include "Rendering/Handles/ShaderHandles.h"

namespace Phoenix
{
	class FGFXHandles
	{
	public:
		FModelHandles& GetModelHandles();
		const FModelHandles& GetModelHandles() const;

		FImageHandles& GetImageHandles();
		const FImageHandles& GetImageHandles() const;

		FShaderHandles& GetShaderHandles();
		const FShaderHandles& GetShaderHandles() const;

	protected:
	private:
		FModelHandles ModelHandles;
		FImageHandles ImageHandles;
		FShaderHandles ShaderHandles;
	};
}

#endif
