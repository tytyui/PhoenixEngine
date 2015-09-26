#include "Rendering/RenderEngine.h"

#include "Math/Vector2D.h"
#include "Rendering/GLInterface.h"
#include "Rendering/Model.h"
#include "Rendering/ModelProcessor.h"

using namespace Phoenix;

bool FRenderEngine::FInitParams::IsValid() const
{
	const bool IsWindowValid = Window != nullptr;
	return IsWindowValid;
}

void FRenderEngine::Init(const FInitParams& InInitParams)
{
	F_Assert(InInitParams.IsValid(), "Initialization parameters must be valid.");

	InitParams = InInitParams;

	InitParams.Window->SetGraphicsContextCurrent();

	{	// #FIXME: Remove this later.
		FModelProcessor::FLoadParams LoadParams;

		LoadParams.File = "Station_2.obj";
		LoadParams.ModelDataHints = EModelData::All;

		FModelProcessor ModelProcessor;
		ModelProcessor.Load(LoadParams);
	}	// #END_FIXME

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

	InitParams.Window->Show();

	const FVector2D& Dimensions = InitParams.Window->GetDimensions();
	const GLsizei Width = static_cast<GLsizei>(Dimensions.x);
	const GLsizei Height = static_cast<GLsizei>(Dimensions.y);

	F_GLIgnoreErrors();
	F_GL(GL::Viewport(0, 0, Width, Height));
	F_GL(GL::ClearColor(0.f, 0.f, 0.f, 1.f));
	F_GL(GL::Clear(GL::EClearBit::Color));

	InitParams.Window->BufferSwap();

	IsRunning = true;
	F_Log("FRenderEngine initialized.");
}

bool FRenderEngine::IsValid() const
{
	return IsRunning;
}

void FRenderEngine::DeInit()
{
	InitParams = FInitParams();
	IsRunning = false;
}

void FRenderEngine::Render()
{
	F_Assert(IsValid(), "This class is in an invalid state.");

	F_GLDisplayErrors();
	F_GL(GL::Clear(GL::EClearBit::Color));

	// #FIXME: Add tons of stuff here.

	InitParams.Window->BufferSwap();
}