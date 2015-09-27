#include "Rendering/ModelProcessor.h"

#include <limits>  // #FIXME: Wrap this.

#include "ExternalLib/AssimpIncludes.h"
#include "ExternalLib/FBXIncludes.h"
#include "Utility/Containers/Vector.h"
#include "Utility/Debug/Assert.h"
#include "Utility/Debug/Debug.h"

// #FIXME: If the ::max() functions are wrapped,
// then this can be removed.
// Note: This is required because some prorammer 
// decided that defining max(a, b) was a good idea.
#undef max

using namespace Phoenix;

namespace Phoenix
{
	struct FModelProcessorHelper
	{
		static void ProcessMesh(
			FModelProcessor::FDataEntry& DataEntry,
			const aiScene& AIScene, 
			const aiMesh& AIMesh);

		template <class IndexT>
		static void ProcessMeshFaces(
			FModelProcessor::FDataEntry& DataEntry,
			const aiScene& AIScene,
			const aiMesh& AIMesh);
	};
}

void FModelProcessor::Load(const FLoadParams& LoadParams)
{
	F_Assert(LoadParams.File.size(), "No file was specified.");
	F_Assert(LoadParams.ModelDataHints, "No hints were specified.");
	
	// #FIXME: At some point (if necessary), the amount of 
	// allocations this class performs can be significantly
	// reduced in order to maximize performance.
	*this = FModelProcessor();
	
	if (IsFileFBX(LoadParams.File))
	{
		LoadFBX(LoadParams);
		return;
	}

	if (IsFileMisc(LoadParams.File))
	{
		LoadMisc(LoadParams);
		return;
	}

	F_Assert(false, "Invalid file type.");
}

FModelProcessor::FDataEntries& FModelProcessor::GetDataEntries()
{
	return DataEntries;
}

void FModelProcessor::LoadFBX(const FLoadParams& LoadParams)
{
	// #FIXME
}

void FModelProcessor::LoadMisc(const FLoadParams& LoadParams)
{
	static const SizeT DefaultCapacity = 32;
	static const SizeT DefaultDataEntryCapacity = 16;

	const UInt32 Flags =
		aiProcess_CalcTangentSpace |
		aiProcess_JoinIdenticalVertices |
		aiProcess_Triangulate |
		aiProcess_GenNormals |
		aiProcess_ValidateDataStructure |
		aiProcess_ImproveCacheLocality |
		aiProcess_OptimizeMeshes |
		aiProcess_OptimizeGraph |
		aiProcess_FlipUVs;

	Assimp::Importer ModelLoader;
	const aiScene* const AIScene = ModelLoader.ReadFile(LoadParams.File, Flags);

	const bool SceneIsValid = AIScene != nullptr;

	if (!SceneIsValid)
	{
		F_LogError("Failed to load misc model.  Error log: " << ModelLoader.GetErrorString());
		return;
	}

	F_Assert(AIScene->mRootNode != nullptr, "Root node is invalid.");
	F_Assert((AIScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) == 0, "Scene flags are invalid.");

	const aiScene& AISceneRef = *AIScene;

	TVector<const aiNode*> AINodes;

	AINodes.reserve(DefaultCapacity);
	AINodes.push_back(AISceneRef.mRootNode);

	for (SizeT I = 0; I < AINodes.size(); ++I)
	{
		for (UInt32 ChildI = 0; ChildI < AINodes[I]->mNumChildren; ++ChildI)
		{
			F_Assert(AINodes[I]->mChildren[ChildI], "Node index " << I << " has null mesh at index " << ChildI << ".");
			const aiNode* const ChildNode = AINodes[I]->mChildren[ChildI];
			AINodes.push_back(ChildNode);
		}
	}
	
	F_Assert(DataEntries.size() == 0, "DataEntries was not cleared prior to this operation.");
	DataEntries.reserve(DefaultDataEntryCapacity);

	const SizeT AINodesSize = AINodes.size();
	for (SizeT I = 0; I < AINodesSize; ++I)
	{
		for (UInt32 MeshI = 0; MeshI < AINodes[I]->mNumMeshes; ++MeshI)
		{
			{
				FDataEntry DataEntry;
				DataEntry.ModelData = LoadParams.ModelDataHints;

				DataEntries.push_back(std::move(DataEntry));
			}

			const UInt32 Handle = AINodes[I]->mMeshes[MeshI];
			F_Assert(Handle < AISceneRef.mNumMeshes, "Index " << Handle << " is out of range of " << AISceneRef.mNumMeshes);

			const SizeT DataEntryIndex = DataEntries.size() - 1;
			FDataEntry& DataEntry = DataEntries[DataEntryIndex];

			const aiMesh& AIMesh = *AISceneRef.mMeshes[Handle];
			FModelProcessorHelper::ProcessMesh(DataEntry, AISceneRef, AIMesh);
			
			if (DataEntry.ModelData == EModelData::None)
			{
				F_LogError("Data entry initialization failed.");
				DataEntries.pop_back();
			}
		}
	}

	F_Log("Processed " << LoadParams.File);
}

