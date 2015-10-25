#ifndef PHOENIX_TIMER_H
#define PHOENIX_TIMER_H

#include <chrono>
#include <numeric>
#include <type_traits>

#include "ExternalLib/GLFWIncludes.h"

namespace Phoenix
{
	struct FHighResolutionTimer
	{
	public:
		void Reset();

		void Update();

		template <class T>
		T GetDeltaSeconds();

		template <class T>
		static T GetTimeInSeconds();

	protected:
	private:
		typedef Float64 TimeStampT;

		TimeStampT PreviousTime{ 0 };
		TimeStampT CurrentTime{ 0 };
	};
	
	inline void FHighResolutionTimer::Reset()
	{
		const TimeStampT TimeStamp = glfwGetTime();

		PreviousTime = TimeStamp;
		CurrentTime = TimeStamp;
	}

	inline void FHighResolutionTimer::Update()
	{
		const TimeStampT TimeStamp = glfwGetTime();

		PreviousTime = CurrentTime;
		CurrentTime = TimeStamp;
	}

	template <class T>
	T FHighResolutionTimer::GetDeltaSeconds()
	{
		static_assert(std::is_floating_point<T>::value, "This template must be a floating point type.");

		const T DeltaSeconds = static_cast<T>(CurrentTime - PreviousTime);
		return DeltaSeconds;
	}

	template <class T>
	T FHighResolutionTimer::GetTimeInSeconds()
	{
		static_assert(std::is_floating_point<T>::value, "This template must be a floating point type.");

		const T TimeInSeconds = static_cast<T>(glfwGetTime());
		return TimeInSeconds;
	}
}

#endif
