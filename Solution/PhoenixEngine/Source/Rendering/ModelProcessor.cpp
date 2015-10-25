#include "Rendering/ModelProcessor.h"

#include "ExternalLib/AssimpIncludes.h"
#include "ExternalLib/FBXIncludes.h"
#include "Utility/Containers/Vector.h"
#include "Utility/Debug/Assert.h"
#include "Utility/Debug/Debug.h"
#include "Utility/FileIO/Endian.h"
#include "Utility/FileIO/FileStream.h"
#include "Utility/Misc/Memory.h"
#include "Rendering/MeshData.h"

// Note: This is required because some programmer 
// decided that defining max(a, b) was a good idea.
#undef max

namespace Phoenix
{
	struct FModelProcessorHelper
	{
		static const UInt8 FloatsPerVertex;
		static const UInt8 FloatsPerUVCoord;
		static const UInt8 IndicesPerFace;
		static const UInt8 UVCoordsPerTriangle;
		static const UInt8 VerticesPerTriangle;

		static const FChar* const GetAttributeTypeName(
			const FbxNodeAttribute::EType Type);

		static void ProcessMesh(
			FMeshData& MeshData,
			const aiScene& AIScene,
			const aiMesh& AIMesh);

		static void ProcessMesh(
			FMeshData& MeshData,
			fbxsdk::FbxMesh& FBXMesh);

		template <class IndexT>
		static void ProcessMeshFaces(
			FMeshData& MeshData,
			const aiScene& AIScene,
			const aiMesh& AIMesh);
	};
}

using namespace Phoenix;

const SizeT FModelProcessor::DefaultNodeCapacity = 32;
const SizeT FModelProcessor::DefaultMeshEntriesCapacity = 16;

const UInt8 FModelProcessorHelper::FloatsPerVertex = 3;
const UInt8 FModelProcessorHelper::FloatsPerUVCoord = 2;
const UInt8 FModelProcessorHelper::IndicesPerFace = 3;
const UInt8 FModelProcessorHelper::UVCoordsPerTriangle = 3;
const UInt8 FModelProcessorHelper::VerticesPerTriangle = 3;

void FModelProcessor::Load(const FLoadParams& LoadParams)
{
	F_Assert(LoadParams.File, "No file was specified.");
	F_Assert(LoadParams.MeshAttributeHints, "No hints were specified.");

	Unload();

	FLoadFunction const LoadFunction = GetLoadFunction(LoadParams);

	if (!LoadFunction)
	{
		return;
	}

	(this->*LoadFunction)(LoadParams);
}

void FModelProcessor::Save(const FSaveParams& SaveParams)
{
	// Note: This will be done at a later date.
	F_Assert(false, "This method is not implemented.");
}

void FModelProcessor::Unload()
{
	MeshEntries.clear();
}

const bool FModelProcessor::HasMeshDataEntries() const
{
	const bool Result = MeshEntries.size() != 0;
	return Result;
}

const FMeshData::FEntries& FModelProcessor::GetMeshDataEntries() const
{
	return MeshEntries;
}

FModelProcessor::FLoadFunction FModelProcessor::GetLoadFunction(const FLoadParams& LoadParams)
{
	const FString File = LoadParams.File;

	if (IsFilePhoenix(File))
	{
		return &FModelProcessor::LoadPhoenix;
	}

	if (IsFileFBX(File))
	{
		return &FModelProcessor::LoadFBX;
	}

	if (IsFileMisc(File))
	{
		return &FModelProcessor::LoadMisc;
	}

	F_LogError("Could not retrieve load function for " << File);
	return nullptr;
}

