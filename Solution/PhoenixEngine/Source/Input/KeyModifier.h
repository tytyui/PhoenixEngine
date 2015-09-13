#ifndef PHOENIX_KEY_MODIFIER_H
#define PHOENIX_KEY_MODIFIER_H

#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	/*!
	 * \brief Flags for modifiers that were active during an Input Event
	 */
	enum class EKeyModifier : Int32
	{
		None = 0x0000,
		Shift = 0x0001,
		Control = 0x0002,
		Alt = 0x0004
	};

	inline constexpr EKeyModifier operator | (EKeyModifier LHS, EKeyModifier RHS)
	{
		return static_cast<EKeyModifier>(static_cast<Int32>(LHS) | static_cast<Int32>(RHS));
	}

	inline EKeyModifier& operator |= (EKeyModifier& LHS, EKeyModifier RHS)
	{
		LHS = LHS | RHS;
		return LHS;
	}
}

#endif
