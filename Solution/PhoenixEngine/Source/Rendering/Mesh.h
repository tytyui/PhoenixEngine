#ifndef PHOENIX_MESH_H
#define PHOENIX_MESH_H

#include "ExternalLib/GLIncludes.h"
#include "Utility/Misc/Primitives.h"
#include "Rendering/GLInterface.h"

namespace Phoenix {
	class FMesh {
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

		GLuint GetVertexArray() const;

		GLsizei GetIndexCount() const;

		UInt8 GetIndexTypeSize() const;

		GL::EType::Value GetIndexType() const;

	private:
		GLuint VertexArray{ 0 };
		GLuint VertexBuffer{ 0 };
		GLuint ElementBuffer{ 0 };
		GLsizei IndexCount{ 0 };
		UInt8 IndexTSize{ 0 };

		void PostMoveReset();
	};
}

#endif
