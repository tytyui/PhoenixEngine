#include "Rendering/ModelProcessor.h"

#include "ExternalLib/AssimpIncludes.h"
#include "ExternalLib/FBXIncludes.h"
#include "Utility/Containers/Vector.h"
#include "Utility/Debug/Assert.h"
#include "Utility/Debug/Debug.h"

using namespace Phoenix;

void FModelProcessor::Load(const FLoadParams& LoadParams)
{
	F_Assert(LoadParams.File.size(), "No file was specified.");
	F_Assert(LoadParams.ModelDataHints, "No hints were specified.");

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

void FModelProcessor::Save(const FSaveParams& SaveParams)
{
	F_Assert(SaveParams.File.size(), "No file was specified.");

	// #FIXME
}

const TVector<Float32>& FModelProcessor::GetPositions() const
{
	return Positions;
}

const TVector<Float32>& FModelProcessor::GetNormals() const
{
	return Normals;
}

const TVector<Float32>& FModelProcessor::GetUVCoords() const
{
	return UVCoords;
}

bool FModelProcessor::HasPositions() const
{
	const bool Result = (ModelData & EModelData::Positions) == EModelData::Positions;
	return Result;
}

bool FModelProcessor::HasNormals() const
{
	const bool Result = (ModelData & EModelData::Normals) == EModelData::Normals;
	return Result;
}

bool FModelProcessor::HasUVCoords() const
{
	const bool Result = (ModelData & EModelData::UVCoords) == EModelData::UVCoords;
	return Result;
}

void FModelProcessor::LoadFBX(const FLoadParams& LoadParams)
{
	// #FIXME
}

void FModelProcessor::LoadMisc(const FLoadParams& LoadParams)
{
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

	static const SizeT DefaultCapacity = 64;
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

	const SizeT AINodesSize = AINodes.size();
	for (SizeT I = 0; I < AINodesSize; ++I)
	{
		for (UInt32 MeshI = 0; MeshI < AINodes[I]->mNumMeshes; ++MeshI)
		{
			const UInt32 Handle = AINodes[I]->mMeshes[MeshI];
			F_Assert(Handle < AISceneRef.mNumMeshes, "Index " << Handle << " is out of range of " << AISceneRef.mNumMeshes);
			const aiMesh& AIMesh = *AISceneRef.mMeshes[Handle];

			// #FIXME: Process mesh.
		}
	}

	// #FIXME
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
