#ifndef PHOENIX_KEYBOARD_EVENT_H
#define PHOENIX_KEYBOARD_EVENT_H

#include "Input/KeyCode.h"
#include "Input/InputAction.h"
#include "Input/KeyModifier.h"

namespace Phoenix
{
	/*!
	 * \brief This struct contains Key press info and is sent by the Keyboard Callback from FInput
	 */
	struct FKeyboardEvent
	{
		EKeyCode KeyCode = EKeyCode::Unknown;
		EInputAction InputAction = EInputAction::Unknown;
		EKeyModifier KeyModifiers = EKeyModifier::None;

		FKeyboardEvent() = default;

		FKeyboardEvent(EKeyCode KeyCode, EInputAction InputAction, EKeyModifier KeyModifiers)
			: KeyCode(KeyCode)
			, InputAction(InputAction)
			, KeyModifiers(KeyModifiers)
		{}

	};
}
#endif
