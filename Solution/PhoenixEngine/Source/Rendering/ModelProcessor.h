#ifndef PHOENIX_MODEL_PROCESSOR_H
#define PHOENIX_MODEL_PROCESSOR_H

#include "Utility/Containers/Vector.h"
#include "Utility/Misc/Primitives.h"
#include "Utility/Misc/String.h"
#include "Rendering/ModelData.h"

namespace Phoenix
{
	class FModelProcessor
	{
		friend struct FModelProcessorHelper;
	public:
		struct FLoadParams
		{
			FString File;
			EModelData::Type ModelDataHints{ EModelData::None };
		};

		struct FSaveParams
		{
			FString File;
		};

		struct FDataEntry
		{
			EModelData::Type ModelData{ EModelData::None };
			TVector<Float32> Positions;
			TVector<Float32> Normals;
			TVector<Float32> UVCoords;
			TVector<UInt8> Indices;
			UInt8 IndexTSize{ 0 };
		};

		typedef TVector<FDataEntry> FDataEntries;

		FModelProcessor() = default;

		FModelProcessor(const FModelProcessor&) = default;
		FModelProcessor& operator=(const FModelProcessor&) = default;

		FModelProcessor(FModelProcessor&&) = default;
		FModelProcessor& operator=(FModelProcessor&&) = default;

		void Load(const FLoadParams& LoadParams);

		FDataEntries& GetDataEntries();

	private:
		FDataEntries DataEntries;

		void LoadFBX(const FLoadParams& LoadParams);

		void LoadMisc(const FLoadParams& LoadParams);

		static bool IsFileFBX(const FString& File);

		static bool IsFileMisc(const FString& File);
	};
}

#endif
