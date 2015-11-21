#ifndef PHOENIX_EVENT_HANDLER_H
#define PHOENIX_EVENT_HANDLER_H

#include "Utility/Containers/Vector.h"
#include "Utility/Misc/Primitives.h"
#include "Utility/Misc/StaticObject.h"
#include "Platform/Event/Event.h"
#include "Platform/Event/EventTypes.h"
#include "Platform/Input/InputAction.h"
#include "Platform/Input/KeyMods.h"
#include "Platform/Input/Keys.h"
#include "Platform/Input/MouseButton.h"

namespace Phoenix
{
	class FEventHandler
	{
		F_AddStaticObjectToClass(FEventHandler);
	public:
		FEventHandler() = default;

		FEventHandler(const FEventHandler&) = delete;
		FEventHandler& operator=(const FEventHandler&) = delete;

		FEventHandler(FEventHandler&&) = delete;
		FEventHandler& operator=(FEventHandler&&) = delete;

		TVector<FEvent>& GetEvents();

		void EventCallback(const FEvent& Event);

		void WindowCloseAttemptCallback();

		void WindowFocusedCallback(const Int32 IsFocused);

		void WindowFrameBufferResizedCallback(const Int32 Width, const Int32 Height);

		void WindowIconifiedCallback(const Int32 IsIconified);

		void WindowPositionChangedCallback(const Int32 X, const Int32 Y);

		void WindowRefreshedCallback();

		void WindowSizeChangedCallback(const Int32 Width, const Int32 Height);

		void CursorEnterCallback(const Int32 DidEnterArea);

		void CursorPosCallback(const Float32 CursorX, const Float32 CursorY);

		template <class... Arguments>
		void KeyCallback(Arguments&&... Args);

		void UnicodeKeyCallback(const UInt32 Key, const Int32 Mods);

		template <class... Arguments>
		void MouseButtonCallback(Arguments&&... Args);

		void ScrollCallback(const Float32 DeltaX, const Float32 DeltaY);

	protected:
	private:
		TVector<FEvent> Events;

		void AddEvent(const FEvent& Event);
	};

	template <class... Arguments>
	void FEventHandler::KeyCallback(Arguments&&... Args)
	{
		FEvent Event;
		Event.Key = FKeyEvent(std::forward<Arguments>(Args)...);

		AddEvent(Event);
	}

	template <class... Arguments>
	void FEventHandler::MouseButtonCallback(Arguments&&... Args)
	{
		FEvent Event;
		Event.Mouse = FMouseEvent(std::forward<Arguments>(Args)...);

		AddEvent(Event);
	}
}

#endif
