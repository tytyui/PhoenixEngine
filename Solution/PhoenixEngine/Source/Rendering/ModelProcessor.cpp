#include "Rendering/ModelProcessor.h"

#include "ExternalLib/AssimpIncludes.h"
#include "ExternalLib/FBXIncludes.h"
#include "Utility/Containers/Vector.h"
#include "Utility/Debug/Assert.h"
#include "Utility/Debug/Debug.h"

// Note: This is required because some prorammer 
// decided that defining max(a, b) was a good idea.
#undef max

using namespace Phoenix;

namespace Phoenix {
	struct FModelProcessorHelper {
		static void ProcessMesh(
			FMeshData& MeshData,
			const aiScene& AIScene,
			const aiMesh& AIMesh);

		template <class IndexT>
		static void ProcessMeshFaces(
			FMeshData& MeshData,
			const aiScene& AIScene,
			const aiMesh& AIMesh);
	};
}

void FModelProcessor::Load(const FLoadParams& LoadParams) {
	F_Assert(LoadParams.File, "No file was specified.");
	F_Assert(LoadParams.MeshAttributeHints, "No hints were specified.");

	// #FIXME: At some point (if necessary), the amount of 
	// allocations this class performs can be significantly
	// reduced in order to maximize performance.
	Unload();

	if (IsFileFBX(LoadParams.File)) {
		LoadFBX(LoadParams);
		return;
	}

	if (IsFileMisc(LoadParams.File)) {
		LoadMisc(LoadParams);
		return;
	}

	F_Assert(false, "Invalid file type.");
}

void FModelProcessor::Save(const FSaveParams& SaveParams) {
	F_Assert(false, "");
	// #FIXME
}

void FModelProcessor::Unload() {
	MeshEntries.clear();
}

const bool FModelProcessor::HasMeshDataEntries() const {
	const bool Result = MeshEntries.size() != 0;
	return Result;
}

const FMeshData::FEntries& FModelProcessor::GetMeshDataEntries() const {
	return MeshEntries;
}

void FModelProcessor::LoadFBX(const FLoadParams& LoadParams) {
	// #FIXME
}

void FModelProcessor::LoadMisc(const FLoadParams& LoadParams) {
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

	if (!SceneIsValid) {
		F_LogError("Failed to load misc model.  Error log: " << ModelLoader.GetErrorString());
		return;
	}

	F_Assert(AIScene->mRootNode != nullptr, "Root node is invalid.");
	F_Assert((AIScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) == 0, "Scene flags are invalid.");

	const aiScene& AISceneRef = *AIScene;

	TVector<const aiNode*> AINodes;

	AINodes.reserve(DefaultCapacity);
	AINodes.push_back(AISceneRef.mRootNode);

	for (SizeT I = 0; I < AINodes.size(); ++I) {
		for (UInt32 ChildI = 0; ChildI < AINodes[I]->mNumChildren; ++ChildI) {
			F_Assert(AINodes[I]->mChildren[ChildI],
				"Node index " << I << " has null mesh at index " << ChildI << ".");

			const aiNode* const ChildNode = AINodes[I]->mChildren[ChildI];
			AINodes.push_back(ChildNode);
		}
	}

	F_Assert(MeshEntries.size() == 0, "DataEntries was not cleared prior to this operation.");
	MeshEntries.reserve(DefaultDataEntryCapacity);

	const SizeT AINodesSize = AINodes.size();
	for (SizeT I = 0; I < AINodesSize; ++I) {
		for (UInt32 MeshI = 0; MeshI < AINodes[I]->mNumMeshes; ++MeshI) {
			{
				FMeshData MeshData;
				MeshData.ModelData = LoadParams.MeshAttributeHints;

				MeshEntries.push_back(std::move(MeshData));
			}

			const UInt32 Handle = AINodes[I]->mMeshes[MeshI];
			F_Assert(Handle < AISceneRef.mNumMeshes,
				"Index " << Handle << " is out of range of " << AISceneRef.mNumMeshes);

			const SizeT DataEntryIndex = MeshEntries.size() - 1;
			FMeshData& MeshData = MeshEntries[DataEntryIndex];

			const aiMesh& AIMesh = *AISceneRef.mMeshes[Handle];
			FModelProcessorHelper::ProcessMesh(MeshData, AISceneRef, AIMesh);

			if (MeshData.ModelData == EMeshAttribute::None) {
				F_LogError("Data entry initialization failed.");
				MeshEntries.pop_back();
			}
		}
	}

	F_LogTrace("Model created from " << LoadParams.File);
}

bool FModelProcessor::IsFileFBX(const FString& File) {
	F_Assert(File.size(), "Invalid file name.");

	// #FIXME: Use a "HasExtension" method instead.
	FString Extension = FStr::ExtractExtension(File);
	FStr::ToLower(Extension);

	const bool IsFBX = Extension == "fbx";
	return IsFBX;
}

bool FModelProcessor::IsFileMisc(const FString& File) {
	F_Assert(File.size(), "Invalid file name.");
	// Note: Currently, if a file isn't an FBX 
	// file, the misc loader should be used.
	const bool IsFBX = IsFileFBX(File);
	return !IsFBX;
}

