#ifndef PHOENIX_RENDER_ENGINE_H
#define PHOENIX_RENDER_ENGINE_H

#include "Utility/Misc/Memory.h"
#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	namespace ERenderEngineInternals
	{
		typedef UInt32 Type;

		enum Value : Type
		{
			Size = 512
		};
	}

	class FRenderEngine
	{
		friend struct FRenderEngineInternals;
	public:
		struct FInitParams
		{

		};

		FRenderEngine();

		FRenderEngine(const FRenderEngine&) = delete;
		FRenderEngine& operator=(const FRenderEngine&) = delete;

		FRenderEngine(FRenderEngine&&) = delete;
		FRenderEngine& operator=(FRenderEngine&&) = delete;

		~FRenderEngine();

		void Init(class IWindow& Window);

		bool IsValid() const;

		void DeInit();

		void Draw();

	protected:
	private:
		typedef void(FRenderEngine::*DrawFunction)();

		UInt8 PImplData[ERenderEngineInternals::Size];

		struct FRenderEngineInternals& Get();

		const struct FRenderEngineInternals& Get() const;

		void DrawInternal();

		void EmptyFunction();

		void DebugInitializeTestCode();

		void DebugRenderTestCode();
	};
}

#endif
