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
			Indices = 1 << 2,
			UVCoords = 1 << 3,
			DiffuseMap = 1 << 4,
			NormalMap = 1 << 5,
			SpecularMap = 1 << 6,
			Material = 1 << 7,
			All = Positions | Normals | Indices | UVCoords | DiffuseMap | NormalMap | SpecularMap | Material
		};
	}
}

#endif