void FModelProcessorHelper::ProcessMesh(
	FMeshData& MeshData,
	const aiScene& AIScene,
	const aiMesh& AIMesh) {
	F_Assert(MeshData.ModelData, "No model data hints were requested.");

	static const UInt8 FloatsPerVertex = 3;
	static const UInt8 FloatsPerUVCoord = 2;

	const bool PositionHintIsSet = (MeshData.ModelData & EMeshAttribute::Positions) != 0;
	const bool NormalsHintIsSet = (MeshData.ModelData & EMeshAttribute::Normals) != 0;
	const bool IndicesHintIsSet = (MeshData.ModelData & EMeshAttribute::Indices) != 0;
	const bool UVCoordsHintIsSet = (MeshData.ModelData & EMeshAttribute::UVCoords) != 0;

	const bool HasVertexData = AIMesh.mNumVertices > 0;
	const bool HasIndexData = AIMesh.mNumFaces > 0;
	const bool HasUVCoords = AIMesh.mTextureCoords[0] != nullptr;

	if (!HasVertexData || !HasIndexData) {
		F_LogError("This mesh does not have any vertex and/or index data.");
		MeshData.ModelData = EMeshAttribute::None;
		return;
	}

	if (IndicesHintIsSet && !HasIndexData) {
		F_LogWarning("Indices were specified but this mesh does not have any.");
		MeshData.ModelData &= ~EMeshAttribute::Indices;
	}

	if (UVCoordsHintIsSet && !HasUVCoords) {
		F_LogWarning("UVCoords were specified but this mesh does not have any.");
		MeshData.ModelData &= ~EMeshAttribute::UVCoords;
	}

	if (PositionHintIsSet && HasVertexData) {
		const SizeT PositionCount = AIMesh.mNumVertices * FloatsPerVertex;
		MeshData.Positions.resize(PositionCount);

		for (UInt32 I = 0; I < AIMesh.mNumVertices; ++I) {
			const SizeT X = I * FloatsPerVertex;
			const SizeT Y = I * FloatsPerVertex + 1;
			const SizeT Z = I * FloatsPerVertex + 2;

			MeshData.Positions[X] = AIMesh.mVertices[I].x;
			MeshData.Positions[Y] = AIMesh.mVertices[I].y;
			MeshData.Positions[Z] = AIMesh.mVertices[I].z;
		}
	}

	if (NormalsHintIsSet && HasVertexData) {
		const SizeT NormalsCount = AIMesh.mNumVertices * FloatsPerVertex;
		MeshData.Normals.resize(NormalsCount);

		for (UInt32 I = 0; I < AIMesh.mNumVertices; ++I) {
			const SizeT X = I * FloatsPerVertex;
			const SizeT Y = I * FloatsPerVertex + 1;
			const SizeT Z = I * FloatsPerVertex + 2;

			MeshData.Normals[X] = AIMesh.mNormals[I].x;
			MeshData.Normals[Y] = AIMesh.mNormals[I].y;
			MeshData.Normals[Z] = AIMesh.mNormals[I].z;
		}
	}

	if (UVCoordsHintIsSet && HasUVCoords) {
		const SizeT UVCoordsCount = AIMesh.mNumVertices * FloatsPerUVCoord;
		MeshData.UVCoords.resize(UVCoordsCount);

		for (UInt32 I = 0; I < AIMesh.mNumVertices; ++I) {
			const SizeT X = I * FloatsPerUVCoord;
			const SizeT Y = I * FloatsPerUVCoord + 1;

			MeshData.UVCoords[X] = AIMesh.mTextureCoords[0][I].x;
			MeshData.UVCoords[Y] = AIMesh.mTextureCoords[0][I].y;
		}
	}

	if (IndicesHintIsSet && HasIndexData) {
		if (AIMesh.mNumVertices <= TNumericLimits<UInt8>::max()) {
			ProcessMeshFaces<UInt8>(MeshData, AIScene, AIMesh);
		}
		else if (AIMesh.mNumVertices <= TNumericLimits<UInt16>::max()) {
			ProcessMeshFaces<UInt16>(MeshData, AIScene, AIMesh);
		}
		else {
			ProcessMeshFaces<UInt32>(MeshData, AIScene, AIMesh);
		}
	}

	// #FIXME: Process materials/textures.
}

template <class IndexT>
void FModelProcessorHelper::ProcessMeshFaces(
	FMeshData& MeshData,
	const aiScene& AIScene,
	const aiMesh& AIMesh) {
	static_assert(!TNumericLimits<IndexT>::is_signed, "IndexT must be unsigned.");
	static_assert(sizeof(IndexT) >= 1, "sizeof(IndexT) must be >= 1 byte.");
	static_assert(sizeof(IndexT) <= 4, "sizeof(IndexT) must be <= 4 bytes.");

	static const UInt8 IndicesPerFace = 3;

	const SizeT IndicesSize = AIMesh.mNumFaces * IndicesPerFace * sizeof(IndexT);

	MeshData.Indices.resize(IndicesSize);
	MeshData.IndexTSize = sizeof(IndexT);

	for (UInt32 I = 0; I < AIMesh.mNumFaces; I++) {
		const aiFace& AIFace = AIMesh.mFaces[I];

		F_Assert(AIFace.mNumIndices == IndicesPerFace, "Face data was not triangulated.");
		for (UInt8 J = 0; J < IndicesPerFace; ++J) {
			F_Assert(AIFace.mIndices[J] <= TNumericLimits<IndexT>::max(), "Index is out of bounds.");
			const SizeT IndicesI = I * IndicesPerFace * sizeof(IndexT) + J * sizeof(IndexT);

			IndexT* const IndexTPtr = reinterpret_cast<IndexT*>(&(MeshData.Indices[IndicesI]));
			*IndexTPtr = static_cast<IndexT>(AIFace.mIndices[J]);
		}
	}
}
