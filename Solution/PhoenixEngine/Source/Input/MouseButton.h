#ifndef PHOENIX_MOUSE_BUTTON_H
#define PHOENIX_MOUSE_BUTTON_H

#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	enum class EMouseButton : Int32
	{
		Left = 0,
		Right = 1,
		Middle = 2,
		Button4 = 3,
		Button5 = 4,
		Button6 = 5,
		Button7 = 6,
		Button8 = 7,
		Button9 = 8,

		Unknown = -1
	};
}

#endif