void FModelProcessor::LoadFBX(const FLoadParams& LoadParams)
{
	TRawPtr<FbxManager> FBXManager = FbxManager::Create();

	if (!FBXManager.IsValid())
	{
		F_LogError("FBX SDK is an evaluation copy and it has expired.  See FbxManager::Create().");
		return;
	}

	TRawPtr<FbxIOSettings> IOSettings = FbxIOSettings::Create(FBXManager.Get(), IOSROOT);
	IOSettings->SetBoolProp(IMP_FBX_MATERIAL, true);
	IOSettings->SetBoolProp(IMP_FBX_TEXTURE, true);
	IOSettings->SetBoolProp(IMP_FBX_LINK, false);
	IOSettings->SetBoolProp(IMP_FBX_SHAPE, false);
	IOSettings->SetBoolProp(IMP_FBX_GOBO, false);
	IOSettings->SetBoolProp(IMP_FBX_ANIMATION, true);
	IOSettings->SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);

	FBXManager->SetIOSettings(IOSettings.Get());

	TRawPtr<FbxImporter> FBXImporter = FbxImporter::Create(FBXManager.Get(), "Importer");

	if (!FBXImporter->Initialize(LoadParams.File, -1, FBXManager->GetIOSettings()))
	{
		F_LogError("Failed to load fbx model.  Error log: " << FBXImporter->GetStatus().GetErrorString());
		FBXManager->Destroy();
		FBXManager = nullptr;
		return;
	}

	TRawPtr<FbxScene> FBXScene = FbxScene::Create(FBXManager.Get(), "Scene");
	FBXImporter->Import(FBXScene.Get());
	FBXImporter->Destroy();
	FBXImporter = nullptr;

	TRawPtr<FbxNode> RootFBXNode = FBXScene->GetRootNode();
	TVector<TRawPtr<FbxNode>> FBXNodes;

	FBXNodes.reserve(FModelProcessor::DefaultNodeCapacity);

	if (RootFBXNode.IsValid())
	{
		FBXNodes.push_back(RootFBXNode.Get());
	}

	for (SizeT I = 0; I < FBXNodes.size(); ++I)
	{
		for (Int32 ChildI = 0; ChildI < FBXNodes[I]->GetChildCount(); ++ChildI)
		{
			F_Assert(FBXNodes[I]->GetChild(ChildI),
				"Node index " << I << " has null node at index " << ChildI << ".");

			FbxNode* const ChildNode = FBXNodes[I]->GetChild(ChildI);
			FBXNodes.push_back(ChildNode);
		}
	}

	F_Assert(MeshEntries.size() == 0, "Mesh entries were not cleared prior to this operation.");
	MeshEntries.reserve(FModelProcessor::DefaultMeshEntriesCapacity);

	for (SizeT I = 0; I < FBXNodes.size(); ++I)
	{
		FbxNode& FBXNode = *FBXNodes[I];

		for (Int32 AttribI = 0; AttribI < FBXNode.GetNodeAttributeCount(); ++AttribI)
		{
			TRawPtr<FbxNodeAttribute> FBXNodeAttribute = FBXNode.GetNodeAttributeByIndex(AttribI);
			const FbxNodeAttribute::EType NodeAttributeType = FBXNodeAttribute->GetAttributeType();

			switch (NodeAttributeType)
			{
				case FbxNodeAttribute::eMesh:
				{
					{
						FMeshData MeshData;
						MeshData.MeshAttrib = LoadParams.MeshAttributeHints;

						MeshEntries.push_back(std::move(MeshData));
					}

					{
						const SizeT MeshEntryIndex = MeshEntries.size() - 1;
						FMeshData& MeshData = MeshEntries[MeshEntryIndex];

						TRawPtr<FbxMesh> FBXMesh = static_cast<FbxMesh*>(FBXNodeAttribute.Get());
						FModelProcessorHelper::ProcessMesh(MeshData, *FBXMesh);

						if (MeshData.MeshAttrib == EMeshAttribute::None)
						{
							F_LogError("Mesh entry initialization failed.");
							MeshEntries.pop_back();
						}
					}
					break;
				}
			}
		}
	}

	FBXManager->Destroy();
	FBXManager = nullptr;
}

