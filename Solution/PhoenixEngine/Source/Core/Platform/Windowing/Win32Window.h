#pragma once

#include "Core/Platform/Windowing/IWindow.h"
#include "Utility/Misc/Function.h"

typedef struct GLFWwindow FGLWindow;

namespace Phoenix
{
	class FWin32Window : public IWindow
	{

	public:

		FWin32Window() = delete;
		FWin32Window(int Width, int Height, const FString& WindowTitle);

		virtual ~FWin32Window();
		
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

		virtual void SetGraphicsContext(const FGraphicsContext& InContext);

		//Input
		typedef TFunction<void(Int32 Key, Int32 ScanCode, Int32 Action, Int32 Mods)> FWindowKeyPressCallback;
		typedef TFunction<void(Int32 Button, Int32 Action, Int32 Mods)> FWindowMouseClickCallback;
		typedef TFunction<void(Float64 XPos, Float64 YPos)> FWindowMouseMoveCallback;

		virtual void SetKeyPressCallback(const FWindowKeyPressCallback& KeyPressCallback);
		virtual void SetMouseButtonCallback(const FWindowMouseClickCallback& MouseClickCallback);
		virtual void SetMouseMoveCallback(const FWindowMouseMoveCallback& MouseMoveCallback);

	protected:

		virtual void Init() override;

	private:

		FGLWindow* Window;
		FWindowKeyPressCallback KeyPressCallback;
		FWindowMouseClickCallback MouseClickCallback;
		FWindowMouseMoveCallback MouseMoveCallback;

		//GLFW interface
		void OnKeyPressCallback(FGLWindow* Window, Int32 Key, Int32 ScanCode, Int32 Action, Int32 Mods);

	};
}
