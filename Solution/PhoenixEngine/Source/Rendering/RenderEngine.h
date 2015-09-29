#ifndef PHOENIX_RENDER_ENGINE_H
#define PHOENIX_RENDER_ENGINE_H

#include "Utility/Misc/Primitives.h"
#include "Platform/Windowing/IWindow.h"

namespace Phoenix
{
	namespace ERenderEngineInternals
	{
		typedef UInt32 Type;

		enum Value : Type
		{
			Size = 64
		};
	}

	class FRenderEngine
	{
	public:
		struct FInitParams
		{
			IWindow* Window{ nullptr };

			bool IsValid() const;
		};

		FRenderEngine();
		
		FRenderEngine(const FRenderEngine&) = delete;
		FRenderEngine& operator=(const FRenderEngine&) = delete;

		FRenderEngine(FRenderEngine&&) = delete;
		FRenderEngine& operator=(FRenderEngine&&) = delete;

		~FRenderEngine();

		void Init(const FInitParams& InInitParams);

		bool IsValid() const;

		void DeInit();

		void Render();

	private:
		UInt8 PImplData[ERenderEngineInternals::Size];

		struct FRenderEngineInternals& Get();

		const struct FRenderEngineInternals& Get() const;
	};
}

#endif
