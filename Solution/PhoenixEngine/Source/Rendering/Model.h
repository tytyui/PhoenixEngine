#ifndef PHOENIX_MODEL_H
#define PHOENIX_MODEL_H

#include "Utility/Containers/Vector.h"
#include "Utility/Misc/String.h"
#include "Rendering/MeshData.h"

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

		void Init(const FMeshData::FEntries& MeshDataEntries);

		void Init(const FString& File);

		bool IsValid() const;

		void DeInit();

		void Save(const FString& File);

		// #FIXME

	private:
		// #FIXME
	};
}

#endif
