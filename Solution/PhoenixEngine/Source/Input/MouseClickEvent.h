#ifndef PHOENIX_MOUSE_CLICK_EVENT_H
#define PHOENIX_MOUSE_CLICK_EVENT_H

#include "Input/MouseButton.h"
#include "Input/InputAction.h"
#include "Input/KeyModifier.h"

namespace Phoenix
{
	/*!
	 * \brief This contains mouse click info and is sent by the Mouse click Callback from FInput
	 */
	struct FMouseClickEvent
	{
		EMouseButton MouseButton = EMouseButton::Unknown;
		EInputAction InputAction = EInputAction::Unknown;
		//GLFW mouse events keep track of keyboard modifiers as well
		EKeyModifier KeyModifier = EKeyModifier::None; 

		FMouseClickEvent() = default;
	
		FMouseClickEvent(EMouseButton MouseButton, EInputAction	InputAction, EKeyModifier KeyModifier)
			: MouseButton(MouseButton)
			, InputAction(InputAction)
			, KeyModifier(KeyModifier)
		{}
	};
}

#endif
