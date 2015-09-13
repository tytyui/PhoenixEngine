#ifndef PHOENIX_INPUT_H
#define PHOENIX_INPUT_H

#include "input/KeyboardEvent.h"
#include "Input/MouseClickEvent.h"
#include "Utility/Misc/Function.h"
#include "Utility/Misc/Primitives.h"
#include "Utility/Misc/Singleton.h"

namespace Phoenix
{
	class FWin32Window;

	class FInput
	{
	public:
		FInput() = default;

		FInput(const FInput&) = delete;
		FInput& operator=(const FInput&) = delete;

		FInput(FInput&&) = default;
		FInput& operator=(FInput&&) = default;

		~FInput() = default;

		typedef std::function<void(const FKeyboardEvent&)> FKeyPressCallback;

		void Init(FWin32Window* Window);

		//Register for Input events
		void RegisterKeyPressCallback(const FKeyPressCallback& KeyPressCallback);

	private:

		FKeyPressCallback KeyPressCallback;

		//Callbacks from the Windowing system
		void OnWindowKeyboardEvent(Int32 Key, Int32 ScanCode, Int32 Action, Int32 Mods);

		//Broadcast Input Events
		void BroadcastKeyboardEvent(const FKeyboardEvent& KeyboardEvent);

		//Helper functions to construct events from the ints that come from the Windowing system
		FKeyboardEvent CreateKeyboardEvent(Int32 Key, Int32 Action, Int32 Mods);

		//Validation
		bool ValidateKeyCode(EKeyCode KeyCode) const;
		bool ValidateInputAction(EInputAction InputAction) const;
		bool ValidateKeyModifiers(EKeyModifier KeyMods) const;
		bool ValidateMouseButton(EMouseButton MouseButton) const;
	};
}
#endif


