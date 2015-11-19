#ifndef PHOENIX_MOUSE_BUTTON_H
#define PHOENIX_MOUSE_BUTTON_H

#include "ExternalLib/GLFWIncludes.h"
#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	namespace EMouseButton
	{
		typedef UInt8 Type;

		enum Value : Type
		{
			Left = GLFW_MOUSE_BUTTON_LEFT,
			Right = GLFW_MOUSE_BUTTON_RIGHT,
			Middle = GLFW_MOUSE_BUTTON_MIDDLE,
			Button1 = GLFW_MOUSE_BUTTON_1,
			Button2 = GLFW_MOUSE_BUTTON_2,
			Button3 = GLFW_MOUSE_BUTTON_3,
			Button4 = GLFW_MOUSE_BUTTON_4,
			Button5 = GLFW_MOUSE_BUTTON_5,
			Button6 = GLFW_MOUSE_BUTTON_6,
			Button7 = GLFW_MOUSE_BUTTON_7,
			Button8 = GLFW_MOUSE_BUTTON_8,
			Count = GLFW_MOUSE_BUTTON_LAST + 1
		};

		static bool IsValid(const Type MouseButton)
		{
			const bool Result = MouseButton < EMouseButton::Count;
			return Result;
		}
	}
}

#endif
