#include "Rendering/RenderEngine.h"

#include "ExternalLib/GLEWIncludes.h"
#include "ExternalLib/GLIncludes.h"
#include "Utility/FileIO/FileStream.h"
#include "Utility/Misc/Timer.h"
#include "Math/Math.h"
#include "Math/MatrixTransform.h"
#include "Math/Vector4D.h"
#include "Platform/Windowing/IWindow.h"
#include "Rendering/Camera.h"
#include "Rendering/GLInterface.h"
#include "Rendering/Model.h"
#include "Rendering/ModelProcessor.h"
#include "Rendering/Image.h"
#include "Rendering/ImageProcessor.h"
#include "Rendering/Shader.h"

using namespace Phoenix::GL;
using namespace Phoenix;

namespace Phoenix
{
	struct FRenderEngineInternals
	{
		IWindow* MainWindow{ nullptr };
		FRenderEngine::DrawFunction DrawFunc{ &FRenderEngine::EmptyFunction };
		bool bIsInit{ false };

		// #FIXME: Testing values.
		FCamera Camera;
		FModel Model;
		FShader ModelShader;
		FImage Image;
		FModel FBXModel;
		FImage FBXImage;
	};
}

static_assert(sizeof(FRenderEngine) >= sizeof(FRenderEngineInternals), "Size must be updated.");
static_assert(sizeof(FRenderEngine) == ERenderEngineInternals::Size, "Size must be updated.");

FRenderEngine::FRenderEngine()
{
	std::memset(PImplData, 0, sizeof(PImplData));

	FRenderEngineInternals& Ref = Get();
	const FRenderEngineInternals* const Ptr = new (&Ref) FRenderEngineInternals();

	F_Assert(this == (void*)Ptr, "Placement new required additional memory overhead.  Rework this.");
}

FRenderEngine::~FRenderEngine()
{
	DeInit();
	FRenderEngineInternals& Eng = Get();
	Eng.~FRenderEngineInternals();
}

void FRenderEngine::Init(IWindow& InMainWindow)
{
	DeInit();
	auto& Eng = Get();

	Eng.MainWindow = &InMainWindow;
	Eng.MainWindow->SetGraphicsContextCurrent();
	Eng.MainWindow->SetSwapInterval(1); // #FIXME: Magic number

	glewExperimental = true;

	const bool bGlewFailedToInit = glewInit() != GLEW_OK;
	if (bGlewFailedToInit)
	{
		F_LogError("Failed to initialize GLEW.");
		DeInit();
		return;
	}

	Eng.MainWindow->Show();

	F_GLIgnoreErrors();
	F_GL(GL::Viewport(
		0,
		0,
		static_cast<GLsizei>(Eng.MainWindow->GetDimensions().x),
		static_cast<GLsizei>(Eng.MainWindow->GetDimensions().y)));
	F_GL(GL::ClearColor(0.f, 0.f, 0.f, 1.f));
	F_GL(GL::Clear(EClearBit::Color));
	F_GL(GL::Enable(ECapability::DepthTest));

	Eng.MainWindow->BufferSwap();

	Eng.DrawFunc = &FRenderEngine::DrawInternal;
	Eng.bIsInit = true;

	F_Log("\tGFXEngine::Init() was successful.");
	F_Assert(IsValid(), "Initialization was successful but this class is still invalid.");
	DebugInitializeTestCode();
}

bool FRenderEngine::IsValid() const
{
	auto& Eng = Get();
	return Eng.bIsInit;
}

void FRenderEngine::DeInit()
{
	auto& Eng = Get();

	Eng.FBXImage.DeInit();
	Eng.FBXModel.DeInit();
	Eng.Image.DeInit();
	Eng.ModelShader.DeInit();
	Eng.Model.DeInit();
	Eng.Camera = FCamera();

	Eng.DrawFunc = &FRenderEngine::EmptyFunction;
	Eng.MainWindow = nullptr;

	if (Eng.bIsInit)
	{
		Eng.bIsInit = false;
		F_Log("\tGFXEngine::DeInit() was successful.");
	}
}

