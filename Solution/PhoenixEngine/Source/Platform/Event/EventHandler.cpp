#include "Platform/Event/EventHandler.h"

using namespace Phoenix;

TVector<FEvent>& FEventHandler::GetEvents()
{
	return Events;
}

void FEventHandler::EventCallback(const FEvent& Event)
{
	AddEvent(Event);
}

void FEventHandler::WindowCloseAttemptCallback()
{

}

void FEventHandler::WindowFocusedCallback(const Int32 IsFocused)
{

}

void FEventHandler::WindowFrameBufferResizedCallback(const Int32 Width, const Int32 Height)
{
}

void FEventHandler::WindowIconifiedCallback(const Int32 IsIconified)
{
}

void FEventHandler::WindowPositionChangedCallback(const Int32 X, const Int32 Y)
{
}

void FEventHandler::WindowRefreshedCallback()
{
}

void FEventHandler::WindowSizeChangedCallback(const Int32 Width, const Int32 Height)
{
}

void FEventHandler::CursorEnterCallback(const Int32 DidEnterArea)
{
}

void FEventHandler::CursorPosCallback(const Float32 CursorX, const Float32 CursorY)
{
}

void FEventHandler::KeyCallback(
	const EKeyEventType::Value SubType,
	const EKey::Value Key,
	const EInputAction::Value Action,
	const EKeyMods::BitMask Mods,
	const Float32 TimeStamp)
{
	FEvent Event;
	Event.Key = FKeyEvent(SubType, Key, Action, Mods, 0.f);

	AddEvent(Event);
}

void FEventHandler::UnicodeKeyCallback(const UInt32 Key, const Int32 Mods)
{
}

void FEventHandler::MouseButtonCallback(const Int32 Button, const Int32 Action, const Int32 Mods)
{
}

void FEventHandler::ScrollCallback(const Float32 DeltaX, const Float32 DeltaY)
{
}

void FEventHandler::AddEvent(const FEvent& Event)
{
	Events.push_back(Event);
}