#ifndef PHOENIX_EVENT_H
#define PHOENIX_EVENT_H

#include "Utility/Misc/Primitives.h"
#include "Platform/Event/EventTypes.h"
#include "Platform/Input/InputAction.h"
#include "Platform/Input/KeyMods.h"
#include "Platform/Input/Keys.h"

namespace Phoenix
{
	struct FEventInfo
	{
		friend struct FEvent;

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

	struct FEvent
	{
		union
		{
			FEventInfo Info;
			FKeyEvent Key;
		};
	};
}

#endif
