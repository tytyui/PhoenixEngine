#ifndef PHOENIX_ENGINE_H
#define PHOENIX_ENGINE_H

#include "Utility/Function.h"

namespace Phoenix
{
	class FEngine
	{
	public:
		using UpdateCallback = TFunction<void(float)>;

		FEngine() = default;

		FEngine(const FEngine&) = delete;
		FEngine& operator=(const FEngine&) = delete;

		FEngine(FEngine&&) = default;
		FEngine& operator=(FEngine&&) = default;

		~FEngine() = default;

		void Init(const UpdateCallback& OnUpdateCallback);

		void DeInit();

		void Run();

	private:
		UpdateCallback OnUpdateCallback;

		void Update(float DT);
	};
}

#endif

