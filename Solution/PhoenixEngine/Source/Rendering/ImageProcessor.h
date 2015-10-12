#ifndef PHOENIX_IMAGE_PROCESSOR_H
#define PHOENIX_IMAGE_PROCESSOR_H

#include "Utility/Misc/Primitives.h"
#include "Rendering/ImageData.h"

namespace Phoenix {
	class FImageProcessor {
		friend struct FImageProcessorHelper;
	public:
		struct FLoadParams {
			const FChar* File{ nullptr };
			EPixelFormat::Value ImageLayout{ EPixelFormat::Unknown };
		};

		FImageProcessor() = default;
		~FImageProcessor();

		FImageProcessor(const FImageProcessor&) = delete;
		FImageProcessor& operator=(const FImageProcessor&) = delete;

		FImageProcessor(FImageProcessor&&);
		FImageProcessor& operator=(FImageProcessor&&);

		void Load(const FLoadParams& LoadParams);

		bool IsValid() const;

		void Unload();

		const FImageData& GetImageData() const;

		const UInt8* GetPixels() const;

		UInt32 GetPixelCount() const;

		EPixelFormat::Value GetPixelFormat() const;

		UInt16 GetWidth() const;

		UInt16 GetHeight() const;

	private:
		static const UInt16 MaxWidth;
		static const UInt16 MaxHeight;

		FImageData Data;

		void PostMoveReset();
	};
}

#endif
