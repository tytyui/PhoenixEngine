#include "Rendering/GFXEngine.h"

#include "ExternalLib/GLEWIncludes.h"
#include "ExternalLib/GLIncludes.h"
#include "Utility/FileIO/FileStream.h"
#include "Utility/Misc/Memory.h"
#include "Utility/Misc/Timer.h"
#include "Math/Math.h"
#include "Math/Matrix3D.h"
#include "Math/MatrixTransform.h"
#include "Math/Vector4D.h"
#include "Platform/Windowing/IWindow.h"
#include "Rendering/Camera.h"
#include "Rendering/GLInterface.h"
#include "Rendering/Caches/GFXCaches.h"
#include "Rendering/Handles/GFXHandles.h"
#include "Rendering/Image/Image.h"
#include "Rendering/Image/ImageProcessor.h"
#include "Rendering/Model/Model.h"
#include "Rendering/Model/ModelProcessor.h"
#include "Rendering/Shader/Shader.h"

using namespace Phoenix::GL;
using namespace Phoenix;

namespace Phoenix
{
	struct FGFXEngineInternals
	{
		IWindow* MainWindow{ nullptr };
		FGFXEngine::DrawFunction DrawFunc{ &FGFXEngine::EmptyFunction };
		TUniquePtr<FGFXCaches> Caches{ std::make_unique<FGFXCaches>() };
		TUniquePtr<FGFXHandles> Handles{ std::make_unique<FGFXHandles>() };
		bool bIsInit{ false };

		// #FIXME: Testing values.
		FCamera Camera;
		THandle<FModel> Model;
		THandle<FShader> ModelShader;
		THandle<FImage> Image;
		THandle<FModel> FBXModel;
		THandle<FImage> FBXImage;
		bool bIsDebugCodeInit{ false };
	};
}

static_assert(sizeof(FGFXEngine) >= sizeof(FGFXEngineInternals), "Size must be updated.");
static_assert(sizeof(FGFXEngine) == EGFXEngineInternals::Size, "Size must be updated.");

FGFXEngine::FGFXEngine()
{
	FGFXEngineInternals& Ref = Get();
	const FGFXEngineInternals* const Ptr = new (&Ref) FGFXEngineInternals();

	F_Assert(this == (void*)Ptr, "Placement new required additional memory overhead.  Rework this.");
}

FGFXEngine::~FGFXEngine()
{
	DeInit();
	FGFXEngineInternals& Eng = Get();
	Eng.~FGFXEngineInternals();
}

void FGFXEngine::Init(IWindow& InMainWindow)
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

	Eng.DrawFunc = &FGFXEngine::DrawInternal;
	Eng.bIsInit = true;

	F_Log("\tGFXEngine::Init() was successful.  Class internals size: " << sizeof(FGFXEngineInternals));
	F_Assert(IsValid(), "Initialization was successful but this class is still invalid.");
	DebugInitializeTestCode();
}

bool FGFXEngine::IsValid() const
{
	auto& Eng = Get();
	return Eng.bIsInit;
}

void FGFXEngine::DeInit()
{
	auto& Eng = Get();

	Eng.FBXImage.DeInit();
	Eng.FBXModel.DeInit();
	Eng.Image.DeInit();
	Eng.ModelShader.DeInit();
	Eng.Model.DeInit();
	Eng.Camera = FCamera();

	Eng.DrawFunc = &FGFXEngine::EmptyFunction;
	Eng.MainWindow = nullptr;

	if (Eng.bIsInit)
	{
		Eng.bIsInit = false;
		F_Log("\tGFXEngine::DeInit() was successful.");
	}
}

void FGFXEngine::Draw()
{
	auto& Eng = Get();

	F_Assert(Eng.DrawFunc, "DrawFunc is null.");
	(this->*Eng.DrawFunc)();
}

struct FGFXEngineInternals& FGFXEngine::Get()
{
	typedef FGFXEngineInternals FREI;

	FREI* const Ptr = reinterpret_cast<FREI*>(&PImplData[0]);
	FREI& Ref = *Ptr;
	return Ref;
}

const struct FGFXEngineInternals& FGFXEngine::Get() const
{
	typedef FGFXEngineInternals FREI;

	const FREI* const Ptr = reinterpret_cast<const FREI*>(&PImplData[0]);
	const FREI& Ref = *Ptr;
	return Ref;
}

void FGFXEngine::DrawInternal()
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

void FGFXEngine::EmptyFunction()
{
}

