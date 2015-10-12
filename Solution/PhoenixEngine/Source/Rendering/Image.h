#ifndef PHOENIX_IMAGE_H
#define PHOENIX_IMAGE_H

#include "ExternalLib/GLIncludes.h"
#include "Utility/Misc/Primitives.h"
#include "Rendering/ImageData.h"

namespace Phoenix {
	class FImage {
	public:
		struct FInitParams {
			const FImageData* ImageData{ nullptr };
			GLint MipmapLevel{ 0 };
		};

		FImage() = default;

		FImage(const FImage&) = delete;
		FImage& operator=(const FImage&) = delete;

		FImage(FImage&&);
		FImage& operator=(FImage&&);

		void Init(const FInitParams& InitParams);

		bool IsValid() const;

		void DeInit();

		void Enable();

		static void Disable();

	protected:
	private:
		GLuint ID{ 0 };
		EPixelFormat::Value PixelFormat{ EPixelFormat::Unknown };
		UInt16 Width{ 0 };
		UInt16 Height{ 0 };

		void PostMoveReset();
	};
}

#endif
