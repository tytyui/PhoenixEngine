#ifndef PHOENIX_MODEL_DATA_H
#define PHOENIX_MODEL_DATA_H

#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	namespace EModelData
	{
		typedef UInt8 Type;

		enum BitMask : Type
		{
			None = 0,
			Positions = 1 << 0,
			Normals = 1 << 1,
			UVCoords = 1 << 2,
			DiffuseMap = 1 << 3,
			NormalMap = 1 << 4,
			SpecularMap = 1 << 5,
			Material = 1 << 6,
			All = Positions | Normals | UVCoords | DiffuseMap | NormalMap | SpecularMap | Material
		};
	}
}

#endif