void FModelProcessor::LoadMisc(const FLoadParams& LoadParams)
{
	F_Assert(LoadParams.File, "File was not specified.");
	F_Assert(LoadParams.MeshAttributeHints, "Mesh attribute hints were not specified.");

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

	AINodes.reserve(FModelProcessor::DefaultNodeCapacity);
	AINodes.push_back(AISceneRef.mRootNode);

	for (SizeT I = 0; I < AINodes.size(); ++I)
	{
		for (UInt32 ChildI = 0; ChildI < AINodes[I]->mNumChildren; ++ChildI)
		{
			F_Assert(AINodes[I]->mChildren[ChildI],
				"Node index " << I << " has null mesh at index " << ChildI << ".");

			const aiNode* const ChildNode = AINodes[I]->mChildren[ChildI];
			AINodes.push_back(ChildNode);
		}
	}

	F_Assert(MeshEntries.size() == 0, "Mesh entries were not cleared prior to this operation.");
	MeshEntries.reserve(FModelProcessor::DefaultMeshEntriesCapacity);

	const SizeT AINodesSize = AINodes.size();
	for (SizeT I = 0; I < AINodesSize; ++I)
	{
		for (UInt32 MeshI = 0; MeshI < AINodes[I]->mNumMeshes; ++MeshI)
		{
			{
				FMeshData MeshData;
				MeshData.MeshAttrib = LoadParams.MeshAttributeHints;

				MeshEntries.push_back(std::move(MeshData));
			}

			{
				const UInt32 Handle = AINodes[I]->mMeshes[MeshI];
				F_Assert(Handle < AISceneRef.mNumMeshes,
					"Index " << Handle << " is out of range of " << AISceneRef.mNumMeshes);

				const SizeT MeshEntryIndex = MeshEntries.size() - 1;
				FMeshData& MeshData = MeshEntries[MeshEntryIndex];

				const aiMesh& AIMesh = *AISceneRef.mMeshes[Handle];
				FModelProcessorHelper::ProcessMesh(MeshData, AISceneRef, AIMesh);

				if (MeshData.MeshAttrib == EMeshAttribute::None)
				{
					F_LogError("Mesh entry initialization failed.");
					MeshEntries.pop_back();
				}
			}
		}
	}

	F_LogTrace("Model created from " << LoadParams.File);
}

void FModelProcessor::LoadPhoenix(const FLoadParams& LoadParams)
{
	// Note: This will be done at a later date.
	F_Assert(false, "This method is not yet implemented.");
}

bool FModelProcessor::IsFileFBX(const FString& File)
{
	F_Assert(File.size(), "Invalid file name.");

	FString Extension = NString::ExtractExtension(File);
	NString::ToLower(Extension);

	const bool Result = Extension == "fbx";
	return Result;
}

bool FModelProcessor::IsFileMisc(const FString& File)
{
	F_Assert(File.size(), "Invalid file name.");

	const bool Result = !(IsFileFBX(File) || IsFilePhoenix(File));
	return Result;
}

bool FModelProcessor::IsFilePhoenix(const FString& File)
{
	F_Assert(File.size(), "Invalid file name.");

	FString Extension = NString::ExtractExtension(File);
	NString::ToLower(Extension);

	const bool Result = Extension == "pmesh";
	return Result;
}

const FChar* const FModelProcessorHelper::GetAttributeTypeName(
	const FbxNodeAttribute::EType Type)
{
	switch (Type)
	{
		case FbxNodeAttribute::eUnknown: return "unidentified";
		case FbxNodeAttribute::eNull: return "null";
		case FbxNodeAttribute::eMarker: return "marker";
		case FbxNodeAttribute::eSkeleton: return "skeleton";
		case FbxNodeAttribute::eMesh: return "mesh";
		case FbxNodeAttribute::eNurbs: return "nurbs";
		case FbxNodeAttribute::ePatch: return "patch";
		case FbxNodeAttribute::eCamera: return "camera";
		case FbxNodeAttribute::eCameraStereo: return "stereo";
		case FbxNodeAttribute::eCameraSwitcher: return "camera switcher";
		case FbxNodeAttribute::eLight: return "light";
		case FbxNodeAttribute::eOpticalReference: return "optical reference";
		case FbxNodeAttribute::eOpticalMarker: return "marker";
		case FbxNodeAttribute::eNurbsCurve: return "nurbs curve";
		case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface";
		case FbxNodeAttribute::eBoundary: return "boundary";
		case FbxNodeAttribute::eNurbsSurface: return "nurbs surface";
		case FbxNodeAttribute::eShape: return "shape";
		case FbxNodeAttribute::eLODGroup: return "lodgroup";
		case FbxNodeAttribute::eSubDiv: return "subdiv";
	}

	return "unknown";
}

