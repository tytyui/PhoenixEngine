#include "Rendering/Shader/Shader.h"

#include "Utility/Debug/Assert.h"
#include "Math/MatrixTransform.h"
#include "Rendering/Shader/ShaderUniforms.h"

using namespace Phoenix;

const GLint FShader::InvalidUniform = -1;

FShader::FInitParams::FInitParams()
{
	Code.fill(nullptr);
}

FShader::FShader()
{
	Shaders.fill(0);
}

FShader::FShader(FShader&& RHS)
	: Program(RHS.Program)
	, Shaders(RHS.Shaders)
{
	RHS.PostMoveReset();
}

FShader& FShader::operator=(FShader&& RHS)
{
	F_Assert(this != &RHS, "Self assignment is illegal.");

	Program = RHS.Program;
	Shaders = RHS.Shaders;
	
	RHS.PostMoveReset();
	return *this;
}

FShader::~FShader()
{
	DeInit();
}

void FShader::Init(const FInitParams& InitParams)
{
	DeInit();

	InitProgram();

	for (UInt32 I = 0; I < InitParams.Code.size(); ++I)
	{
		if (!InitParams.Code[I])
		{
			continue;
		}

		const EShaderIndex::Value Index = static_cast<EShaderIndex::Value>(I);
		InitShader(Index, InitParams.Code[I]);
	}

	OnInitComplete();
}

bool FShader::IsValid() const
{
	const bool Result = IsProgramValid();
	return Result;
}

void FShader::DeInit()
{
	for (UInt32 I = 0; I < Shaders.size(); ++I)
	{
		const EShaderIndex::Value Index = static_cast<EShaderIndex::Value>(I);
		DeInitShader(Index);
	}

	DeInitProgram();
}

void FShader::Enable()
{
	F_Assert(IsValid(), "Shader is invalid.");
	F_GL(GL::UseProgram(Program));
}

void FShader::Disable()
{
	F_GL(GL::UseProgram(0));
}

void FShader::SetProjection(const FMatrix4D& ProjectionMatrix) const
{
	SetUniform(ProjectionMatrix, EUniform::Projection);
}

void FShader::SetView(const FMatrix4D& ViewMatrix) const
{
	SetUniform(ViewMatrix, EUniform::View);
}

void FShader::SetWorld(const FMatrix4D& WorldMatrix) const
{
	SetUniform(WorldMatrix, EUniform::World);
}

void FShader::SetInverseTransposeWorld(const FMatrix3D& InverseTransposeWorld) const
{
	SetUniform(InverseTransposeWorld, EUniform::InverseTransposeWorld);
}

void FShader::SetWorldViewProjectionPtr(const FMatrix4D& WorldViewProjection) const
{
	SetUniform(WorldViewProjection, EUniform::WorldViewProjection);
}

void FShader::SetDiffuseMap(const GLint DiffuseMap) const
{
	const GLint UniformLocation = GetShaderUniformLocation(EUniform::DiffuseMap);
	F_GL(GL::Uniform1i(UniformLocation, DiffuseMap));
}

void FShader::SetNormalMap(const GLint NormalMap) const
{
	const GLint UniformLocation = GetShaderUniformLocation(EUniform::NormalMap);
	F_GL(GL::Uniform1i(UniformLocation, NormalMap));
}

void FShader::InitProgram()
{
	DeInitProgram();
	Program = F_GL(GL::CreateProgram());
	F_LogErrorIf(Program == 0, "Failed to create shader program.");
}

bool FShader::IsProgramValid() const
{
	const bool Result = Program != 0;
	return Result;
}

void FShader::DeInitProgram()
{
	if (Program)
	{
		F_GL(GL::DeleteProgram(Program));
		Program = 0;
	}
}

