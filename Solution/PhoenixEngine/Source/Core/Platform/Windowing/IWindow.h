#pragma once

#include "Math/Math.h"
#include "Math/Vector2D.h"

#include "Utility/Misc/String.h"

namespace Phoenix
{
	class FGraphicsContext;

	class FIcon
	{

	public:
		// JOSH::NOTE
		// Temp class so I can do stuff with this, like place it on the stack.
		// Didn't know where to put it or what we expect from it, and just wanted
		// to get stuff going.
		FIcon() = default;
		~FIcon() {}

	};

	class IWindow
	{

	public:

		IWindow() = default;
		IWindow(const IWindow&) = delete;
		const IWindow& operator=(const IWindow&) = delete;

		virtual ~IWindow() {}

		// Hide / Show
		virtual void Hide() = 0;
		virtual void Show() = 0;

		// Minimize / Restore
		virtual void Minimize() = 0;
		virtual void Restore() = 0;

		virtual void OnMinimize() = 0;
		virtual void OnRestore() = 0;

		// Enter / Exit Full Screen
		virtual void SetFullScreen(const bool bFullScreenEnabled) = 0;

		// EventPolling
		// Any other required Event stuff
		virtual void ProcessEvents() = 0;

		// Setting size
		virtual void SetDimensions(const FVector2D& InDimensions) = 0;
		// Getting size
		virtual const FVector2D& GetDimensions() const = 0;

		// Set position
		virtual void SetPosition(const FVector2D& InPosition) = 0;
		// Get position
		virtual const FVector2D& GetPosition() const = 0;

		// Set Title
		virtual void SetWindowTitle(const FString& InWindowTitleText) = 0;
		virtual const FString& GetWindowTitle() const = 0;

		// Set Icon
		virtual void SetTaskbarIcon(const FIcon& InIcon) = 0;
		virtual const FIcon& GetTaskbarIcon() const = 0;

		// Set Title Icon
		virtual void SetTitlebarIcon(const FIcon& InIcon) = 0;
		virtual const FIcon& GetTitlebarIcon() const = 0;

	protected:

		virtual void Init() = 0;

		bool bIsHidden;
		bool bIsMinimized;
		bool bIsFullScreen;

		FIcon TaskbarIcon;
		FIcon TitlebarIcon;

		FVector2D Position;
		FVector2D Dimensions;

		FString WindowTitleText;
	};
}
