#ifndef PHOENIX_KEY_MODS_H
#define PHOENIX_KEY_MODS_H

#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	/*!
	 * \brief Flags for modifiers that were active during a FKeyEvent.
	 */
	namespace EKeyMods
	{
		typedef UInt8 Type;

		enum BitMask : Type
		{
			None,
			Shift = 1 << 0,
			Control = 1 << 1,
			Alt = 1 << 2,
			All = Shift | Control | Alt
		};

		static bool IsValid(const Type KeyMods)
		{
			const bool Result = KeyMods <= EKeyMods::All;
			return Result;
		}
	}
}

#endif
