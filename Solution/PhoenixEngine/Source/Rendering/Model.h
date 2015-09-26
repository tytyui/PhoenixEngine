#ifndef PHOENIX_MODEL_H
#define PHOENIX_MODEL_H

#include "Utility/Misc/String.h"

namespace Phoenix
{
	class FModel
	{
	public:
		FModel() = default;

		FModel(const FModel&) = delete;
		FModel& operator=(const FModel&) = delete;

		FModel(FModel&&) = delete;
		FModel& operator=(FModel&&) = delete;

		void Init(const FString& File);

		bool IsValid() const;

		void DeInit();

		// #FIXME

	private:
		// #FIXME
	};
}

#endif