void FModelProcessorHelper::ProcessMesh(
	FMeshData& MeshData,
	const aiScene& AIScene,
	const aiMesh& AIMesh)
{
	F_Assert(MeshData.MeshAttrib, "No model data hints were requested.");
	// #FIXME: Compress the code.

	const bool PositionHintIsSet = (MeshData.MeshAttrib & EMeshAttribute::Positions) != 0;
	const bool NormalsHintIsSet = (MeshData.MeshAttrib & EMeshAttribute::Normals) != 0;
	const bool IndicesHintIsSet = (MeshData.MeshAttrib & EMeshAttribute::Indices) != 0;
	const bool UVCoordsHintIsSet = (MeshData.MeshAttrib & EMeshAttribute::UVCoords) != 0;

	const bool HasVertexData = AIMesh.mNumVertices > 0;
	const bool HasIndexData = AIMesh.mNumFaces > 0;
	const bool HasUVCoords = AIMesh.mTextureCoords[0] != nullptr;

	if (!HasVertexData || !HasIndexData)
	{
		F_LogError("This mesh does not have any vertex and/or index data.");
		MeshData.MeshAttrib = EMeshAttribute::None;
		return;
	}

	if (IndicesHintIsSet && !HasIndexData)
	{
		F_LogWarning("Indices were specified but this mesh does not have any.");
		MeshData.MeshAttrib &= ~EMeshAttribute::Indices;
	}

	if (UVCoordsHintIsSet && !HasUVCoords)
	{
		F_LogWarning("UVCoords were specified but this mesh does not have any.");
		MeshData.MeshAttrib &= ~EMeshAttribute::UVCoords;
	}

	if (PositionHintIsSet && HasVertexData)
	{
		const SizeT PositionsArraySize = AIMesh.mNumVertices * FModelProcessorHelper::FloatsPerVertex;
		MeshData.Positions.resize(PositionsArraySize);

		for (UInt32 I = 0; I < AIMesh.mNumVertices; ++I)
		{
			const SizeT Stride = I * FModelProcessorHelper::FloatsPerVertex;

			const SizeT X = Stride;
			const SizeT Y = Stride + 1;
			const SizeT Z = Stride + 2;

			MeshData.Positions[X] = AIMesh.mVertices[I].x;
			MeshData.Positions[Y] = AIMesh.mVertices[I].y;
			MeshData.Positions[Z] = AIMesh.mVertices[I].z;
		}

		MeshData.VertexCount = AIMesh.mNumVertices;
	}

	if (NormalsHintIsSet && HasVertexData)
	{
		const SizeT NormalsArraySize = AIMesh.mNumVertices * FModelProcessorHelper::FloatsPerVertex;
		MeshData.Normals.resize(NormalsArraySize);

		for (UInt32 I = 0; I < AIMesh.mNumVertices; ++I)
		{
			const SizeT Stride = I * FModelProcessorHelper::FloatsPerVertex;

			const SizeT X = Stride;
			const SizeT Y = Stride + 1;
			const SizeT Z = Stride + 2;

			MeshData.Normals[X] = AIMesh.mNormals[I].x;
			MeshData.Normals[Y] = AIMesh.mNormals[I].y;
			MeshData.Normals[Z] = AIMesh.mNormals[I].z;
		}
	}

	if (UVCoordsHintIsSet && HasUVCoords)
	{
		const SizeT UVCoordsArraySize = AIMesh.mNumVertices * FModelProcessorHelper::FloatsPerUVCoord;
		MeshData.UVCoords.resize(UVCoordsArraySize);

		for (UInt32 I = 0; I < AIMesh.mNumVertices; ++I)
		{
			const SizeT Stride = I * FModelProcessorHelper::FloatsPerUVCoord;

			const SizeT X = Stride;
			const SizeT Y = Stride + 1;

			MeshData.UVCoords[X] = AIMesh.mTextureCoords[0][I].x;
			MeshData.UVCoords[Y] = AIMesh.mTextureCoords[0][I].y;
		}
	}

	if (IndicesHintIsSet && HasIndexData)
	{
		if (AIMesh.mNumVertices <= TNumericLimits<UInt8>::max())
		{
			ProcessMeshFaces<UInt8>(MeshData, AIScene, AIMesh);
		}
		else if (AIMesh.mNumVertices <= TNumericLimits<UInt16>::max())
		{
			ProcessMeshFaces<UInt16>(MeshData, AIScene, AIMesh);
		}
		else
		{
			ProcessMeshFaces<UInt32>(MeshData, AIScene, AIMesh);
		}
	}

	// #FIXME: Process materials/textures.
}

