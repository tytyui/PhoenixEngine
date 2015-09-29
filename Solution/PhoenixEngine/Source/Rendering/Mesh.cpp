#include "Rendering/Mesh.h"

#include "Utility/Debug/Assert.h"
#include "Rendering/GLInterface.h"
#include "Rendering/MeshData.h"

using namespace Phoenix;
using namespace Phoenix::GL;

FMesh::FMesh(FMesh&& RHS)
	: VertexArray(RHS.VertexArray)
	, VertexBuffer(RHS.VertexBuffer)
	, ElementBuffer(RHS.ElementBuffer)
	, IndexCount(RHS.IndexCount)
	, IndexTSize(RHS.IndexTSize)
{
	RHS.PostMoveReset();
}

FMesh& FMesh::operator=(FMesh&& RHS)
{
	F_Assert(this != &RHS, "Self move assign is illegal.");
	DeInit();

	VertexArray = RHS.VertexArray;
	VertexBuffer = RHS.VertexBuffer;
	ElementBuffer = RHS.ElementBuffer;
	IndexCount = RHS.IndexCount;
	IndexTSize = RHS.IndexTSize;

	RHS.PostMoveReset();
	return *this;
}

FMesh::~FMesh()
{
	DeInit();
}

void FMesh::Init(const FMeshData& MeshData)
{
	// #FIXME: This function could be more
	// maintainable than it currently is.
	F_Assert(MeshData.Positions.size(), "Position data is missing.");
	F_Assert(MeshData.Normals.size(), "Position data is missing.");
	F_Assert(MeshData.UVCoords.size(), "Position data is missing.");
	F_Assert(MeshData.Indices.size(), "Index data is missing.");

	F_GLDisplayErrors();

	DeInit();

	F_GL(GenVertexArrays(1, &VertexArray));
	F_GL(GenBuffers(1, &VertexBuffer));
	F_GL(GenBuffers(1, &ElementBuffer));

	F_GL(BindVertexArray(VertexArray));

	{
		const GLsizeiptr PositionsSize = MeshData.Positions.size() * sizeof(Float32);
		const GLsizeiptr NormalsSize = MeshData.Normals.size() * sizeof(Float32);
		const GLsizeiptr UVCoordsSize = MeshData.UVCoords.size() * sizeof(Float32);

		const GLsizeiptr TotalSize = PositionsSize + NormalsSize + UVCoordsSize;

		const GLsizeiptr NormalsStart = PositionsSize;
		const GLsizeiptr UVCoordsStart = NormalsStart + NormalsSize;

		const GLvoid* const NormalsStartPtr = reinterpret_cast<GLvoid*>(NormalsStart);
		const GLvoid* const UVCoordsStartPtr = reinterpret_cast<GLvoid*>(UVCoordsStart);

		F_GL(BindBuffer(EBuffer::Array, VertexArray));
		F_GL(BufferData(EBuffer::Array, TotalSize, nullptr, EUsage::StaticDraw));

		F_GL(BufferSubData(EBuffer::Array, 0, PositionsSize, &MeshData.Positions[0]));
		F_GL(BufferSubData(EBuffer::Array, NormalsStart, NormalsSize, &MeshData.Normals[0]));
		F_GL(BufferSubData(EBuffer::Array, UVCoordsStart, UVCoordsSize, &MeshData.UVCoords[0]));

		F_GL(VertexAttribPointer(0, 3, EType::Float, EBool::False, 3 * sizeof(GLfloat), nullptr));
		F_GL(VertexAttribPointer(1, 3, EType::Float, EBool::False, 3 * sizeof(GLfloat), NormalsStartPtr));
		F_GL(VertexAttribPointer(2, 2, EType::Float, EBool::False, 2 * sizeof(GLfloat), UVCoordsStartPtr));
	}

	{
		const GLsizeiptr Size = MeshData.Indices.size() * sizeof(UInt8);

		F_GL(BindBuffer(EBuffer::ElementArray, ElementBuffer));
		F_GL(BufferData(EBuffer::ElementArray, Size, &MeshData.Indices[0], EUsage::StaticDraw));

		IndexCount = MeshData.Indices.size();
		IndexTSize = MeshData.IndexTSize;
	}

	F_GL(BindVertexArray(0));
}

bool FMesh::IsValid() const
{
	const bool Result = VertexArray != 0;
	return Result;
}

void FMesh::DeInit()
{
	F_GLDisplayErrors();
	if (VertexArray)
	{
		F_GL(DeleteVertexArrays(1, &VertexArray));
		VertexArray = 0;
	}

	if (VertexBuffer)
	{
		F_GL(DeleteBuffers(1, &VertexBuffer));
		VertexBuffer = 0;
	}

	if (ElementBuffer)
	{
		F_GL(DeleteBuffers(1, &ElementBuffer));
		ElementBuffer = 0;
	}

	IndexCount = 0;
	IndexTSize = 0;
}

GLuint FMesh::GetVertexArray() const
{
	return VertexArray;
}

GLsizei FMesh::GetIndexCount() const
{
	return IndexCount;
}

UInt8 FMesh::GetIndexTypeSize() const
{
	return IndexTSize;
}

void FMesh::PostMoveReset()
{
	VertexArray = 0;
	VertexBuffer = 0;
	ElementBuffer = 0;
	IndexCount = 0;
	IndexTSize = 0;
}
