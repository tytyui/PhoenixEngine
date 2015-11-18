#ifndef PHOENIX_SHADER_H
#define PHOENIX_SHADER_H

#include "Utility/Containers/Array.h"
#include "Utility/Misc/String.h"
#include "Math/Matrix3D.h"
#include "Math/Matrix4D.h"
#include "Rendering/GLInterface.h"

namespace Phoenix
{
	namespace EShaderIndex
	{
		typedef UInt32 Type;

		enum Value : Type
		{
			Compute,
			Vertex,
			TessControl,
			TessEvaluation,
			Geometry,
			Fragment,
			Count
		};

		static inline bool IsIndexValid(const EShaderIndex::Type ShaderIndex)
		{
			const bool Result = ShaderIndex < EShaderIndex::Count;
			return Result;
		}

		static inline GL::EShader::Value ToShader(const EShaderIndex::Value ShaderIndex)
		{
			static_assert(EShaderIndex::Count == 6, "This table requires updating.");
			static const TArray<GL::EShader::Value, EShaderIndex::Count> LookUpTable = {
				GL::EShader::Compute,
				GL::EShader::Vertex,
				GL::EShader::TessControl,
				GL::EShader::TessEvaluation,
				GL::EShader::Geometry,
				GL::EShader::Fragment,
			};

			const GL::EShader::Value Result = LookUpTable[ShaderIndex];
			return Result;
		}

		static inline const FChar* const ToString(const EShaderIndex::Value ShaderIndex)
		{
			static_assert(EShaderIndex::Count == 6, "This table requires updating.");
			static const TArray<const GLchar* const, EShaderIndex::Count> LookUpTable = {
				"Compute",
				"Vertex",
				"TessControl",
				"TessEvaluation",
				"Geometry",
				"Fragment"
			};

			const FChar* const Result = LookUpTable[ShaderIndex];
			return Result;
		}
	}

	class FShader
	{
	public:
		typedef TArray<const GLchar*, EShaderIndex::Count> CodeT;
		typedef TArray<FString, EShaderIndex::Count> CodeStrT;

		static const GLint InvalidUniform;

		struct FInitParams
		{
			CodeT Code;

			FInitParams();

			FInitParams(const FInitParams&) = delete;
			FInitParams& operator=(const FInitParams&) = delete;

			FInitParams(FInitParams&&) = delete;
			FInitParams& operator=(FInitParams&&) = delete;
		};

		FShader();

		FShader(const FShader&) = delete;
		FShader& operator=(const FShader&) = delete;

		FShader(FShader&&);
		FShader& operator=(FShader&&);

		~FShader();

		void Init(const FInitParams& InitParams);

		bool IsValid() const;

		void DeInit();

		void Enable();

		static void Disable();

		void SetProjection(const FMatrix4D& ProjectionMatrix) const;

		void SetView(const FMatrix4D& ViewMatrix) const;

		void SetWorld(const FMatrix4D& WorldMatrix) const;

		void SetInverseTransposeWorld(const FMatrix3D& InverseTransposeWorld) const;

		void SetWorldViewProjectionPtr(const FMatrix4D& WorldViewProjection) const;

		void SetDiffuseMap(const GLint DiffuseMap) const;

		void SetNormalMap(const GLint NormalMap) const;

	private:
		GLuint Program{ 0 };
		TArray<GLuint, EShaderIndex::Count> Shaders;

		void InitProgram();

		bool IsProgramValid() const;

		void DeInitProgram();

		void InitShader(const EShaderIndex::Value ShaderIndex, const GLchar* const Code);

		bool IsShaderValid(const EShaderIndex::Value ShaderIndex) const;

		void DeInitShader(const EShaderIndex::Value ShaderIndex);

		GLint GetShaderUniformLocation(const GLchar* const UniformName) const;

		bool IsShaderUniformValid(const GLchar* const UniformName) const;

		void OnInitComplete();

		void SetUniform(const FMatrix3D& Matrix3D, const GLchar* const UniformName) const;

		void SetUniform(const FMatrix4D& Matrix4D, const GLchar* const UniformName) const;

		void PostMoveReset();
	};
}

#endif