void FModelProcessorHelper::ProcessMesh(
	FMeshData& MeshData,
	FbxMesh& FBXMesh)
{
	F_Assert(MeshData.MeshAttrib, "No model data hints were requested.");
	// #FIXME: Compress the code.

	const bool PositionHintIsSet = (MeshData.MeshAttrib & EMeshAttribute::Positions) != 0;
	const bool NormalsHintIsSet = (MeshData.MeshAttrib & EMeshAttribute::Normals) != 0;
	const bool IndicesHintIsSet = (MeshData.MeshAttrib & EMeshAttribute::Indices) != 0;
	const bool UVCoordsHintIsSet = (MeshData.MeshAttrib & EMeshAttribute::UVCoords) != 0;

	const Int32 ControlPointsCount = FBXMesh.GetControlPointsCount();
	const Int32 TriangleCount = FBXMesh.GetPolygonCount();
	const Int32 VertexCount = TriangleCount * FModelProcessorHelper::VerticesPerTriangle;

	const SizeT PositionsArraySize = VertexCount * FModelProcessorHelper::FloatsPerVertex;
	const SizeT UVCoordsArraySize = VertexCount * FModelProcessorHelper::FloatsPerUVCoord;

	const bool HasVertexData = ControlPointsCount > 0 && TriangleCount > 0;

	if (!HasVertexData)
	{
		F_LogError("The provided FBXMesh does not have any vertex data.");
		MeshData.MeshAttrib = EMeshAttribute::None;
		return;
	}

	if (PositionHintIsSet)
	{
		MeshData.Positions.resize(PositionsArraySize);

		for (Int32 I = 0; I < TriangleCount; ++I)
		{
			F_Assert(FBXMesh.GetPolygonSize(I) == FModelProcessorHelper::FloatsPerVertex,
				"Three vertices are required for a triangle.");

			const SizeT Stride =
				I * FModelProcessorHelper::VerticesPerTriangle * FModelProcessorHelper::FloatsPerVertex;
			
			for (Int32 J = 0; J < FModelProcessorHelper::FloatsPerVertex; ++J)
			{
				const SizeT Offset = J * FModelProcessorHelper::FloatsPerVertex;
				const SizeT StrideOffsetSum = Stride + Offset;

				const SizeT X = StrideOffsetSum;
				const SizeT Y = StrideOffsetSum + 1;
				const SizeT Z = StrideOffsetSum + 2;

				const Int32 Index = FBXMesh.GetPolygonVertex(I, J);
				F_Assert(Index >= 0 && Index < ControlPointsCount, "Index is out of bounds.");

				MeshData.Positions[X] = static_cast<FMeshData::PositionT>(FBXMesh.mControlPoints[Index][0]);
				MeshData.Positions[Y] = static_cast<FMeshData::PositionT>(FBXMesh.mControlPoints[Index][1]);
				MeshData.Positions[Z] = static_cast<FMeshData::PositionT>(FBXMesh.mControlPoints[Index][2]);
			}
		}

		MeshData.VertexCount = VertexCount;
	}

	if (NormalsHintIsSet)
	{
		MeshData.Normals.resize(PositionsArraySize);

		for (Int32 I = 0; I < TriangleCount; ++I)
		{
			F_Assert(FBXMesh.GetPolygonSize(I) == FModelProcessorHelper::FloatsPerVertex,
				"Three vertices are required for a triangle.");

			const SizeT Stride =
				I * FModelProcessorHelper::VerticesPerTriangle * FModelProcessorHelper::FloatsPerVertex;

			for (Int32 J = 0; J < FModelProcessorHelper::FloatsPerVertex; ++J)
			{
				const SizeT Offset = J * FModelProcessorHelper::FloatsPerVertex;
				const SizeT StrideOffsetSum = Stride + Offset;

				const SizeT X = StrideOffsetSum;
				const SizeT Y = StrideOffsetSum + 1;
				const SizeT Z = StrideOffsetSum + 2;

				FbxVector4 Normal;
				const bool bIsNormalRetrieved = FBXMesh.GetPolygonVertexNormal(I, J, Normal);
				F_Assert(bIsNormalRetrieved, "Failed to retrieve normal.");

				MeshData.Normals[X] = static_cast<FMeshData::NormalT>(Normal[0]);
				MeshData.Normals[Y] = static_cast<FMeshData::NormalT>(Normal[1]);
				MeshData.Normals[Z] = static_cast<FMeshData::NormalT>(Normal[2]);
			}
		}
	}

	if (UVCoordsHintIsSet)
	{
		TRawPtr<FbxLayerElementArrayTemplate<FbxVector2>> UVCoordsArray = nullptr;
		FBXMesh.GetTextureUV(&UVCoordsArray.Get(), FbxLayerElement::eTextureDiffuse);
		MeshData.UVCoords.resize(UVCoordsArraySize);

		if (!UVCoordsArray.IsValid())
		{
			F_LogWarning("Failed to get UV coordinates for a mesh.");
			std::fill(MeshData.UVCoords.begin(), MeshData.UVCoords.end(), 0.f);
		}
		else
		{
			for (Int32 I = 0; I < TriangleCount; ++I)
			{
				F_Assert(FBXMesh.GetPolygonSize(I) == FModelProcessorHelper::FloatsPerVertex,
					"Three vertices are required for a triangle.");

				const SizeT Stride =
					I * FModelProcessorHelper::VerticesPerTriangle * FModelProcessorHelper::FloatsPerUVCoord;

				for (Int32 J = 0; J < FModelProcessorHelper::FloatsPerVertex; ++J)
				{
					const SizeT Offset = J * FModelProcessorHelper::FloatsPerUVCoord;
					const SizeT StrideOffsetSum = Stride + Offset;

					const SizeT X = StrideOffsetSum;
					const SizeT Y = StrideOffsetSum + 1;

					const Int32 Index = FBXMesh.GetTextureUVIndex(I, J);
					F_Assert(Index >= 0 && Index < UVCoordsArray->GetCount(), "Index is out of bounds.");

					FbxVector2 UVCoord = UVCoordsArray->GetAt(Index);

					MeshData.UVCoords[X] = static_cast<FMeshData::UVCoordT>(UVCoord[0]);
					MeshData.UVCoords[Y] = static_cast<FMeshData::UVCoordT>(UVCoord[1]);
				}
			}
		}
	}

	if (IndicesHintIsSet)
	{
		// #FIXME: The FBX SDK doesn't seem to expose
		// index data for all of the types, so eventually,
		// duplicate data will have to be removed and indices
		// will have to be generated accordingly, and then
		// the indices will have to be sorted appropriately
		// for later.
		typedef UInt32 IndexDataTypeT;

		const UInt32 VertexCountUInt32 = static_cast<UInt32>(VertexCount);
		const SizeT IndexArraySize = VertexCountUInt32 * sizeof(IndexDataTypeT);

		MeshData.Indices.resize(IndexArraySize);
		MeshData.IndexTSize = sizeof(IndexDataTypeT);

		for (SizeT I = 0; I < VertexCountUInt32; ++I)
		{
			const SizeT IndicesI = I * sizeof(IndexDataTypeT);

			FMeshData::IndexT* const IndexTPtr = &(MeshData.Indices[IndicesI]);
			IndexDataTypeT* const IndexDataTypeTPtr = reinterpret_cast<IndexDataTypeT*>(IndexTPtr);

			*IndexDataTypeTPtr = static_cast<IndexDataTypeT>(I);
		}
	}

	UInt32* Indices = reinterpret_cast<UInt32*>(&MeshData.Indices[0]);

	// #FIXME: Process materials/textures
}

