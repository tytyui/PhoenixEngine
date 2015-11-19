#pragma once
#include "Components/Core.h"

namespace Phoenix
{
	class FRenderCore :
		public FCore<FRenderCore>
	{
	public:
		FRenderCore();
		~FRenderCore();

		// Separate init from construction code.
		virtual void Init() final;

		// Each core must update each loop
		virtual void Update(float dt) final;

		void Render();
	};
}