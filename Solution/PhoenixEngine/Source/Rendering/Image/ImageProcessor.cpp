#include "Rendering/Image/ImageProcessor.h"

#include "ExternalLib/SOILIncludes.h"
#include "Utility/Containers/Array.h"
#include "Utility/Debug/Assert.h"
#include "Utility/Debug/Debug.h"

using namespace Phoenix;

const FImageData::WidthT FImageProcessor::MaxWidth = 1 << 14;
const FImageData::HeightT FImageProcessor::MaxHeight = 1 << 14;

static_assert(sizeof(FImageData::WidthT) >= 2, "This constant expects a type that has 2 or more bytes.");
static_assert(sizeof(FImageData::HeightT) >= 2, "This constant expects a type that has 2 or more bytes.");

namespace Phoenix
{
	struct FImageProcessorHelper
	{
		static inline int ToForceChannels(const EPixelFormat::Value ImageLayout)
		{
			static_assert(SOIL_LOAD_AUTO == EPixelFormat::Unknown, "This table requires updating.");
			static_assert(SOIL_LOAD_L == EPixelFormat::Luminous, "This table requires updating.");
			static_assert(SOIL_LOAD_LA == EPixelFormat::LuminousAlpha, "This table requires updating.");
			static_assert(SOIL_LOAD_RGB == EPixelFormat::RGB, "This table requires updating.");
			static_assert(SOIL_LOAD_RGBA == EPixelFormat::RGBA, "This table requires updating.");

			static const UInt8 ArraySize = 5;
			static const TArray<int, ArraySize> LookUpTable = {
				SOIL_LOAD_AUTO,
				SOIL_LOAD_L,
				SOIL_LOAD_LA,
				SOIL_LOAD_RGB,
				SOIL_LOAD_RGBA
			};

			return LookUpTable[ImageLayout];
		}

		static inline EPixelFormat::Value ToImageLayout(const int ForceChannels)
		{
			F_Assert(ForceChannels > 0, "ForceChannels must be greater than 0.");
			F_Assert(ForceChannels <= 4, "ForceChannels must be less than or equal to 4.");
			const EPixelFormat::Value ImageLayout = static_cast<EPixelFormat::Value>(ForceChannels);
			return ImageLayout;
		}
	};
}

FImageProcessor::~FImageProcessor()
{
	Unload();
}

FImageProcessor::FImageProcessor(FImageProcessor&& RHS)
	: Data(RHS.Data)
{
	RHS.PostMoveReset();
}

FImageProcessor& FImageProcessor::operator=(FImageProcessor&& RHS)
{
	F_Assert(this != &RHS, "Self assignment is illegal.");

	Data = RHS.Data;

	RHS.PostMoveReset();
	return *this;
}

void FImageProcessor::Load(const FLoadParams& LoadParams)
{
	F_Assert(LoadParams.File, "File must be specified.");
	F_Assert(LoadParams.ImageLayout != EPixelFormat::Unknown, "ImageLayout must be specified.");

	Unload();

	int ImageWidth = 0;
	int ImageHeight = 0;
	int ImageChannels = 0;
	const int ForceChannels = FImageProcessorHelper::ToForceChannels(LoadParams.ImageLayout);

	Data.Pixels = SOIL_load_image(
		LoadParams.File,
		&ImageWidth,
		&ImageHeight,
		&ImageChannels,
		ForceChannels);

	if (!Data.Pixels)
	{
		F_LogError("Failed to load file " << LoadParams.File << ".  " << SOIL_last_result());
		Unload();
		return;
	}

	{
		const bool ReturnParamsAreValid =
			ImageWidth > 0 && ImageWidth < MaxWidth &&
			ImageHeight > 0 && ImageHeight < MaxHeight &&
			ImageChannels > 0;

		F_Assert(ReturnParamsAreValid, "One or more return parameter is invalid.");
	}

	Data.Width = static_cast<FImageData::WidthT>(ImageWidth);
	Data.Height = static_cast<FImageData::HeightT>(ImageHeight);
	Data.PixelFormat = FImageProcessorHelper::ToImageLayout(ForceChannels);

	F_LogTrace(
		"Created image from " << LoadParams.File
		<< ", W: " << Data.Width
		<< " H: " << Data.Height
		<< ", Ch: " << ImageChannels
		<< ", ForceCh: " << ForceChannels);
}

bool FImageProcessor::IsValid() const
{
	const bool Result = Data.Pixels != nullptr;
	return Result;
}

void FImageProcessor::Unload()
{
	if (Data.Pixels)
	{
		SOIL_free_image_data(Data.Pixels);
		Data.Pixels = nullptr;
	}

	Data.PixelFormat = EPixelFormat::Unknown;
	Data.Width = 0;
	Data.Height = 0;
}

const FImageData& FImageProcessor::GetImageData() const
{
	return Data;
}

const FImageData::PixelsT FImageProcessor::GetPixels() const
{
	return Data.Pixels;
}

FImageData::PixelCountT FImageProcessor::GetPixelCount() const
{
	const UInt32 PixelCount = Data.Width * Data.Height * Data.PixelFormat;
	return PixelCount;
}

EPixelFormat::Value FImageProcessor::GetPixelFormat() const
{
	return Data.PixelFormat;
}

FImageData::WidthT FImageProcessor::GetWidth() const
{
	return Data.Width;
}

FImageData::HeightT FImageProcessor::GetHeight() const
{
	return Data.Height;
}

void FImageProcessor::PostMoveReset()
{
	Data = FImageData();
}
