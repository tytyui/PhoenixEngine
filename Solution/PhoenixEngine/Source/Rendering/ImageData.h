#ifndef PHOENIX_IMAGE_DATA_H
#define PHOENIX_IMAGE_DATA_H

#include "Utility/Misc/Primitives.h"

namespace Phoenix {
	namespace EPixelFormat {
		typedef UInt8 Type;

		enum Value : Type {
			Unknown,
			Luminous,
			LuminousAlpha,
			RGB,
			RGBA,
			Count
		};
	}

	struct FImageData {
		UInt8* Pixels{ nullptr };
		EPixelFormat::Value PixelFormat{ EPixelFormat::Unknown };
		UInt16 Width{ 0 };
		UInt16 Height{ 0 };
	};
}

#endif