void FGFXEngine::DebugInitializeTestCode()
{
	// Note: This code is not truly meant to be 
	// clean and is for debugging purposes only.
	auto& Eng = Get();

#pragma region (Camera) Initialize Camera
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

#pragma region (Model) Initialize Model
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

		// #FIXME: Load the images before the meshes try to find them.

		Eng.Model = Eng.Handles->GetModelHandles().CreateHandle();
		Eng.Model->Init(ModelProcessor.GetMeshDataEntries(), Eng.Caches->GetImageCache());
	}
#pragma endregion

#pragma region (ModelShader) Initialize Shader
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

		Eng.ModelShader = Eng.Handles->GetShaderHandles().CreateHandle();
		Eng.ModelShader->Init(Params);
	}
#pragma endregion

#pragma region (Image) Initialize Diffuse Image
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

		Eng.Image = Eng.Handles->GetImageHandles().CreateHandle();
		Eng.Image->Init(InitParams);
		Eng.Caches->GetImageCache().AddEntry(LoadParams.File, Eng.Image);
	}
#pragma endregion

#define RENDER_ENGINE_USE_BOX_EXAMPLE 0
#define RENDER_ENGINE_USE_DAGGER_EXAMPLE 0
#define RENDER_ENGINE_USE_WIZARD_EXAMPLE 1

#pragma region (FBXModel) Initialize FBX Model
	{
#if RENDER_ENGINE_USE_BOX_EXAMPLE
		static const FChar* const LoadFile = "Assets/Models/box.fbx";
#elif RENDER_ENGINE_USE_DAGGER_EXAMPLE 
		static const FChar* const LoadFile = "Assets/Models/dagger.fbx";
#elif RENDER_ENGINE_USE_WIZARD_EXAMPLE 
		static const FChar* const LoadFile = "Assets/Models/wizard girl.fbx";
#endif

		FModelProcessor::FLoadParams LoadParams;
		LoadParams.File = LoadFile;
		LoadParams.MeshAttributeHints = EMeshAttribute::All;

		FModelProcessor ModelProcessor;
		ModelProcessor.Load(LoadParams);

		if (!ModelProcessor.HasMeshDataEntries())
		{
			return;
		}

		// #FIXME: Load the images before the meshes try to find them.

		Eng.FBXModel = Eng.Handles->GetModelHandles().CreateHandle();
		Eng.FBXModel->Init(ModelProcessor.GetMeshDataEntries(), Eng.Caches->GetImageCache());
	}
#pragma endregion

#pragma region (FBXImage) Initialize FBX Image
	{
#if RENDER_ENGINE_USE_BOX_EXAMPLE
		static const FChar* const LoadFile = "Assets/Textures/daggercolor.tga";
#elif RENDER_ENGINE_USE_DAGGER_EXAMPLE 
		static const FChar* const LoadFile = "Assets/Textures/daggercolor.tga";
#elif RENDER_ENGINE_USE_WIZARD_EXAMPLE 
		static const FChar* const LoadFile = "Assets/Textures/WizardGirlColor_Red.tga";
#endif

		FImageProcessor::FLoadParams LoadParams;
		LoadParams.File = LoadFile;
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

		Eng.FBXImage = Eng.Handles->GetImageHandles().CreateHandle();
		Eng.FBXImage->Init(InitParams);
		Eng.Caches->GetImageCache().AddEntry(LoadParams.File, Eng.FBXImage);
	}

	Eng.bIsDebugCodeInit = true;
#pragma endregion
}

