#ifndef PHOENIX_MODEL_PROCESSOR_H
#define PHOENIX_MODEL_PROCESSOR_H

#include "Utility/Containers/Vector.h"
#include "Utility/Misc/Primitives.h"
#include "Utility/Misc/String.h"
#include "Rendering/MeshData.h"

namespace Phoenix
{
	class FModelProcessor
	{
		friend struct FModelProcessorHelper;
	public:
		struct FLoadParams
		{
			const FChar* File{ nullptr };
			EMeshAttribute::Type MeshAttributeHints{ EMeshAttribute::None };
		};

		struct FSaveParams
		{
			const FChar* File{ nullptr };
		};

		FModelProcessor() = default;

		FModelProcessor(const FModelProcessor&) = default;
		FModelProcessor& operator=(const FModelProcessor&) = default;

		FModelProcessor(FModelProcessor&&) = default;
		FModelProcessor& operator=(FModelProcessor&&) = default;

		void Load(const FLoadParams& LoadParams);

		void Save(const FSaveParams& SaveParams);

		void Unload();

		const bool HasMeshDataEntries() const;

		const FMeshData::FEntries& GetMeshDataEntries() const;

	private:
		static const SizeT DefaultNodeCapacity;
		static const SizeT DefaultMeshEntriesCapacity;

		typedef void(FModelProcessor::*FLoadFunction)(const FLoadParams& LoadParams);

		FMeshData::FEntries MeshEntries;

		static FLoadFunction GetLoadFunction(const FLoadParams& LoadParams);

		void LoadFBX(const FLoadParams& LoadParams);

		void LoadMisc(const FLoadParams& LoadParams);

		void LoadPhoenix(const FLoadParams& LoadParams);

		static bool IsFileFBX(const FString& File);

		static bool IsFileMisc(const FString& File);

		static bool IsFilePhoenix(const FString& File);
	};
}

#endif
