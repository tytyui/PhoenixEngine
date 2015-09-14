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

		typedef TFunction<void(const FKeyboardEvent&)> FKeyPressCallback;
		typedef TFunction<void(const FMouseClickEvent&)> FMouseClickCallback;

		void Init(FWin32Window* Window);

		//Register for Input events
		void RegisterKeyPressCallback(const FKeyPressCallback& KeyPressCallback);
		void RegisterMouseClickCallback(const FMouseClickCallback& MouseClickCallback);

	private:

		//#FIXME will need to be updated to a proper data structure
		FKeyPressCallback KeyPressCallback;
		FMouseClickCallback MouseClickCallback;

		//Callbacks from the Windowing system
		void OnWindowKeyboardEvent(Int32 Key, Int32 ScanCode, Int32 Action, Int32 Mods) const;
		void OnWindowMouseClickEvent(Int32 Button, Int32 Action, Int32 Mods) const;

		//Broadcast Input Events
		void BroadcastKeyboardEvent(const FKeyboardEvent& KeyboardEvent) const;
		void BroadcastMouseClickEvent(const FMouseClickEvent& MouseClickEvent) const;

		//Helper functions to construct events from the ints that come from the Windowing system
		FKeyboardEvent CreateKeyboardEvent(Int32 Key, Int32 Action, Int32 Mods) const;
		FMouseClickEvent CreateMouseClickEvent(Int32 Button, Int32 Action, Int32 Mods) const;

		//Validation
		bool ValidateKeyCode(EKeyCode KeyCode) const;
		bool ValidateInputAction(EInputAction InputAction) const;
		bool ValidateKeyModifiers(EKeyModifier KeyMods) const;
		bool ValidateMouseButton(EMouseButton MouseButton) const;
	};
}
#endif


