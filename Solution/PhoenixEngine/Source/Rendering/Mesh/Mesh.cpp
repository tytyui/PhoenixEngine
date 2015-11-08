#include "Rendering/Mesh/Mesh.h"

#include "Utility/Debug/Assert.h"
#include "Rendering/Caches/ImageCache.h"

using namespace Phoenix;

FMesh::FMesh(FMesh&& RHS)
	: VertexArray(RHS.VertexArray)
	, VertexBuffer(RHS.VertexBuffer)
	, ElementBuffer(RHS.ElementBuffer)
	, IndexCount(RHS.IndexCount)
	, IndexTSize(RHS.IndexTSize)
	, VertexCount(RHS.VertexCount)
	, DiffuseImage(std::move(RHS.DiffuseImage))
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
	VertexCount = RHS.VertexCount;
	DiffuseImage = std::move(RHS.DiffuseImage);

	RHS.PostMoveReset();
	return *this;
}

FMesh::~FMesh()
{
	DeInit();
}

void FMesh::Init(const FMeshData& MeshData, const FImageCache& ImageCache)
{
	// #FIXME: This function could be more
	// maintainable than it currently is.
	// Specifically: VertexAttribPointer and
	// EnableVertexAttribArray.
	F_Assert(MeshData.Positions.size(), "Position data is missing.");
	F_Assert(MeshData.Normals.size(), "Normal data is missing.");
	F_Assert(MeshData.UVCoords.size(), "UVCoords data is missing.");
	F_Assert(MeshData.Indices.size(), "Index data is missing.");

	F_GLDisplayErrors();

	DeInit();

	F_GL(GL::GenVertexArrays(1, &VertexArray));
	F_GL(GL::GenBuffers(1, &VertexBuffer));
	F_GL(GL::GenBuffers(1, &ElementBuffer));

	F_GL(GL::BindVertexArray(VertexArray));

	{
		const GLsizeiptr PositionsSize = MeshData.Positions.size() * sizeof(FMeshData::PositionT);
		const GLsizeiptr NormalsSize = MeshData.Normals.size() * sizeof(FMeshData::NormalT);
		const GLsizeiptr UVCoordsSize = MeshData.UVCoords.size() * sizeof(FMeshData::UVCoordT);

		const GLsizeiptr TotalSize = PositionsSize + NormalsSize + UVCoordsSize;

		const GLsizeiptr NormalsStart = PositionsSize;
		const GLsizeiptr UVCoordsStart = NormalsStart + NormalsSize;

		const GLvoid* const NormalsStartPtr = reinterpret_cast<GLvoid*>(NormalsStart);
		const GLvoid* const UVCoordsStartPtr = reinterpret_cast<GLvoid*>(UVCoordsStart);

		F_GL(GL::BindBuffer(GL::EBuffer::Array, VertexArray));
		F_GL(GL::BufferData(GL::EBuffer::Array, TotalSize, nullptr, GL::EUsage::StaticDraw));

		F_GL(GL::BufferSubData(GL::EBuffer::Array, 0, PositionsSize, &MeshData.Positions[0]));
		F_GL(GL::BufferSubData(GL::EBuffer::Array, NormalsStart, NormalsSize, &MeshData.Normals[0]));
		F_GL(GL::BufferSubData(GL::EBuffer::Array, UVCoordsStart, UVCoordsSize, &MeshData.UVCoords[0]));

		F_GL(GL::EnableVertexAttribArray(0));
		F_GL(GL::EnableVertexAttribArray(1));
		F_GL(GL::EnableVertexAttribArray(2));

		F_GL(GL::VertexAttribPointer(0, 3, GL::EType::Float, GL::EBool::False, 3 * sizeof(GLfloat), nullptr));
		F_GL(GL::VertexAttribPointer(1, 3, GL::EType::Float, GL::EBool::False, 3 * sizeof(GLfloat), NormalsStartPtr));
		F_GL(GL::VertexAttribPointer(2, 2, GL::EType::Float, GL::EBool::False, 2 * sizeof(GLfloat), UVCoordsStartPtr));
	}

	{
		const GLsizeiptr Size = MeshData.Indices.size() * sizeof(FMeshData::IndexT);

		F_GL(GL::BindBuffer(GL::EBuffer::ElementArray, ElementBuffer));
		F_GL(GL::BufferData(GL::EBuffer::ElementArray, Size, &MeshData.Indices[0], GL::EUsage::StaticDraw));

		IndexCount = Size / MeshData.IndexTSize;
		IndexTSize = MeshData.IndexTSize;
		VertexCount = MeshData.VertexCount;

		F_GL(GL::BindVertexArray(0));
	}

	{
		if (MeshData.DiffuseTexNameIndex != 0)
		{
			const FChar* const DiffuseTexName = &MeshData.TextureNames[MeshData.DiffuseTexNameIndex];

			// #FIXME: Retrieve the image from the cache as it should 
			// have been loaded before this method was called.
			// If it wasn't loaded, then too bad, this class should not
			// depend on FImageProcessor.
		}

		// #FIXME: Set up remaining image data here (if it's available).
	}
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
		F_GL(GL::DeleteVertexArrays(1, &VertexArray));
		VertexArray = 0;
	}

	if (VertexBuffer)
	{
		F_GL(GL::DeleteBuffers(1, &VertexBuffer));
		VertexBuffer = 0;
	}

	if (ElementBuffer)
	{
		F_GL(GL::DeleteBuffers(1, &ElementBuffer));
		ElementBuffer = 0;
	}

	IndexCount = 0;
	IndexTSize = 0;
	VertexCount = 0;
	DiffuseImage.DeInit();
}

GL::VertexArrayT FMesh::GetVertexArray() const
{
	return VertexArray;
}

GL::IndexCountT FMesh::GetIndexCount() const
{
	return IndexCount;
}

FMeshData::IndexTSizeT FMesh::GetIndexTypeSize() const
{
	return IndexTSize;
}

GL::EType::Value FMesh::GetIndexType() const
{
	const UInt8 UInt8Size = sizeof(UInt8);
	const UInt8 UInt16Size = sizeof(UInt16);
	const UInt8 UInt32Size = sizeof(UInt32);

	switch (IndexTSize)
	{
		case UInt8Size:
		{
			return GL::EType::UByte;
		}

		case UInt16Size:
		{
			return GL::EType::UShort;
		}

		case UInt32Size:
		{
			return GL::EType::UInt;
		}

		default:
		{
			F_Assert(false, "Invalid size of " << IndexTSize);
			break;
		}
	}

	F_Assert(false, "Invalid size of " << IndexTSize);
	return GL::EType::UByte;
}

FMeshData::VertexCountT FMesh::GetVertexCount() const
{
	return VertexCount;
}

EMeshAttribute::Type FMesh::GetValidImages() const
{
	EMeshAttribute::Type MeshAttrib = EMeshAttribute::None;
	
	if (DiffuseImage.IsValid())
	{
		MeshAttrib |= EMeshAttribute::DiffuseMap;
	}

	return MeshAttrib;
}

const THandle<FImage>& FMesh::GetDiffuseImage() const
{
	return DiffuseImage;
}

void FMesh::PostMoveReset()
{
	VertexArray = 0;
	VertexBuffer = 0;
	ElementBuffer = 0;
	IndexCount = 0;
	IndexTSize = 0;
	VertexCount = 0;
	DiffuseImage.DeInit();
}
