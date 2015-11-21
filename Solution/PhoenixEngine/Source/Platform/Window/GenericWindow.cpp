#include "Platform/Window/GenericWindow.h"

#include "ExternalLib/GLFWIncludes.h"
#include "Utility/Debug/Assert.h"
#include "Utility/Debug/Debug.h"
#include "Platform/Event/EventHandler.h"
#include "Platform/Event/EventTypes.h"
#include "Platform/Input/KeyMods.h"
#include "Platform/Input/Keys.h"

using namespace Phoenix;

FGenericWindow::FGenericWindow(int Width, int Height, const FString& WindowTitle)
{
	Dimensions = FVector2D(Width, Height);
	WindowTitleText = WindowTitle;

	Init();
}

FGenericWindow::~FGenericWindow()
{

}

void FGenericWindow::Init()
{
	bIsHidden = false;
	bIsMinimized = false;
	bIsFullScreen = false;

	glfwInit();

	// Also working out a better way for this, but one thing at a time...
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// This creation stuff will need to be adjusted both design and otherwise 
	// when we think about fullscreen and multi-monitor issues
	Window = glfwCreateWindow(static_cast<int>(Dimensions.x), static_cast<int>(Dimensions.y), WindowTitleText.c_str(), nullptr, nullptr);

	if (!Window)
	{
		F_LogError("Failed to create window.");
		return;
	}

	bIsHidden = glfwGetWindowAttrib(Window, GLFW_VISIBLE) == GL_FALSE;

	glfwSetWindowUserPointer(Window, this);

	glfwSetWindowCloseCallback(Window, &FGenericWindow::WindowCloseAttemptCallback);
	glfwSetWindowFocusCallback(Window, &FGenericWindow::WindowFocusedCallback);
	glfwSetFramebufferSizeCallback(Window, &FGenericWindow::WindowFrameBufferResizedCallback);
	glfwSetWindowIconifyCallback(Window, &FGenericWindow::WindowIconifiedCallback);
	glfwSetWindowPosCallback(Window, &FGenericWindow::WindowPositionChangedCallback);
	glfwSetWindowRefreshCallback(Window, &FGenericWindow::WindowRefreshedCallback);
	glfwSetWindowSizeCallback(Window, &FGenericWindow::WindowSizeChangedCallback);
	glfwSetCursorEnterCallback(Window, &FGenericWindow::CursorEnterCallback);
	glfwSetCursorPosCallback(Window, &FGenericWindow::CursorPosCallback);
	glfwSetKeyCallback(Window, &FGenericWindow::KeyCallback);
	glfwSetMouseButtonCallback(Window, &FGenericWindow::MouseButtonCallback);
	glfwSetScrollCallback(Window, &FGenericWindow::ScrollCallback);

	F_AssertNotNull(glfwGetWindowUserPointer(Window), "GLFW User Ptr Null");
}

void FGenericWindow::Hide()
{
	if (!bIsHidden)
	{
		glfwHideWindow(Window);
		bIsHidden = true;
	}
}

void FGenericWindow::Show()
{
	if (bIsHidden)
	{
		glfwShowWindow(Window);
		bIsHidden = false;
	}
}

void FGenericWindow::Minimize()
{
	if (!bIsMinimized)
	{
		glfwIconifyWindow(Window);
		bIsMinimized = true;

		OnMinimize();
	}
}

void FGenericWindow::Restore()
{
	if (bIsMinimized)
	{
		glfwRestoreWindow(Window);
		bIsMinimized = false;

		OnRestore();
	}
}

void FGenericWindow::BufferSwap()
{
	glfwSwapBuffers(Window);
}

void FGenericWindow::SetSwapInterval(const Int32 Interval)
{
	glfwSwapInterval(Interval);
}

void FGenericWindow::OnMinimize()
{
	// TODO::Implement me
}

void FGenericWindow::OnRestore()
{
	// TODO::Implement me
}

void FGenericWindow::SetEventHandler(const TRawPtr<class FEventHandler>& InEventHandler)
{
	EventHandler = InEventHandler;
}

void FGenericWindow::SetFullScreen(const bool bFullScreenEnabled)
{
	// TODO::Implement me
}

void FGenericWindow::ProcessEvents()
{
	glfwPollEvents();
}

void FGenericWindow::SetDimensions(const FVector2D& InDimensions)
{
	// Do checks/requisite functions when the dimensions change
	Dimensions = InDimensions;
}

const FVector2D& FGenericWindow::GetDimensions() const
{
	return Dimensions;
}

void FGenericWindow::SetPosition(const FVector2D& InPosition)
{
	// Do checks/requisite functions when the position changes
	Position = InPosition;
}

const FVector2D& FGenericWindow::GetPosition() const
{
	return Position;
}

void FGenericWindow::SetWindowTitle(const FString& InWindowTitleText)
{
	// Do checks/requisite functions when the window title changes
	WindowTitleText = InWindowTitleText;
}

const FString& FGenericWindow::GetWindowTitle() const
{
	return WindowTitleText;
}

void FGenericWindow::SetTaskbarIcon(const FIcon& InIcon)
{
	// Do checks/requisite functions when the taskbar icon changes
	TaskbarIcon = InIcon;
}

const FIcon& FGenericWindow::GetTaskbarIcon() const
{
	return TaskbarIcon;
}

void FGenericWindow::SetTitlebarIcon(const FIcon& InIcon)
{
	// Do checks/requisite functions when the titlebar changes
	TitlebarIcon = InIcon;
}

const FIcon& FGenericWindow::GetTitlebarIcon() const
{
	return TitlebarIcon;
}

