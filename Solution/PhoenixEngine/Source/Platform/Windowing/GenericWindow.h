#ifndef PHOENIX_WIN32_WINDOW_H
#define PHOENIX_WIN32_WINDOW_H

#include "Utility/Misc/Function.h"
#include "Platform/Windowing/IWindow.h"

typedef struct GLFWwindow FGLWindow;

namespace Phoenix
{
	class FGenericWindow : public IWindow
	{
	public:

		FGenericWindow() = delete;
		FGenericWindow(int Width, int Height, const FString& WindowTitle);

		virtual ~FGenericWindow();
		
		virtual void Hide() override;
		virtual void Show() override;

		virtual void Minimize() override;
		virtual void Restore() override;

		virtual void OnMinimize() override;
		virtual void OnRestore() override;

		virtual void SetFullScreen(const bool bFullScreenEnabled) override;
		
		virtual void ProcessEvents() override;

		virtual void SetDimensions(const FVector2D& InDimensions) override;
		virtual const FVector2D& GetDimensions() const override;

		virtual void SetPosition(const FVector2D& InPosition) override;
		virtual const FVector2D& GetPosition() const override;

		virtual void SetWindowTitle(const FString& InWindowTitleText) override;
		virtual const FString& GetWindowTitle() const override;

		virtual void SetTaskbarIcon(const FIcon& InIcon) override;
		virtual const FIcon& GetTaskbarIcon() const override;

		virtual void SetTitlebarIcon(const FIcon& InIcon) override;
		virtual const FIcon& GetTitlebarIcon() const override;

		virtual void SetGraphicsContextCurrent() override;

		virtual void BufferSwap() override;

		virtual void SetSwapInterval(const Int32 Interval) override;

		//Input
		typedef TFunction<void(Int32 Key, Int32 ScanCode, Int32 Action, Int32 Mods)> FWindowKeyPressCallback;
		typedef TFunction<void(Int32 Button, Int32 Action, Int32 Mods)> FWindowMouseClickCallback;
		typedef TFunction<void(Float64 XPos, Float64 YPos)> FWindowMouseMoveCallback;

		virtual void SetKeyPressCallback(const FWindowKeyPressCallback& KeyPressCallback);
		virtual void SetMouseClickCallback(const FWindowMouseClickCallback& MouseClickCallback);
		virtual void SetMouseMoveCallback(const FWindowMouseMoveCallback& MouseMoveCallback);

	protected:

		virtual void Init() override;

	private:

		FGLWindow* Window;
		FWindowKeyPressCallback KeyPressCallback;
		FWindowMouseClickCallback MouseClickCallback;
		FWindowMouseMoveCallback MouseMoveCallback;

		//GLFW Input Interface
		void OnKeyPress(FGLWindow* Window, Int32 Key, Int32 ScanCode, Int32 Action, Int32 Mods) const;
		void OnMouseClick(FGLWindow* Window, Int32 Button, Int32 Action, Int32 Mods) const;
		void OnMouseMove(FGLWindow* Window, Float64 XPos, Float64 YPos) const;

	};
}

#endif