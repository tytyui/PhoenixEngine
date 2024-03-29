#include "Rendering/Image/Image.h"

#include "Utility/Containers/Array.h"
#include "Rendering/GLInterface.h"

using namespace Phoenix;
using namespace Phoenix::GL;

namespace Phoenix
{
	struct FImageHelper
	{
		static inline ETexGLFormat::Value ToGLTexFormat(const EPixelFormat::Value PixelFormat)
		{
			static_assert(EPixelFormat::Count == 5, "This table requires updating.");
			static const TArray<ETexGLFormat::Value, EPixelFormat::Count> LookUpTable = {
				/* Unknown			*/ETexGLFormat::Red,
				/* Luminous			*/ETexGLFormat::Red, // #FIXME: This requires correctness verification.
				/* LuminousAlpha	*/ETexGLFormat::RG, // #FIXME: This requires correctness verification.
				/* RGB				*/ETexGLFormat::RGB,
				/* RGBA				*/ETexGLFormat::RGBA
			};

			return LookUpTable[PixelFormat];
		}

		static inline ETexFormat::Value ToTexFormat(const EPixelFormat::Value PixelFormat)
		{
			static_assert(EPixelFormat::Count == 5, "This table requires updating.");
			static const TArray<ETexFormat::Value, EPixelFormat::Count> LookUpTable = {
				/* Unknown			*/ETexFormat::Red,
				/* Luminous			*/ETexFormat::Red, // #FIXME: This requires correctness verification.
				/* LuminousAlpha	*/ETexFormat::RG, // #FIXME: This requires correctness verification.
				/* RGB				*/ETexFormat::RGB,
				/* RGBA				*/ETexFormat::RGBA
			};

			return LookUpTable[PixelFormat];
		}
	};
}

FImage::FImage(FImage&& RHS)
	: ID(RHS.ID)
	, PixelFormat(RHS.PixelFormat)
	, Width(RHS.Width)
	, Height(RHS.Height)
{
	RHS.PostMoveReset();
}

FImage& FImage::operator=(FImage&& RHS)
{
	if (this == &RHS)
	{
		return *this;
	}

	ID = RHS.ID;
	PixelFormat = RHS.PixelFormat;
	Width = RHS.Width;
	Height = RHS.Height;

	RHS.PostMoveReset();
	return *this;
}

void FImage::Init(const FInitParams& InitParams)
{
	F_Assert(InitParams.ImageData, "ImageData is null.");
	F_Assert(InitParams.ImageData->Width, "Width should not be zero.");
	F_Assert(InitParams.ImageData->Height, "Height should not be zero.");

	DeInit();

	const FImageData& ImageData = *InitParams.ImageData;
	// #FIXME: This function could use more validation functions.
	F_Assert(ImageData.Pixels, "Pixel data is null.");

	F_GL(GL::GenTextures(1, &ID));
	F_GL(GL::BindTexture(ETexTarget::T2D, ID));
	
	F_GL(GL::TexParameteri(ETexTarget::T2D, ETexParameter::TextureWrapS, InitParams.TexWrapS));
	F_GL(GL::TexParameteri(ETexTarget::T2D, ETexParameter::TextureWrapT, InitParams.TexWrapT));

	F_GL(GL::TexParameteri(ETexTarget::T2D, ETexParameter::TextureMinFilter, InitParams.TexMinFilter));
	F_GL(GL::TexParameteri(ETexTarget::T2D, ETexParameter::TextureMagFilter, InitParams.TexMagFilter));

	const ETexGLFormat::Value GLTexFormat = FImageHelper::ToGLTexFormat(ImageData.PixelFormat);
	const ETexFormat::Value TexFormat = FImageHelper::ToTexFormat(ImageData.PixelFormat);

	F_GL(GL::TexImage2D(
		ETexTarget::T2D,
		InitParams.MipmapLevel,
		GLTexFormat,
		ImageData.Width,
		ImageData.Height,
		TexFormat,
		EType::UByte,
		ImageData.Pixels));

	F_GL(GL::GenerateMipmap(ETexTarget::T2D));
	F_GL(GL::BindTexture(ETexTarget::T2D, 0));

	F_Assert(IsValid(), "Initialization succeeded but this class is invalid.");
}

bool FImage::IsValid() const
{
	const bool Result = ID != 0;
	return Result;
}

void FImage::DeInit()
{
	if (ID)
	{
		F_GL(GL::DeleteTextures(1, &ID));
		ID = 0;
	}

	Width = 0;
	Height = 0;
	PixelFormat = EPixelFormat::Unknown;
}

void FImage::Enable() const
{
	F_Assert(IsValid(), "Class is invalid.");
	F_GL(GL::BindTexture(ETexTarget::T2D, ID));
}

void FImage::Disable()
{
	F_GL(GL::BindTexture(ETexTarget::T2D, 0));
}

void FImage::PostMoveReset()
{
	ID = 0;
	Width = 0;
	Height = 0;
	PixelFormat = EPixelFormat::Unknown;
}
