#ifndef PHOENIX_MESH_DATA_H
#define PHOENIX_MESH_DATA_H

#include "ExternalLib/GLIncludes.h"
#include "Utility/Containers/Array.h"
#include "Utility/Containers/Vector.h"
#include "Rendering/Image/ImageData.h"

namespace Phoenix
{
	namespace EMeshAttribute
	{
		typedef UInt16 Type;

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

	struct FMeshData
	{
		typedef GLfloat PositionT;
		typedef GLfloat NormalT;
		typedef GLfloat UVCoordT;
		typedef UInt8 IndexT;
		typedef UInt8 IndexTSizeT;
		typedef GLsizei VertexCountT;
		typedef TVector<FMeshData> FEntries;
		typedef UInt16 TexNameIndexT;

		EMeshAttribute::Type MeshAttrib{ EMeshAttribute::None };
		TVector<PositionT> Positions;
		TVector<NormalT> Normals;
		TVector<UVCoordT> UVCoords;
		TVector<IndexT> Indices;
		IndexTSizeT IndexTSize{ 0 };
		VertexCountT VertexCount{ 0 };
		TVector<FChar> TextureNames;
		TexNameIndexT DiffuseTexNameIndex{ 0 };
	};
}

#endif
