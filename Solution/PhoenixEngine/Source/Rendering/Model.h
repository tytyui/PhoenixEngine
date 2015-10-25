#ifndef PHOENIX_MODEL_H
#define PHOENIX_MODEL_H

#include "Utility/Containers/Vector.h"
#include "Utility/Misc/String.h"
#include "Rendering/MeshData.h"
#include "Rendering/Mesh.h"

namespace Phoenix
{
	class FModel
	{
	public:
		typedef TVector<FMesh> FMeshes;

		FModel() = default;

		FModel(const FModel&) = delete;
		FModel& operator=(const FModel&) = delete;

		FModel(FModel&&) = default;
		FModel& operator=(FModel&&) = default;

		void Init(const FMeshData::FEntries& MeshDataEntries);

		bool IsValid() const;

		void DeInit();

		const FMeshes& GetMeshes() const;

	private:
		FMeshes Meshes;
	};
}

#endif
