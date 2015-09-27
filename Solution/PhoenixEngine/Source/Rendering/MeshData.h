#ifndef PHOENIX_MESH_DATA_H
#define PHOENIX_MESH_DATA_H

#include "Utility/Containers/Vector.h"
#include "Rendering/ModelData.h"

namespace Phoenix
{
	struct FMeshData
	{
		EModelData::Type ModelData{ EModelData::None };
		TVector<Float32> Positions;
		TVector<Float32> Normals;
		TVector<Float32> UVCoords;
		TVector<UInt8> Indices;
		UInt8 IndexTSize{ 0 };

		typedef TVector<FMeshData> FEntries;
	};
}

#endif