template <class IndexT>
void FModelProcessorHelper::ProcessMeshFaces(
	FMeshData& MeshData,
	const aiScene& AIScene,
	const aiMesh& AIMesh)
{
	static_assert(!TNumericLimits<IndexT>::is_signed, "IndexT must be unsigned.");
	static_assert(sizeof(IndexT) >= 1, "sizeof(IndexT) must be >= 1 byte.");
	static_assert(sizeof(IndexT) <= 4, "sizeof(IndexT) must be <= 4 bytes.");

	const SizeT IndicesSize = AIMesh.mNumFaces * FModelProcessorHelper::IndicesPerFace * sizeof(IndexT);

	MeshData.Indices.resize(IndicesSize);
	MeshData.IndexTSize = sizeof(IndexT);

	for (UInt32 I = 0; I < AIMesh.mNumFaces; I++)
	{
		const aiFace& AIFace = AIMesh.mFaces[I];

		F_Assert(AIFace.mNumIndices == IndicesPerFace, "Face data was not triangulated.");
		for (UInt8 J = 0; J < FModelProcessorHelper::IndicesPerFace; ++J)
		{
			F_Assert(AIFace.mIndices[J] <= TNumericLimits<IndexT>::max(), "Index is out of bounds.");
			const SizeT IndicesI = I * FModelProcessorHelper::IndicesPerFace * sizeof(IndexT) + J * sizeof(IndexT);

			UInt8* const UInt8Ptr = &(MeshData.Indices[IndicesI]);
			IndexT* const IndexTPtr = reinterpret_cast<IndexT*>(UInt8Ptr);

			*IndexTPtr = static_cast<IndexT>(AIFace.mIndices[J]);
		}
	}
}
