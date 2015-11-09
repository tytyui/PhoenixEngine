#ifndef PHOENIX_RENDER_ENGINE_H
#define PHOENIX_RENDER_ENGINE_H

#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	namespace EGFXEngineInternals
	{
		typedef UInt32 Type;

		enum Value : Type
		{
			Size = 256
		};
	}

	class FGFXEngine
	{
		friend struct FGFXEngineInternals;
	public:
		FGFXEngine();

		FGFXEngine(const FGFXEngine&) = delete;
		FGFXEngine& operator=(const FGFXEngine&) = delete;

		FGFXEngine(FGFXEngine&&) = delete;
		FGFXEngine& operator=(FGFXEngine&&) = delete;

		~FGFXEngine();

		void Init(class IWindow& Window);

		bool IsValid() const;

		void DeInit();

		void Draw();

	protected:
	private:
		typedef void(FGFXEngine::*DrawFunction)();

		UInt8 PImplData[EGFXEngineInternals::Size];

		struct FGFXEngineInternals& Get();

		const struct FGFXEngineInternals& Get() const;

		void DrawInternal();

		void EmptyFunction();

		void DebugInitializeTestCode();

		void DebugRenderTestCode();
	};
}

#endif
