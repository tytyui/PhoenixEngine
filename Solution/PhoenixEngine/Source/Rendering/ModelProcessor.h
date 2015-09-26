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

		FModelProcessor() = default;

		FModelProcessor(const FModelProcessor&) = delete;
		FModelProcessor& operator=(const FModelProcessor&) = delete;

		FModelProcessor(FModelProcessor&&) = delete;
		FModelProcessor& operator=(FModelProcessor&&) = delete;

		void Load(const FLoadParams& LoadParams);

		void Save(const FSaveParams& SaveParams);
		
		const TVector<Float32>& GetPositions() const;

		const TVector<Float32>& GetNormals() const;

		const TVector<Float32>& GetUVCoords() const;

		bool HasPositions() const;

		bool HasNormals() const;

		bool HasUVCoords() const;

	private:
		EModelData::BitMask ModelData{ EModelData::None };
		TVector<Float32> Positions;
		TVector<Float32> Normals;
		TVector<Float32> UVCoords;

		void LoadFBX(const FLoadParams& LoadParams);

		void LoadMisc(const FLoadParams& LoadParams);

		static bool IsFileFBX(const FString& File);

		static bool IsFileMisc(const FString& File);
	};
}

#endif
