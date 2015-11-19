#include "Platform/Event/Event.h"

using namespace Phoenix;


FEventInfo::FEventInfo(
	const EEvent::TypeT InType,
	const EEvent::SubTypeT InSubType)
	: FEventInfo(InType, InSubType, 0.f)
{
}

FEventInfo::FEventInfo(
	const EEvent::TypeT InType,
	const EEvent::SubTypeT InSubType,
	const Float32 InTimeStamp)
	: Type(InType)
	, SubType(InSubType)
	, TimeStamp(InTimeStamp)
{
}

FKeyEvent::FKeyEvent(
	const EKeyEventType::Value SubType,
	const EKey::Value InKey,
	const EInputAction::Value InAction,
	const EKeyMods::BitMask InMods,
	const Float32 TimeStamp)
	: Info(EEventType::Key, SubType, TimeStamp)
	, Key(InKey)
	, Action(InAction)
	, Mods(InMods)
{
}
