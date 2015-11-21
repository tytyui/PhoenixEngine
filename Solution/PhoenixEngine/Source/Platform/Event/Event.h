#ifndef PHOENIX_EVENT_H
#define PHOENIX_EVENT_H

#include "Utility/Debug/Assert.h"
#include "Utility/Misc/Primitives.h"
#include "Utility/Misc/OutputStream.h"
#include "Platform/Event/EventTypes.h"
#include "Platform/Input/InputAction.h"
#include "Platform/Input/KeyMods.h"
#include "Platform/Input/Keys.h"
#include "Platform/Input/MouseButton.h"

namespace Phoenix
{
	struct FEventInfo
	{
		EEvent::TypeT Type;
		EEvent::SubTypeT SubType;
		Float32 TimeStamp;

		FEventInfo() = default;

		FEventInfo(
			const EEvent::TypeT InType, 
			const EEvent::SubTypeT InSubType);

		FEventInfo(
			const EEvent::TypeT InType,
			const EEvent::SubTypeT InSubType,
			const Float32 InTimeStamp);
	};

	struct FKeyEvent
	{
		FEventInfo Info;
		EKey::Value Key;
		EInputAction::Value Action;
		EKeyMods::BitMask Mods;

		FKeyEvent() = default;

		FKeyEvent(
			const EKeyEventType::Value SubType,
			const EKey::Value InKey,
			const EInputAction::Value InAction,
			const EKeyMods::BitMask InMods,
			const Float32 TimeStamp);
	};

	struct FMouseEvent
	{
		FEventInfo Info;
		EMouseButton::Value Button;
		EInputAction::Value Action;
		EKeyMods::BitMask Mods;

		FMouseEvent() = default;

		FMouseEvent(
			const EMouseEventType::Value SubType,
			const EMouseButton::Value InButton,
			const EInputAction::Value InAction,
			const EKeyMods::BitMask InMods,
			const Float32 TimeStamp);
	};

	struct FEvent
	{
		union
		{
			FEventInfo Info;
			FKeyEvent Key;
			FMouseEvent Mouse;
		};
	};

	static FOutputStream& operator<<(FOutputStream& LHS, const FEventInfo& RHS)
	{
		LHS << "Time: " << RHS.TimeStamp << ", Type: " << EEventType::ToString(RHS.Type) << ", SubType: " << RHS.SubType;
		return LHS;
	}

	static FOutputStream& operator<<(FOutputStream& LHS, const FKeyEvent& RHS)
	{
		// #FIXME
		return LHS;
	}

	static FOutputStream& operator<<(FOutputStream& LHS, const FMouseEvent& RHS)
	{
		// #FIXME
		return LHS;
	}

	static FOutputStream& operator<<(FOutputStream& LHS, const FEvent& RHS)
	{
		switch (RHS.Info.Type)
		{
			case EEventType::Key:
			{
				LHS << RHS.Key;
				break;
			}

			case EEventType::Mouse:
			{
				LHS << RHS.Mouse;
				break;
			}

			default:
			{
				LHS << RHS.Info;
				break;
			}
		}

		return LHS;
	}
}

#endif
