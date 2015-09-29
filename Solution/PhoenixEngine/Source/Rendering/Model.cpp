#include "Rendering/Model.h"

#include "Utility/Debug/Assert.h"
#include "Rendering/GLInterface.h"

#include "Utility/Debug/Debug.h"

using namespace Phoenix;

void FModel::Init(const FMeshData::FEntries& MeshDataEntries)
{
	F_Assert(MeshDataEntries.size(), "Invalid mesh data entries size of 0.");
	DeInit();

	Meshes.resize(MeshDataEntries.size());

	const SizeT Size = Meshes.size();

	for (SizeT I = 0; I < Size; ++I)
	{
		const FMeshData& MeshData = MeshDataEntries[I];
		Meshes[I].Init(MeshData);
	}
}

void FModel::Init(const FString& File)
{
	// #FIXME
}

bool FModel::IsValid() const
{
	for (const auto& Mesh : Meshes)
	{
		if (!Mesh.IsValid())
		{
			return false;
		}
	}

	return true;
}

void FModel::DeInit()
{
	Meshes.clear();
}

void FModel::Save(const FMeshData::FEntries& MeshDataEntries, const FString& File)
{
	// #FIXME
}

const FModel::FMeshes& FModel::GetMeshes() const
{
	return Meshes;
}
