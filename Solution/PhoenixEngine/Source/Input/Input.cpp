#include "Input/Input.h"
#include "Core/Platform/Windowing/Win32Window.h"
#include "Utility/Debug/Assert.h"

using namespace Phoenix;

void FInput::Init(FWin32Window* Window)
{
	F_Assert_NotNull(Window, "Window is Null");

	Window->SetKeyPressCallback
		([this](Int32 Key, Int32 ScanCode, Int32 Action, Int32 Mods) 
		{
			OnWindowKeyboardEvent(Key, ScanCode, Action, Mods);
		});
}

void FInput::RegisterKeyPressCallback(const FKeyPressCallback& KeyPressCallback)
{
	F_Assert_NotNull(KeyPressCallback, "KeyPressCallback is null");
	this->KeyPressCallback = KeyPressCallback;
}

void FInput::OnWindowKeyboardEvent(Int32 Key, Int32 ScanCode, Int32 Action, Int32 Mods)
{
	BroadcastKeyboardEvent(CreateKeyboardEvent(Key, Action, Mods));
}

void FInput::BroadcastKeyboardEvent(const FKeyboardEvent& KeyboardEvent)
{
	if (KeyPressCallback)
	{
		KeyPressCallback(KeyboardEvent);
	}
}

FKeyboardEvent FInput::CreateKeyboardEvent(Int32 Key, Int32 Action, Int32 Mods)
{
	const EKeyCode KeyCode = static_cast<EKeyCode>(Key);
	F_Assert(ValidateKeyCode(KeyCode), "Invalid KeyCode");

	const EInputAction InputAction = static_cast<EInputAction>(Action);
	F_Assert(ValidateInputAction(InputAction), "Invalid Input Action");

	const EKeyModifier KeyMods = static_cast<EKeyModifier>(Mods);
	F_Assert(ValidateKeyModifiers(KeyMods), "Invalid Key Mods");

	return FKeyboardEvent(KeyCode, InputAction, KeyMods);
}

bool FInput::ValidateKeyCode(EKeyCode KeyCode) const
{
	if (KeyCode == EKeyCode::Unknown)
	{
		return false;
	}

	const Int32 IntKey = static_cast<Int32>(KeyCode);
	const bool ValidKeyCode =
		//Alphabet
		(IntKey >= 65 && IntKey <= 90)
		//Numeric
		|| (IntKey >= 48 && IntKey <= 57)
		//Symbols
		|| IntKey == 32 || IntKey == 39
		|| (IntKey >= 44 && IntKey <= 47)
		|| IntKey == 59 || IntKey == 61
		|| (IntKey >= 91 && IntKey <= 93)
		|| IntKey == 96
		//Function Keys
		|| (IntKey >= 256 && IntKey <= 269)
		|| (IntKey >= 280 && IntKey <= 284)
		|| (IntKey >= 290 && IntKey <= 314)
		|| (IntKey >= 320 && IntKey <= 336)
		|| (IntKey >= 340 && IntKey <= 346);

	return ValidKeyCode;
}

bool FInput::ValidateInputAction(EInputAction InputAction) const
{
	const bool ValidInputAction = 
		(InputAction != EInputAction::Unknown)
		&& (InputAction == EInputAction::Release
			|| InputAction == EInputAction::Press
			|| InputAction == EInputAction::Hold);

	return ValidInputAction;
}

bool FInput::ValidateKeyModifiers(EKeyModifier KeyMods) const
{
	const Int32 IntKeyMods = static_cast<Int32>(KeyMods);
	
	const bool ValidKeyMod = IntKeyMods >= 0 && IntKeyMods <= 7;

	return ValidKeyMod;
}

bool FInput::ValidateMouseButton(EMouseButton MouseButton) const
{
	const Int32 IntMouseButton = static_cast<Int32>(MouseButton);

	const bool ValidMouseButton = IntMouseButton >= 0 && IntMouseButton <= 8;

	return ValidMouseButton;
}

