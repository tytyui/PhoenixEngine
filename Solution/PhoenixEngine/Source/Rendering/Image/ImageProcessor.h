#ifndef PHOENIX_IMAGE_PROCESSOR_H
#define PHOENIX_IMAGE_PROCESSOR_H

#include "Utility/Misc/Primitives.h"
#include "Rendering/Image/ImageData.h"

namespace Phoenix
{
	class FImageProcessor
	{
		friend struct FImageProcessorHelper;
	public:
		struct FLoadParams
		{
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

		const FImageData::PixelsT GetPixels() const;

		FImageData::PixelCountT GetPixelCount() const;

		EPixelFormat::Value GetPixelFormat() const;

		FImageData::WidthT GetWidth() const;

		FImageData::HeightT GetHeight() const;

	private:
		static const FImageData::WidthT MaxWidth;
		static const FImageData::HeightT MaxHeight;

		FImageData Data;

		void PostMoveReset();
	};
}

#endif
