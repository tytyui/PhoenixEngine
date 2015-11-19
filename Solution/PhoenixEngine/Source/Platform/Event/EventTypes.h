#ifndef PHOENIX_EVENT_TYPES_H
#define PHOENIX_EVENT_TYPES_H

#include "Utility/Containers/Array.h"
#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	namespace EEvent
	{
		typedef UInt16 TypeT;
		typedef UInt16 SubTypeT;
	}

	namespace EEventType
	{
		typedef EEvent::TypeT Type;

		enum Value : Type
		{
			Unknown,
			Cursor,
			Engine,
			Key,
			Mouse,
			User,
			Window,
			Count
		};

		static const FChar* const ToString(const Type EventType)
		{
			static_assert(EEventType::Count == 7, "This table requires updating.");
			static const TArray<const FChar* const, EEventType::Count> LookUpTable = 
			{
				"Unknown",
				"Cursor",
				"Engine",
				"Key",
				"Mouse",
				"User",
				"Window",
			};

			const FChar* const Result = LookUpTable[EventType];
			return Result;
		}
	}

	namespace ECursorEventType
	{
		typedef EEvent::SubTypeT Type;

		enum Value : Type
		{
			Enter,
			Leave,
			Position,
			Count
		};
	}

	namespace EEngineEventType
	{
		typedef EEvent::SubTypeT Type;

		enum Value : Type
		{
			ShutDownNow,
			IsShutDown,
			Count
		};
	}

	namespace EKeyEventType
	{
		typedef EEvent::SubTypeT Type;

		enum Value : Type
		{
			Default,
			Count
		};
	}

	namespace EMouseEventType
	{
		typedef EEvent::SubTypeT Type;

		enum Value : Type
		{
			Down,
			Scroll,
			Up,
		};
	}

	namespace EWindowEventType
	{
		typedef EEvent::SubTypeT Type;

		enum Value : Type
		{
			CloseAttempt,
			FocusGained,
			FocusLost,
			FrameBufferResized,
			Restored,
			Iconified,
			PositionChanged,
			Refreshed,
			SizeChanged,
			Count
		};
	}
}

#endif
