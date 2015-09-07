#ifndef PHOENIX_CONSOLE_COLOR_H
#define PHOENIX_CONSOLE_COLOR_H

#if _WIN32
#include <windows.h> 
#endif

#include "Utility/Containers/Array.h"
#include "Utility/Debug/Assert.h"
#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	namespace EConsoleColor
	{
		typedef UInt8 Type;

		enum Value : Type
		{
			White,
			Grey,
			Red,
			Green,
			Blue,
			Yellow,
			Pink,
			LightBlue,
			Count,
		};
	}

	struct FConsoleColor
	{
	public:
		explicit FConsoleColor(const EConsoleColor::Value InColor);

		bool IsValid() const;

		static void Set(const FConsoleColor Color);

	protected:
	private:
		EConsoleColor::Value Color{ EConsoleColor::White };
	};

	inline FConsoleColor::FConsoleColor(const EConsoleColor::Value InColor)
		: Color(InColor)
	{
		F_Assert(IsValid(), "This class must be valid.");
	}

	inline bool FConsoleColor::IsValid() const
	{
		const bool bIsValid = Color < EConsoleColor::Count;
		return bIsValid;
	}

	inline void FConsoleColor::Set(const FConsoleColor Color)
	{
#if _WIN32
		F_Assert(Color.IsValid(), "ConsoleColor must be valid.");
		static_assert(EConsoleColor::Count == 8, "This table requires updating.");
		static const TArray<WORD, EConsoleColor::Count> LookUpTable = {
			/* White		*/FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
			/* Grey			*/0,
			/* Red			*/FOREGROUND_RED,
			/* Green		*/FOREGROUND_GREEN,

			/* Blue			*/FOREGROUND_BLUE,
			/* Yellow		*/FOREGROUND_RED | FOREGROUND_GREEN,
			/* Pink			*/FOREGROUND_RED | FOREGROUND_BLUE,
			/* LightBlue	*/FOREGROUND_GREEN | FOREGROUND_BLUE,
		};

		/* Ref: https://msdn.microsoft.com/en-us/library/windows/desktop/ms683231%28v=vs.85%29.aspx */
		HANDLE const Handle = GetStdHandle(STD_OUTPUT_HANDLE);
		const WORD Attributes = LookUpTable[Color.Color] | FOREGROUND_INTENSITY;
		/* Ref: https://msdn.microsoft.com/en-us/library/windows/desktop/ms686047%28v=vs.85%29.aspx */
		SetConsoleTextAttribute(Handle, Attributes);
#endif
	}
}

#endif