bool FModelProcessor::IsFileFBX(const FString& File)
{
	F_Assert(File.size(), "Invalid file name.");

	// #FIXME: Use a "HasExtension" method instead.
	FString Extension = FStr::ExtractExtension(File);
	FStr::ToLower(Extension);
	
	const bool IsFBX = Extension == "fbx";
	return IsFBX;
}

bool FModelProcessor::IsFileMisc(const FString& File)
{
	F_Assert(File.size(), "Invalid file name.");
	// Note: Currently, if a file isn't an FBX 
	// file, the misc loader should be used.
	const bool IsFBX = IsFileFBX(File);

	const bool IsMisc = !IsFBX;
	return IsMisc;
}

void FModelProcessorHelper::ProcessMesh(
	FModelProcessor::FDataEntry& DataEntry,
	const aiScene& AIScene,
	const aiMesh& AIMesh)
{
	F_Assert(DataEntry.ModelData, "No model data hints were requested.");

	static const UInt8 FloatsPerVertex = 3;
	static const UInt8 FloatsPerUVCoord = 2;

	const bool PositionHintIsSet = (DataEntry.ModelData & EModelData::Positions) != 0;
	const bool NormalsHintIsSet = (DataEntry.ModelData & EModelData::Normals) != 0;
	const bool IndicesHintIsSet = (DataEntry.ModelData & EModelData::Indices) != 0;
	const bool UVCoordsHintIsSet = (DataEntry.ModelData & EModelData::UVCoords) != 0;

	const bool HasVertexData = AIMesh.mNumVertices > 0;
	const bool HasIndexData = AIMesh.mNumFaces > 0;
	const bool HasUVCoords = AIMesh.mTextureCoords[0] != nullptr;

	if (!HasVertexData || !HasIndexData)
	{
		F_LogError("This mesh does not have any vertex and/or index data.");
		DataEntry.ModelData = EModelData::None;
		return;
	}

	if (IndicesHintIsSet && !HasIndexData)
	{
		F_LogWarning("Indices were specified but this mesh does not have any.");
		DataEntry.ModelData &= ~EModelData::Indices;
	}

	if (UVCoordsHintIsSet && !HasUVCoords)
	{
		F_LogWarning("UVCoords were specified but this mesh does not have any.");
		DataEntry.ModelData &= ~EModelData::UVCoords;
	}

	if (PositionHintIsSet && HasVertexData)
	{
		const SizeT PositionCount = AIMesh.mNumVertices * FloatsPerVertex;
		DataEntry.Positions.resize(PositionCount);

		for (UInt32 I = 0; I < AIMesh.mNumVertices; ++I)
		{
			const SizeT X = I * FloatsPerVertex;
			const SizeT Y = I * FloatsPerVertex + 1;
			const SizeT Z = I * FloatsPerVertex + 2;

			DataEntry.Positions[X] = AIMesh.mVertices[I].x;
			DataEntry.Positions[Y] = AIMesh.mVertices[I].y;
			DataEntry.Positions[Z] = AIMesh.mVertices[I].z;
		}
	}

	if (NormalsHintIsSet && HasVertexData)
	{
		const SizeT NormalsCount = AIMesh.mNumVertices * FloatsPerVertex;
		DataEntry.Normals.resize(NormalsCount);

		for (UInt32 I = 0; I < AIMesh.mNumVertices; ++I)
		{
			const SizeT X = I * FloatsPerVertex;
			const SizeT Y = I * FloatsPerVertex + 1;
			const SizeT Z = I * FloatsPerVertex + 2;

			DataEntry.Normals[X] = AIMesh.mNormals[I].x;
			DataEntry.Normals[Y] = AIMesh.mNormals[I].y;
			DataEntry.Normals[Z] = AIMesh.mNormals[I].z;
		}
	}

	if (UVCoordsHintIsSet && HasUVCoords)
	{
		const SizeT UVCoordsCount = AIMesh.mNumVertices * FloatsPerUVCoord;
		DataEntry.UVCoords.resize(UVCoordsCount);

		for (UInt32 I = 0; I < AIMesh.mNumVertices; ++I)
		{
			const SizeT X = I * FloatsPerUVCoord;
			const SizeT Y = I * FloatsPerUVCoord + 1;

			DataEntry.UVCoords[X] = AIMesh.mTextureCoords[0][I].x;
			DataEntry.UVCoords[Y] = AIMesh.mTextureCoords[0][I].y;
		}
	}

	if (IndicesHintIsSet && HasIndexData)
	{
		if (AIMesh.mNumVertices <= std::numeric_limits<UInt8>::max()) // #FIXME: Wrap ::max.
		{
			ProcessMeshFaces<UInt8>(DataEntry, AIScene, AIMesh);
		}
		else if (AIMesh.mNumVertices <= std::numeric_limits<UInt16>::max()) // #FIXME: Wrap ::max.
		{
			ProcessMeshFaces<UInt16>(DataEntry, AIScene, AIMesh);
		}
		else
		{
			ProcessMeshFaces<UInt32>(DataEntry, AIScene, AIMesh);
		}
	}
	
	// #FIXME: Process materials/textures.
}