void FRenderEngine::Draw()
{
	auto& Eng = Get();

	F_Assert(Eng.DrawFunc, "DrawFunc is null.");
	(this->*Eng.DrawFunc)();
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

void FRenderEngine::DrawInternal()
{
	F_Assert(IsValid(), "This class is invalid.");
	auto& Eng = Get();

	const GL::EClearBit::Type EGLClearBits =
		GL::EClearBit::Color |
		GL::EClearBit::Depth |
		GL::EClearBit::Stencil;

	F_GL(GL::Clear(EGLClearBits));

	DebugRenderTestCode();

	Eng.MainWindow->BufferSwap();
}

void FRenderEngine::EmptyFunction()
{
}

void FRenderEngine::DebugInitializeTestCode()
{
	// Note: This code is not truly meant to be 
	// clean and is for debugging purposes only.
	auto& Eng = Get();

#pragma region Initialize Camera
	{
		const Float32 FOV = glm::radians(45.f);
		const Float32 AspectRatio =
			Eng.MainWindow->GetDimensions().x /
			Eng.MainWindow->GetDimensions().y;
		const Float32 Near = 0.1f;
		const Float32 Far = 1000.f;

		const FVector3D Position = FVector3D(0, 0.25f, 1.f);
		const FVector3D LookAtTarget = FVector3D(0, 0, 0);
		const FVector3D UpVector = FVector3D(0, 1, 0);

		Eng.Camera.SetPerspective(FOV, AspectRatio, Near, Far);

		Eng.Camera.SetPosition(Position);
		Eng.Camera.SetLookAtTarget(LookAtTarget);
		Eng.Camera.SetUpVector(UpVector);
		Eng.Camera.UpdateViewMatrix();
	}
#pragma endregion

#pragma region Initialize Model
	{
		static const FChar* const LoadFile = "Assets/Models/Fighter-Soul.obj";

		FModelProcessor::FLoadParams LoadParams;
		LoadParams.File = LoadFile;
		LoadParams.MeshAttributeHints = EMeshAttribute::All;

		FModelProcessor ModelProcessor;
		ModelProcessor.Load(LoadParams);

		if (!ModelProcessor.HasMeshDataEntries())
		{
			return;
		}

		Eng.Model.Init(ModelProcessor.GetMeshDataEntries());
	}
#pragma endregion

#pragma region Initialize Shader
	{
		TArray<FString, 2> Code;
		TArray<const FChar* const, 2> Files = {
			"Assets/Shaders/Model_VS.txt",
			"Assets/Shaders/Model_FS.txt",
		};

		for (UInt32 I = 0; I < Files.size(); ++I)
		{
			FFileStream FileStream;
			FileStream.open(Files[I], std::ios::in);

			if (!FileStream.is_open())
			{
				F_LogError("Failed to open file " << Files[I]);
				return;
			}

			FStringStream SS;
			SS << FileStream.rdbuf();
			FileStream.close();

			Code[I] = SS.str();
		}

		FShader::FInitParams Params;

		Params.Code[EShaderIndex::Vertex] = Code[0].c_str();
		Params.Code[EShaderIndex::Fragment] = Code[1].c_str();

		Eng.ModelShader.Init(Params);
	}
#pragma endregion

#pragma region Initialize Diffuse Image
	{
		FImageProcessor::FLoadParams LoadParams;
		LoadParams.File = "Assets/Textures/ship_fighter_soul.jpg";
		LoadParams.ImageLayout = EPixelFormat::RGBA;

		FImageProcessor ImageProcessor;
		ImageProcessor.Load(LoadParams);

		if (!ImageProcessor.IsValid())
		{
			return;
		}

		FImage::FInitParams InitParams;
		InitParams.ImageData = &ImageProcessor.GetImageData();
		InitParams.MipmapLevel = 0;

		Eng.Image.Init(InitParams);
	}
#pragma endregion

#pragma region Initialize FBX Model
	{
		static const FChar* const LoadFile = "Assets/Models/box.fbx";

		FModelProcessor::FLoadParams LoadParams;
		LoadParams.File = LoadFile;
		LoadParams.MeshAttributeHints = EMeshAttribute::All;

		FModelProcessor ModelProcessor;
		ModelProcessor.Load(LoadParams);

		if (!ModelProcessor.HasMeshDataEntries())
		{
			return;
		}

		Eng.FBXModel.Init(ModelProcessor.GetMeshDataEntries());
	}
#pragma endregion

#pragma region Initialize FBX Image
	{
		FImageProcessor::FLoadParams LoadParams;
		LoadParams.File = "Assets/Textures/daggercolor.tga";
		LoadParams.ImageLayout = EPixelFormat::RGBA;

		FImageProcessor ImageProcessor;
		ImageProcessor.Load(LoadParams);

		if (!ImageProcessor.IsValid())
		{
			return;
		}

		FImage::FInitParams InitParams;
		InitParams.ImageData = &ImageProcessor.GetImageData();
		InitParams.MipmapLevel = 0;

		Eng.FBXImage.Init(InitParams);
	}
#pragma endregion
}

void FRenderEngine::DebugRenderTestCode()
{
	// Note: This code is not truly meant to be 
	// clean and is for debugging purposes only.
	auto& Eng = Get();

	const bool ShouldReturn =
		!Eng.Image.IsValid() ||
		!Eng.ModelShader.IsValid() ||
		!Eng.Model.IsValid() ||
		!Eng.ModelShader.IsValid() ||
		!Eng.FBXModel.IsValid() ||
		!Eng.FBXImage.IsValid();

	if (ShouldReturn)
	{
		static bool OnceFlag = true;

		if (OnceFlag)
		{
			OnceFlag = false;
			F_LogWarning("DebugRenderTestCode will not run due to missing data.");
		}

		return;
	}

	const FMatrix4D Identity;

	{
		const Float32 TimeStamp = FHighResolutionTimer::GetTimeInSeconds<Float32>();

		FMatrix4D WorldMatrix =
			glm::rotate(Identity, glm::radians(TimeStamp * 45.f), FVector3D(0, 1, 0)) *
			glm::scale(Identity, FVector3D(0.035f));

		Eng.ModelShader.Enable();

		Eng.ModelShader.SetProjection(Eng.Camera.GetProjectionPtr());
		Eng.ModelShader.SetView(Eng.Camera.GetViewPtr());
		Eng.ModelShader.SetWorld(glm::value_ptr(WorldMatrix));
		Eng.ModelShader.SetDiffuseMap(0);

		// Note: #undefs exist for these defines.
#define PHOENIX_RENDER_ENGINE_TEST_MODEL Eng.FBXModel
#define PHOENIX_RENDER_ENGINE_TEST_IMG Eng.FBXImage
#define PHOENIX_RENDER_ENGINE_TEST_USE_DRAW_ARRAYS 0

		F_GL(GL::ClearColor(0.15f, 0.4f, 1.f, 1.f));

		for (const auto& Mesh : PHOENIX_RENDER_ENGINE_TEST_MODEL.GetMeshes())
		{
			F_GL(GL::BindVertexArray(Mesh.GetVertexArray()));

			F_GL(GL::ActiveTexture(ETex::T0));
			PHOENIX_RENDER_ENGINE_TEST_IMG.Enable();

#if PHOENIX_RENDER_ENGINE_TEST_USE_DRAW_ARRAYS
			F_GL(GL::DrawArrays(EMode::Triangles, 0, Mesh.GetVertexCount()));
#else
			F_GL(GL::DrawElements(EMode::Triangles, Mesh.GetIndexCount(), Mesh.GetIndexType(), nullptr));
#endif

			PHOENIX_RENDER_ENGINE_TEST_IMG.Disable();
			F_GL(GL::BindVertexArray(0));
		}

		Eng.ModelShader.Disable();
	}

#undef PHOENIX_RENDER_ENGINE_TEST_MODEL
#undef PHOENIX_RENDER_ENGINE_TEST_IMG
#undef PHOENIX_RENDER_ENGINE_TEST_USE_DRAW_ARRAYS
}
