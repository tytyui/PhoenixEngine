#include "Rendering/Model.h"

#include "Utility/Debug/Assert.h"
#include "Utility/Debug/Debug.h"
#include "Rendering/GLInterface.h"

using namespace Phoenix;

void FModel::Init(const FMeshData::FEntries& MeshDataEntries) {
	F_Assert(MeshDataEntries.size(), "Invalid mesh data entries size of 0.");
	DeInit();

	Meshes.resize(MeshDataEntries.size());

	const SizeT Size = Meshes.size();

	for (SizeT I = 0; I < Size; ++I) {
		const FMeshData& MeshData = MeshDataEntries[I];
		Meshes[I].Init(MeshData);
	}
}

bool FModel::IsValid() const {
	for (const auto& Mesh : Meshes) {
		if (!Mesh.IsValid()) {
			return false;
		}
	}

	return true;
}

void FModel::DeInit() {
	Meshes.clear();
}

const FModel::FMeshes& FModel::GetMeshes() const {
	return Meshes;
}
