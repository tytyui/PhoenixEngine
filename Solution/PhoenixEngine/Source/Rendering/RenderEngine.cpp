#include "Rendering/RenderEngine.h"

#include "Math/Vector2D.h"
#include "Rendering/GLInterface.h"
#include "Rendering/Model.h"
#include "Rendering/ModelProcessor.h"

using namespace Phoenix;
using namespace Phoenix::GL;

namespace Phoenix
{
	struct FRenderEngineInternals
	{
		FRenderEngine::FInitParams InitParams;
		FModel TestModel;
		bool IsRunning{ false };
	};

	static_assert(sizeof(FRenderEngine) >= sizeof(FRenderEngineInternals), "Size must be updated.");
}

FRenderEngine::FRenderEngine()
{
	std::memset(PImplData, 0, sizeof(PImplData));

	FRenderEngineInternals& Ref = Get();
	const FRenderEngineInternals* const Ptr = new (&Ref) FRenderEngineInternals();

	F_Assert(this == (void*)Ptr, "Placement new required additional memory overhead.  Rework this.");
}

FRenderEngine::~FRenderEngine()
{
	FRenderEngineInternals& Eng = Get();
	Eng.~FRenderEngineInternals();
}

bool FRenderEngine::FInitParams::IsValid() const
{
	const bool IsWindowValid = Window != nullptr;
	return IsWindowValid;
}

void FRenderEngine::Init(const FInitParams& InInitParams)
{
	F_Assert(InInitParams.IsValid(), "Initialization parameters must be valid.");
	FRenderEngineInternals& Eng = Get();

	Eng.InitParams = InInitParams;

	Eng.InitParams.Window->SetGraphicsContextCurrent();

	{
		glewExperimental = true;

		const GLenum GLEWInitResult = glewInit();
		const bool GLEWFailedToInit = GLEWInitResult != GLEW_OK;

		if (GLEWFailedToInit)
		{
			F_LogError("Failed to initialize GLEW.");
			DeInit();
			return;
		}
	}

	F_GLIgnoreErrors();

	{	// #FIXME: Remove this later.
		FModelProcessor::FLoadParams LoadParams;

		LoadParams.File = "Station_2.obj";
		LoadParams.ModelDataHints = EModelData::All;

		FModelProcessor ModelProcessor;
		ModelProcessor.Load(LoadParams);

		const FMeshData::FEntries& Entries = ModelProcessor.GetMeshDataEntries();
		if (Entries.size())
		{
			Eng.TestModel.Init(ModelProcessor.GetMeshDataEntries());
		}

		F_LogErrorIf(!Eng.TestModel.IsValid(), "Model is invalid.");
	}	// #END_FIXME

	Eng.InitParams.Window->Show();

	const FVector2D& Dimensions = Eng.InitParams.Window->GetDimensions();
	const GLsizei Width = static_cast<GLsizei>(Dimensions.x);
	const GLsizei Height = static_cast<GLsizei>(Dimensions.y);

	F_GLDisplayErrors();
	F_GL(Viewport(0, 0, Width, Height));
	F_GL(ClearColor(0.f, 0.f, 0.f, 1.f));
	F_GL(Clear(EClearBit::Color));

	Eng.InitParams.Window->BufferSwap();

	Eng.IsRunning = true;
	F_Log("FRenderEngine initialized.");
}

bool FRenderEngine::IsValid() const
{
	const FRenderEngineInternals& Eng = Get();
	return Eng.IsRunning;
}

void FRenderEngine::DeInit()
{
	FRenderEngineInternals& Eng = Get();
	Eng.InitParams = FInitParams();
	Eng.TestModel.DeInit();
	Eng.IsRunning = false;
}

void FRenderEngine::Render()
{
	F_Assert(IsValid(), "This class is in an invalid state.");
	FRenderEngineInternals& Eng = Get();

	F_GLDisplayErrors();
	F_GL(Clear(EClearBit::Color));

	// #FIXME: Add tons of stuff here.

	Eng.InitParams.Window->BufferSwap();
}

struct FRenderEngineInternals& FRenderEngine::Get()
{
	typedef FRenderEngineInternals FREI;

	FREI* const Ptr = reinterpret_cast<FREI*>(&PImplData[0]);
	FREI& Ref = *Ptr;
	return Ref;
}

const struct FRenderEngineInternals& FRenderEngine::Get() const
{
	typedef FRenderEngineInternals FREI;

	const FREI* const Ptr = reinterpret_cast<const FREI*>(&PImplData[0]);
	const FREI& Ref = *Ptr;
	return Ref;
}