void FShader::InitShader(const EShaderIndex::Value ShaderIndex, const GLchar* const Code)
{
	F_Assert(EShaderIndex::IsIndexValid(ShaderIndex), "Invalid index.");
	F_Assert(Code, "Code is invalid.");

	DeInitShader(ShaderIndex);
	GLuint& Shader = Shaders[ShaderIndex];

	const GL::EShader::Value ShaderType = EShaderIndex::ToShader(ShaderIndex);
	Shader = F_GL(GL::CreateShader(ShaderType));

	if (Shader == 0)
	{
		F_LogError("Failed to create shader.");
		return;
	}

	F_GL(GL::ShaderSource(Shader, Code));
	F_GL(GL::CompileShader(Shader));

	GLint Success = 0;
	F_GL(GL::GetShaderiv(Shader, GL::EShaderData::CompileStatus, Success));

	if (!Success)
	{
		GLchar InfoLog[1024] = "";
		GLsizei WrittenLength = 0;

		F_GL(GL::GetShaderInfoLog(Shader, InfoLog, sizeof(InfoLog), WrittenLength));
		F_LogError("Failed to compile shader.  " << InfoLog);

		DeInitShader(ShaderIndex);
		return;
	}

	F_GL(GL::AttachShader(Program, Shader));
}

bool FShader::IsShaderValid(const EShaderIndex::Value ShaderType) const
{
	F_Assert(EShaderIndex::IsIndexValid(ShaderType), "Invalid index.");

	const bool Result = Shaders[ShaderType] != 0;
	return Result;
}

void FShader::DeInitShader(const EShaderIndex::Value ShaderIndex)
{
	F_Assert(EShaderIndex::IsIndexValid(ShaderIndex), "Invalid index.");

	if (Shaders[ShaderIndex])
	{
		F_GL(GL::DeleteShader(Shaders[ShaderIndex]));
		Shaders[ShaderIndex] = 0;
	}
}

GLint FShader::GetShaderUniformLocation(const GLchar* const UniformName) const
{
	F_Assert(UniformName, "UniformName is null.");

	const GLint Location = F_GL(GL::GetUniformLocation(Program, UniformName));
	F_LogErrorIf(Location == FShader::InvalidUniform, "Failed to get valid uniform for " << UniformName);

	return Location;
}

bool FShader::IsShaderUniformValid(const GLchar* const UniformName) const
{
	F_Assert(UniformName, "UniformName is null.");

	const GLint Uniform = GetShaderUniformLocation(UniformName);
	const bool Result = Uniform != FShader::InvalidUniform;
	return Result;
}

void FShader::OnInitComplete()
{
	static const auto OnErrorFunction = [this]()
	{
		GLchar InfoLog[1024] = "";
		F_GL(GL::GetProgramInfoLog(Program, sizeof(InfoLog), nullptr, InfoLog));
		F_LogError("Error while finalizing shader.  " << InfoLog);
		DeInit();
	};

	F_Assert(IsProgramValid(), "Program is invalid.");
	F_GL(GL::LinkProgram(Program));

	GLint ProgramSuccess = 0;
	F_GL(GL::GetProgramiv(Program, GL::EGetProgram::LinkStatus, ProgramSuccess));

	if (!ProgramSuccess)
	{
		OnErrorFunction();
		return;
	}

	ProgramSuccess = 0;
	F_GL(GL::ValidateProgram(Program));
	F_GL(GL::GetProgramiv(Program, GL::EGetProgram::ValidateStatus, ProgramSuccess));

	if (!ProgramSuccess)
	{
		OnErrorFunction();
		return;
	}

	F_LogTrace("Shader created.");
}

void FShader::SetUniform(const FMatrix3D& Matrix3D, const GLchar* const UniformName) const
{
	const GLint UniformLocation = GetShaderUniformLocation(UniformName);
	const GLfloat* const Matrix3DPtr = glm::value_ptr(Matrix3D);

	F_GL(GL::UniformMatrix3fv(UniformLocation, 1, GL::EBool::False, Matrix3DPtr));
}

void FShader::SetUniform(const FMatrix4D& Matrix4D, const GLchar* const UniformName) const
{
	const GLint UniformLocation = GetShaderUniformLocation(UniformName);
	const GLfloat* const Matrix4DPtr = glm::value_ptr(Matrix4D);

	F_GL(GL::UniformMatrix4fv(UniformLocation, 1, GL::EBool::False, Matrix4DPtr));
}

void FShader::PostMoveReset()
{
	Program = 0;
	Shaders.fill(0);
}
