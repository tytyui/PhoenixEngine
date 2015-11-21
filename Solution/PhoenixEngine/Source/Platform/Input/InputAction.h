#ifndef PHOENIX_INPUT_ACTION_H
#define PHOENIX_INPUT_ACTION_H

#include "ExternalLib/GLFWIncludes.h"
#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	namespace EInputAction
	{
		typedef UInt8 Type;

		enum Value : Type
		{
			Release = GLFW_RELEASE, 
			Press = GLFW_PRESS,
			Repeat = GLFW_REPEAT,
			Count = 3
		};

		static bool IsValid(const Type InputAction)
		{
			const bool Result = InputAction < EInputAction::Count;
			return Result;
		}
	}
}
#endif
