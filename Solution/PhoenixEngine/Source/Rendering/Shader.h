#ifndef PHOENIX_SHADER_H
#define PHOENIX_SHADER_H

#include "Utility/Containers/Array.h"
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
	}

	class FShader
	{
	public:
		static const GLint InvalidUniform;

		struct FInitParams
		{
			TArray<const GLchar*, EShaderIndex::Count> Code;

			FInitParams();

			FInitParams(const FInitParams&) = default;
			FInitParams& operator=(const FInitParams&) = default;

			FInitParams(FInitParams&&) = delete;
			FInitParams& operator=(FInitParams&&) = delete;
		};

		FShader();

		FShader(const FShader&) = delete;
		FShader& operator=(const FShader) = delete;

		FShader(FShader&&) = delete;
		FShader& operator=(FShader&&) = delete;

		~FShader();

		void Init(const FInitParams& InitParams);

		bool IsValid() const;

		void DeInit();

		void Enable();

		static void Disable();

		void SetProjection(const GLfloat* const ProjectionMatrixPtr);

		void SetView(const GLfloat* const ViewMatrixPtr);

		void SetWorld(const GLfloat* const WorldMatrixPtr);

		void SetDiffuseMap(const GLint DiffuseMap);

		void SetNormalMap(const GLint NormalMap);

	private:
		GLuint Program{ 0 };
		TArray<GLuint, EShaderIndex::Count> Shaders;

		void InitProgram();

		void DeInitProgram();

		bool IsProgramValid() const;

		void InitShader(const EShaderIndex::Value ShaderIndex, const GLchar* const Code);

		void DeInitShader(const EShaderIndex::Value ShaderIndex);

		bool IsShaderValid(const EShaderIndex::Value ShaderIndex) const;

		GLint GetShaderUniformLocation(const GLchar* const UniformName) const;

		bool IsShaderUniformValid(const GLchar* const UniformName) const;

		void OnInitComplete();
	};
}

#endif
