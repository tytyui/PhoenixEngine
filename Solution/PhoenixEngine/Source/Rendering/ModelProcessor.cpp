#include "Rendering/ModelProcessor.h"

#include "ExternalLib/AssimpIncludes.h"
#include "ExternalLib/FBXIncludes.h"
#include "Utility/Debug/Assert.h"

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
	// #FIXME
}

bool FModelProcessor::IsFileFBX(const FString& File)
{
	F_Assert(File.size(), "");

	// #FIXME: Use a "HasExtension" method instead.
	FString Extension = FStr::ExtractExtension(File);
	FStr::ToLower(Extension);
	
	const bool IsFBX = Extension == "fbx";
	return IsFBX;
}

bool FModelProcessor::IsFileMisc(const FString& File)
{
	// Note: Currently, if a file isn't an FBX 
	// file, the misc loader should be used.
	const bool IsFBX = IsFileFBX(File);

	const bool IsMisc = !IsFBX;
	
	return IsMisc;
}