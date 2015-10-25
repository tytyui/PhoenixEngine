#include "Platform/Windowing/GenericWindow.h"

#include "ExternalLib/GLFWIncludes.h"
#include "Utility/Debug/Assert.h"

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

	bIsHidden = glfwGetWindowAttrib(Window, GLFW_VISIBLE) == GL_FALSE;

	//Input
	{
		//Hacky way of getting GLFW to accept member functions as callbacks (other options are to make it static, or to use a singleton)

		glfwSetWindowUserPointer(Window, this);
		F_AssertNotNull(glfwGetWindowUserPointer(Window), "GLFW User Ptr Null");

		//Key Press
		auto KeyPressCallback = [](GLFWwindow* Window, Int32 Key, Int32 ScanCode, Int32 Action, Int32 Mods)
		{
			static_cast<FGenericWindow*>(glfwGetWindowUserPointer(Window))->OnKeyPress(Window, Key, ScanCode, Action, Mods);
		};
		glfwSetKeyCallback(Window, KeyPressCallback);

		auto MouseClickCallback = [](GLFWwindow* Window, Int32 Button, Int32 Action, Int32 Mods)
		{
			static_cast<FGenericWindow*>(glfwGetWindowUserPointer(Window))->OnMouseClick(Window, Button, Action, Mods);
		};
		glfwSetMouseButtonCallback(Window, MouseClickCallback);
	}
}

void FGenericWindow::OnKeyPress(FGLWindow * Window, Int32 Key, Int32 ScanCode, Int32 Action, Int32 Mods) const
{
	// #FIXME: If check is temporary for these callbacks.  Eventually, dummy functions will be used.
	if (KeyPressCallback)
	{
		KeyPressCallback(Key, ScanCode, Action, Mods);
	}
}

void FGenericWindow::OnMouseClick(FGLWindow* Window, Int32 Button, Int32 Action, Int32 Mods) const
{
	if (MouseClickCallback)
	{
		MouseClickCallback(Button, Action, Mods);
	}
}

void FGenericWindow::OnMouseMove(FGLWindow* Window, Float64 XPos, Float64 YPos) const
{
	if (MouseMoveCallback)
	{
		MouseMoveCallback(XPos, YPos);
	}
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

void FGenericWindow::SetKeyPressCallback(const FWindowKeyPressCallback& KeyPressCallback)
{
	F_AssertNotNull(KeyPressCallback, "Key Press Callback is Null");
	this->KeyPressCallback = KeyPressCallback;
}

void FGenericWindow::SetMouseClickCallback(const FWindowMouseClickCallback& MouseClickCallback)
{
	F_AssertNotNull(MouseClickCallback, "Mouse Click Callback is Null");
	this->MouseClickCallback = MouseClickCallback;
}

void FGenericWindow::SetMouseMoveCallback(const FWindowMouseMoveCallback& MouseMoveCallback)
{
	F_AssertNotNull(MouseMoveCallback, "Mouse Move Callback is Null");
	this->MouseMoveCallback = MouseMoveCallback;
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
