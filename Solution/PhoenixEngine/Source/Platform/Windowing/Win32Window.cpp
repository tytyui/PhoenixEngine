#include "Platform/Windowing/Win32Window.h"

#include "ExternalLib/GLFWIncludes.h"
#include "Utility/Debug/Assert.h"

using namespace Phoenix;

FWin32Window::FWin32Window(int Width, int Height, const FString& WindowTitle)
{
	Dimensions = FVector2D(Width, Height);
	WindowTitleText = WindowTitle;

	Init();
}

FWin32Window::~FWin32Window()
{
	
}

void FWin32Window::Init()
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

	bIsHidden = glfwGetWindowAttrib(Window, GLFW_VISIBLE) == GL_FALSE;

	//Input
	{
		//Hacky way of getting GLFW to accept member functions as callbacks (other options are to make it static, or to use a singleton)

		glfwSetWindowUserPointer(Window, this);
		F_AssertNotNull(glfwGetWindowUserPointer(Window), "GLFW User Ptr Null");

		//Key Press
		auto KeyPressCallback = [](GLFWwindow* Window, Int32 Key, Int32 ScanCode, Int32 Action, Int32 Mods)
		{
			static_cast<FWin32Window*>(glfwGetWindowUserPointer(Window))->OnKeyPress(Window, Key, ScanCode, Action, Mods);
		};
		glfwSetKeyCallback(Window, KeyPressCallback);

		auto MouseClickCallback = [](GLFWwindow* Window, Int32 Button, Int32 Action, Int32 Mods)
		{
			static_cast<FWin32Window*>(glfwGetWindowUserPointer(Window))->OnMouseClick(Window, Button, Action, Mods);
		};
		glfwSetMouseButtonCallback(Window, MouseClickCallback);
	}
}

void FWin32Window::OnKeyPress(FGLWindow * Window, Int32 Key, Int32 ScanCode, Int32 Action, Int32 Mods) const
{
	F_AssertNotNull(KeyPressCallback, "Key press Callback not set");
	KeyPressCallback(Key, ScanCode, Action, Mods);
}

void FWin32Window::OnMouseClick(FGLWindow* Window, Int32 Button, Int32 Action, Int32 Mods) const
{
	F_AssertNotNull(MouseClickCallback, "Mouse Click Callback not set");
	MouseClickCallback(Button, Action, Mods);
}

void FWin32Window::OnMouseMove(FGLWindow* Window, Float64 XPos, Float64 YPos) const
{
	F_AssertNotNull(MouseMoveCallback, "Mouse Move Callback not set");
	MouseMoveCallback(XPos, YPos);
}

void FWin32Window::Hide()
{
	if (!bIsHidden)
	{
		glfwHideWindow(Window);
		bIsHidden = true;
	}
}

void FWin32Window::Show()
{
	if (bIsHidden)
	{
		glfwShowWindow(Window);
		bIsHidden = false;
	}
}

void FWin32Window::Minimize()
{
	if (!bIsMinimized)
	{
		glfwIconifyWindow(Window);
		bIsMinimized = true;

		OnMinimize();
	}
}

void FWin32Window::Restore()
{
	if (bIsMinimized)
	{
		glfwRestoreWindow(Window);
		bIsMinimized = false;

		OnRestore();
	}
}

void FWin32Window::SetKeyPressCallback(const FWindowKeyPressCallback& KeyPressCallback)
{
	F_AssertNotNull(KeyPressCallback, "Key Press Callback is Null");
	this->KeyPressCallback = KeyPressCallback;
}

void FWin32Window::SetMouseClickCallback(const FWindowMouseClickCallback& MouseClickCallback)
{
	F_AssertNotNull(MouseClickCallback, "Mouse Click Callback is Null");
	this->MouseClickCallback = MouseClickCallback;
}

void FWin32Window::SetMouseMoveCallback(const FWindowMouseMoveCallback& MouseMoveCallback)
{
	F_AssertNotNull(MouseMoveCallback, "Mouse Move Callback is Null");
	this->MouseMoveCallback = MouseMoveCallback;
}

void FWin32Window::BufferSwap()
{
	glfwSwapBuffers(Window);
}

void FWin32Window::OnMinimize()
{
	// TODO::Implement me
}

void FWin32Window::OnRestore()
{
	// TODO::Implement me
}

void FWin32Window::SetFullScreen(const bool bFullScreenEnabled)
{
	// TODO::Implement me
}

void FWin32Window::ProcessEvents()
{
	glfwPollEvents();
}

void FWin32Window::SetDimensions(const FVector2D& InDimensions)
{
	// Do checks/requisite functions when the dimensions change
	Dimensions = InDimensions;
}

const FVector2D& FWin32Window::GetDimensions() const
{
	return Dimensions;
}

void FWin32Window::SetPosition(const FVector2D& InPosition)
{
	// Do checks/requisite functions when the position changes
	Position = InPosition;
}

const FVector2D& FWin32Window::GetPosition() const
{
	return Position;
}

void FWin32Window::SetWindowTitle(const FString& InWindowTitleText)
{
	// Do checks/requisite functions when the window title changes
	WindowTitleText = InWindowTitleText;
}

const FString& FWin32Window::GetWindowTitle() const
{
	return WindowTitleText;
}

void FWin32Window::SetTaskbarIcon(const FIcon& InIcon)
{
	// Do checks/requisite functions when the taskbar icon changes
	TaskbarIcon = InIcon;
}

const FIcon& FWin32Window::GetTaskbarIcon() const
{
	return TaskbarIcon;
}

void FWin32Window::SetTitlebarIcon(const FIcon& InIcon)
{
	// Do checks/requisite functions when the titlebar changes
	TitlebarIcon = InIcon;
}

const FIcon& FWin32Window::GetTitlebarIcon() const
{
	return TitlebarIcon;
}

void FWin32Window::SetGraphicsContextCurrent()
{
	glfwMakeContextCurrent(Window);
}
