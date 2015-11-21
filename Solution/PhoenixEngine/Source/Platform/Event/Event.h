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
		friend struct FEvent;
		friend struct FKeyEvent;
		friend struct FMouseEvent;

		EEvent::TypeT Type;
		EEvent::SubTypeT SubType;
		Float32 TimeStamp;

		FEventInfo(
			const EEvent::TypeT InType,
			const EEvent::SubTypeT InSubType);

		FEventInfo(
			const EEvent::TypeT InType,
			const EEvent::SubTypeT InSubType,
			const Float32 InTimeStamp);

	private:
		FEventInfo() = default;
	};

	struct FKeyEvent
	{
		friend struct FEvent;

		FEventInfo Info;
		EKey::Value Key;
		EInputAction::Value Action;
		EKeyMods::BitMask Mods;

		FKeyEvent(
			const EKeyEventType::Value SubType,
			const EKey::Value InKey,
			const EInputAction::Value InAction,
			const EKeyMods::BitMask InMods,
			const Float32 TimeStamp);

	private:
		FKeyEvent() = default;
	};

	struct FMouseEvent
	{
		friend struct FEvent;

		FEventInfo Info;
		EMouseButton::Value Button;
		EInputAction::Value Action;
		EKeyMods::BitMask Mods;

		FMouseEvent(
			const EMouseEventType::Value SubType,
			const EMouseButton::Value InButton,
			const EInputAction::Value InAction,
			const EKeyMods::BitMask InMods,
			const Float32 TimeStamp);
	
	private:
		FMouseEvent() = default;
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