template <class IndexT>
void FModelProcessorHelper::ProcessMeshFaces(
	FModelProcessor::FDataEntry& DataEntry,
	const aiScene& AIScene,
	const aiMesh& AIMesh)
{
	static_assert(!std::numeric_limits<IndexT>::is_signed, "IndexT must be unsigned.");
	static_assert(sizeof(IndexT) >= 1 && sizeof(IndexT) <= 4, "IndexT must be 1, 2, or 4 bytes.");

	static const UInt8 IndicesPerFace = 3;

	const SizeT IndicesSize = AIMesh.mNumFaces * IndicesPerFace * sizeof(IndexT);

	DataEntry.Indices.resize(IndicesSize);
	DataEntry.IndexTSize = sizeof(IndexT);

	for (UInt32 I = 0; I < AIMesh.mNumFaces; I++)
	{
		const aiFace& AIFace = AIMesh.mFaces[I];

		for (UInt8 J = 0; J < IndicesPerFace; ++J)
		{
			F_Assert(AIFace.mIndices[J] <= std::numeric_limits<IndexT>::max(), "Index is out of bounds.");
			const SizeT IndicesI = I * IndicesPerFace + sizeof(IndexT) * J;

			IndexT* const IndexTPtr = reinterpret_cast<IndexT*>(&(DataEntry.Indices[IndicesI]));
			*IndexTPtr = static_cast<IndexT>(AIFace.mIndices[J]);
		}
	}
}