void FGFXEngine::DebugRenderTestCode()
{
	// Note: This code is not truly meant to be 
	// clean and is for debugging purposes only.
	auto& Eng = Get();

	const bool ShouldReturn = !Eng.bIsDebugCodeInit;

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

	const FMatrix4D& ProjectionMatrix = Eng.Camera.GetProjection();
	const FMatrix4D& ViewMatrix = Eng.Camera.GetView();
	const FMatrix4D ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

	{
		const Float32 TimeStamp = FHighResolutionTimer::GetTimeInSeconds<Float32>();

#if RENDER_ENGINE_USE_BOX_EXAMPLE
		const Float32 Scale = 0.035f;
		const Float32 DefaultRotationX = 0.f;
		const Float32 XOffset = -0.5f;
		const Float32 YOffset = 0.f;
#elif RENDER_ENGINE_USE_DAGGER_EXAMPLE 
		const Float32 Scale = 0.035f;
		const Float32 DefaultRotationX = 0.f;
		const Float32 XOffset = -0.5f;
		const Float32 YOffset = 0.f;
#elif RENDER_ENGINE_USE_WIZARD_EXAMPLE 
		const Float32 Scale = 0.007f;
		const Float32 DefaultRotationX = -90.f;
		const Float32 XOffset = -0.3f;
		const Float32 YOffset = -0.25f;
#endif

		FMatrix4D WorldMatrix =
			glm::translate(Identity, FVector3D(XOffset, YOffset, 0)) *
			glm::rotate(Identity, glm::radians(DefaultRotationX), FVector3D(1, 0, 0)) *
			glm::rotate(Identity, glm::radians(TimeStamp * 30.f), FVector3D(0, 0, 1)) *
			glm::scale(Identity, FVector3D(Scale));

		FMatrix4D WorldViewProjectionMatrix = ViewProjectionMatrix * WorldMatrix;
		FMatrix3D ITWorldMatrix = FMatrix3D(glm::transpose(glm::inverse(WorldMatrix)));

		Eng.ModelShader->Enable();

		Eng.ModelShader->SetWorldViewProjectionPtr(WorldViewProjectionMatrix);
		Eng.ModelShader->SetInverseTransposeWorld(ITWorldMatrix);
		Eng.ModelShader->SetDiffuseMap(0);


		F_GL(GL::ClearColor(0.15f, 0.4f, 1.f, 1.f));

		// Note: #undefs exist for these defines.
#define PHOENIX_RENDER_ENGINE_TEST_MODEL Eng.FBXModel
#define PHOENIX_RENDER_ENGINE_TEST_IMG Eng.FBXImage
#define PHOENIX_RENDER_ENGINE_TEST_USE_DRAW_ARRAYS 0

#define PHOENIX_RENDER_ENGINE_TEST_DRAW_FBX_MODEL 1
#if PHOENIX_RENDER_ENGINE_TEST_DRAW_FBX_MODEL
		for (const auto& Mesh : PHOENIX_RENDER_ENGINE_TEST_MODEL->GetMeshes())
		{
			F_GL(GL::BindVertexArray(Mesh.GetVertexArray()));

			F_GL(GL::ActiveTexture(ETex::T0));
			PHOENIX_RENDER_ENGINE_TEST_IMG->Enable();

#	if PHOENIX_RENDER_ENGINE_TEST_USE_DRAW_ARRAYS
			F_GL(GL::DrawArrays(EMode::Triangles, 0, Mesh.GetVertexCount()));
#	else
			F_GL(GL::DrawElements(EMode::Triangles, Mesh.GetIndexCount(), Mesh.GetIndexType(), nullptr));
#	endif

			PHOENIX_RENDER_ENGINE_TEST_IMG->Disable();
			F_GL(GL::BindVertexArray(0));
		}
#endif

#define PHOENIX_RENDER_ENGINE_TEST_DRAW_ASSIMP_MODEL 1
#if PHOENIX_RENDER_ENGINE_TEST_DRAW_ASSIMP_MODEL
		WorldMatrix =
			glm::translate(Identity, FVector3D(0, 0, 0)) *
			glm::rotate(Identity, glm::radians(TimeStamp * 30.f), FVector3D(0, 1, 0)) *
			glm::scale(Identity, FVector3D(0.07f));

		WorldViewProjectionMatrix = ViewProjectionMatrix * WorldMatrix;
		ITWorldMatrix = FMatrix3D(glm::transpose(glm::inverse(WorldMatrix)));

		Eng.ModelShader->SetWorldViewProjectionPtr(WorldViewProjectionMatrix);
		Eng.ModelShader->SetInverseTransposeWorld(ITWorldMatrix);

		for (const auto& Mesh : Eng.Model->GetMeshes())
		{
			F_GL(GL::BindVertexArray(Mesh.GetVertexArray()));

			F_GL(GL::ActiveTexture(ETex::T0));
			Eng.Image->Enable();
			F_GL(GL::DrawElements(EMode::Triangles, Mesh.GetIndexCount(), Mesh.GetIndexType(), nullptr));
			Eng.Image->Disable();
			F_GL(GL::BindVertexArray(0));
		}
#endif

		Eng.ModelShader->Disable();
	}
}

#undef RENDER_ENGINE_USE_BOX_EXAMPLE
#undef RENDER_ENGINE_USE_DAGGER_EXAMPLE
#undef RENDER_ENGINE_USE_WIZARD_EXAMPLE

#undef PHOENIX_RENDER_ENGINE_TEST_MODEL
#undef PHOENIX_RENDER_ENGINE_TEST_IMG
#undef PHOENIX_RENDER_ENGINE_TEST_USE_DRAW_ARRAYS

#undef PHOENIX_RENDER_ENGINE_TEST_DRAW_FBX_MODEL
#undef PHOENIX_RENDER_ENGINE_TEST_DRAW_ASSIMP_MODEL