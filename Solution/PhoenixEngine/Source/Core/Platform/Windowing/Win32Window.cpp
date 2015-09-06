#include "Core/Platform/Windowing/Win32Window.h"

#ifdef _DEBUG
#	pragma comment (lib, "glew32sd.lib")
#else
#	pragma comment (lib, "glew32s.lib")
#endif

#pragma comment (lib, "opengl32.lib")

#pragma comment (lib, "glfw3.lib")

#include "Rendering/GLIncludes.h"

using namespace Phoenix;

FWin32Window::FWin32Window(int Width, int Height, const FString& WindowTitle)
{
	Dimensions = FVector2D(Width, Height);
	WindowTitleText = WindowTitle;

	Init();
}

Phoenix::FWin32Window::~FWin32Window()
{
	
}

void FWin32Window::Init()
{
	glfwInit();

	// Also working out a better way for this, but one thing at a time...
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// This creation stuff will need to be adjusted both design and otherwise 
	// when we think about fullscreen and multi-monitor issues
	Window = glfwCreateWindow(static_cast<int>(Dimensions.x), static_cast<int>(Dimensions.y), WindowTitleText.c_str(), nullptr, nullptr);

	glfwMakeContextCurrent(Window);

	// This should very soon also be handled by a GLEW layer
	glewExperimental = true;
	int GLEWInitStatus = glewInit();
	if (!GLEWInitStatus)
	{
		// 99 Problems, successful init ain't one
	}
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

void Phoenix::FWin32Window::Minimize()
{
	if (!bIsMinimized)
	{
		glfwIconifyWindow(Window);
		bIsMinimized = true;

		OnMinimize();
	}
}

void Phoenix::FWin32Window::Restore()
{
	if (bIsMinimized)
	{
		glfwRestoreWindow(Window);
		bIsMinimized = false;

		OnRestore();
	}
}

void FWin32Window::OnMinimize()
{
	
}

void FWin32Window::OnRestore()
{

}

void FWin32Window::SetFullScreen(const bool bFullScreenEnabled)
{
	
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

void FWin32Window::SetGraphicsContext(const FGraphicsContext& InContext)
{
}
