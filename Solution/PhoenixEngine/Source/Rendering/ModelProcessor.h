#ifndef PHOENIX_MODEL_PROCESSOR_H
#define PHOENIX_MODEL_PROCESSOR_H

#include "Utility/Containers/Vector.h"
#include "Utility/Misc/Primitives.h"
#include "Utility/Misc/String.h"
#include "Rendering/MeshData.h"
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

		FModelProcessor() = default;

		FModelProcessor(const FModelProcessor&) = default;
		FModelProcessor& operator=(const FModelProcessor&) = default;

		FModelProcessor(FModelProcessor&&) = default;
		FModelProcessor& operator=(FModelProcessor&&) = default;

		void Load(const FLoadParams& LoadParams);

		const FMeshData::FEntries& GetMeshDataEntries() const;

	private:
		FMeshData::FEntries MeshEntries;

		void LoadFBX(const FLoadParams& LoadParams);

		void LoadMisc(const FLoadParams& LoadParams);

		static bool IsFileFBX(const FString& File);

		static bool IsFileMisc(const FString& File);
	};
}

#endif
