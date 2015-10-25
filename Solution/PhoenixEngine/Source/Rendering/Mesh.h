#ifndef PHOENIX_MESH_H
#define PHOENIX_MESH_H

#include "ExternalLib/GLIncludes.h"
#include "Utility/Misc/Primitives.h"
#include "Rendering/GLInterface.h"
#include "Rendering/MeshData.h"

namespace Phoenix
{
	class FMesh
	{
	public:
		FMesh() = default;

		FMesh(const FMesh&) = delete;
		FMesh& operator=(const FMesh&) = delete;

		FMesh(FMesh&&);
		FMesh& operator=(FMesh&&);

		~FMesh();

		void Init(const struct FMeshData& MeshData);

		bool IsValid() const;

		void DeInit();

		GL::VertexArrayT GetVertexArray() const;

		GL::IndexCountT GetIndexCount() const;

		FMeshData::IndexTSizeT GetIndexTypeSize() const;

		GL::EType::Value GetIndexType() const;

		FMeshData::VertexCountT GetVertexCount() const;

	private:
		GL::VertexArrayT VertexArray{ 0 };
		GL::VertexBufferT VertexBuffer{ 0 };
		GL::ElementBufferT ElementBuffer{ 0 };
		GL::IndexCountT IndexCount{ 0 };
		FMeshData::IndexTSizeT IndexTSize{ 0 };
		FMeshData::VertexCountT VertexCount{ 0 };

		void PostMoveReset();
	};
}

#endif