void FGenericWindow::SetGraphicsContextCurrent()
{
	glfwMakeContextCurrent(Window);
}

FGenericWindow& FGenericWindow::GetClass(GLFWwindow* const Instance)
{
	void* const Ptr = glfwGetWindowUserPointer(Instance);
	FGenericWindow* const WindowPtr = static_cast<FGenericWindow*>(Ptr);
	FGenericWindow& WindowRef = *WindowPtr;
	return WindowRef;
}

void FGenericWindow::WindowCloseAttemptCallback(GLFWwindow* Instance)
{
	auto& Ref = GetClass(Instance);
	Ref.EventHandler->WindowCloseAttemptCallback();
}

void FGenericWindow::WindowFocusedCallback(GLFWwindow* Instance, Int32 IsFocused)
{
	auto& Ref = GetClass(Instance);
	Ref.EventHandler->WindowFocusedCallback(IsFocused);
}

void FGenericWindow::WindowFrameBufferResizedCallback(GLFWwindow* Instance, Int32 Width, Int32 Height)
{
	auto& Ref = GetClass(Instance);
	Ref.EventHandler->WindowFrameBufferResizedCallback(Width, Height);
}

void FGenericWindow::WindowIconifiedCallback(GLFWwindow* Instance, Int32 IsIconified)
{
	auto& Ref = GetClass(Instance);
	Ref.EventHandler->WindowIconifiedCallback(IsIconified);
}

void FGenericWindow::WindowPositionChangedCallback(GLFWwindow* Instance, Int32 X, Int32 Y)
{
	auto& Ref = GetClass(Instance);
	Ref.EventHandler->WindowPositionChangedCallback(X, Y);
}

void FGenericWindow::WindowRefreshedCallback(GLFWwindow* Instance)
{
	auto& Ref = GetClass(Instance);
	Ref.EventHandler->WindowRefreshedCallback();
}

void FGenericWindow::WindowSizeChangedCallback(GLFWwindow* Instance, Int32 Width, Int32 Height)
{
	auto& Ref = GetClass(Instance);
	Ref.EventHandler->WindowSizeChangedCallback(Width, Height);
}

void FGenericWindow::CursorEnterCallback(GLFWwindow* Instance, Int32 DidEnterArea)
{
	auto& Ref = GetClass(Instance);
	Ref.EventHandler->CursorEnterCallback(DidEnterArea);
}

void FGenericWindow::CursorPosCallback(GLFWwindow* Instance, Float64 CursorX, Float64 CursorY)
{
	auto& Ref = GetClass(Instance);
	Ref.EventHandler->CursorPosCallback(static_cast<Float32>(CursorX), static_cast<Float32>(CursorY));
}

void FGenericWindow::KeyCallback(GLFWwindow* Instance, Int32 Key, Int32 ScanCode, Int32 Action, Int32 Mods)
{
	auto& Ref = GetClass(Instance);

	const EInputAction::Value InputAction = static_cast<EInputAction::Value>(Action);

	switch (InputAction)
	{
		case EInputAction::Release:
		case EInputAction::Press:
		{
			const EKeyEventType::Value KeyEventType = EKeyEventType::Default;
			const EKey::Value InputKey = static_cast<EKey::Value>(Key);
			const EKeyMods::BitMask InputMods = static_cast<EKeyMods::BitMask>(Mods);
			const Float32 TimeStamp = 0.f;

			Ref.EventHandler->KeyCallback(KeyEventType, InputKey, InputAction, InputMods, TimeStamp);
			break;
		}

		case EInputAction::Repeat:
		{
			// Note: This is intentionally ignored, because this event is not what you
			// often want in games, and the cost of sending this otherwise unnecessary 
			// event to each class that receives input simply isn't worth it.
			break;
		}

		default:
		{
			F_Assert(false, "Invalid input action or unsupported enum with a value of " << InputAction);
			break;
		}
	}
}

void FGenericWindow::UnicodeKeyCallback(GLFWwindow* Instance, UInt32 Key, Int32 Mods)
{
	auto& Ref = GetClass(Instance);
	Ref.EventHandler->UnicodeKeyCallback(Key, Mods);
}

void FGenericWindow::MouseButtonCallback(GLFWwindow* Instance, Int32 Button, Int32 Action, Int32 Mods)
{
	auto& Ref = GetClass(Instance);

	const EMouseEventType::Value MouseEventType = EMouseEventType::Default;
	const EMouseButton::Value MouseButton = static_cast<EMouseButton::Value>(Button);
	const EInputAction::Value InputAction = static_cast<EInputAction::Value>(Action);
	const EKeyMods::BitMask InputMods = static_cast<EKeyMods::BitMask>(Mods);
	const Float32 TimeStamp = 0.f;

	switch (InputAction)
	{
		case EInputAction::Release:
		case EInputAction::Press:
		{
			Ref.EventHandler->MouseButtonCallback(MouseEventType, MouseButton, InputAction, InputMods, TimeStamp);
			break;
		}

		case EInputAction::Repeat:
		{
			// Note: This is intentionally ignored, because this event is not what you
			// often want in games, and the cost of sending this otherwise unnecessary 
			// event to each class that receives input simply isn't worth it.
			break;
		}

		default:
		{
			F_Assert(false, "Invalid input action or unsupported enum with a value of " << InputAction);
			break;
		}
	}
}

void FGenericWindow::ScrollCallback(GLFWwindow* Instance, Float64 DeltaX, Float64 DeltaY)
{
	auto& Ref = GetClass(Instance);
	Ref.EventHandler->ScrollCallback(static_cast<Float32>(DeltaX), static_cast<Float32>(DeltaY));
}
