#ifndef PHOENIX_RENDER_ENGINE_H
#define PHOENIX_RENDER_ENGINE_H

#include "Platform/Windowing/IWindow.h"

namespace Phoenix
{
	class FRenderEngine
	{
	public:
		struct FInitParams
		{
			IWindow* Window{ nullptr };

			bool IsValid() const;
		};

		FRenderEngine() = default;
		
		FRenderEngine(const FRenderEngine&) = delete;
		FRenderEngine& operator=(const FRenderEngine&) = delete;

		FRenderEngine(FRenderEngine&&) = delete;
		FRenderEngine& operator=(FRenderEngine&&) = delete;

		void Init(const FInitParams& InInitParams);

		bool IsValid() const;

		void DeInit();

		void Render();

		// #FIXME

	protected:
	private:
		FInitParams InitParams;
		bool IsRunning{ false };
	};
}

#endif
