#ifndef PHOENIX_INPUT_ACTION_H
#define PHOENIX_INPUT_ACTION_H

#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	enum class EInputAction : Int32
	{
		Release = 0,
		Press = 1,
		Hold = 2,
		Unknown = -1
	};
}
#endif
