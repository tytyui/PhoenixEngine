#ifndef PHOENIX_TIMER_H
#define PHOENIX_TIMER_H

#include <chrono>
#include <numeric>
#include <type_traits>

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
		T GetTimeInSeconds();

	protected:
	private:
		typedef std::chrono::high_resolution_clock ClockT;
		typedef std::chrono::high_resolution_clock::time_point TimeStampT;
		template <class T>
		using TDuration = std::chrono::duration<T>;

		TimeStampT PreviousTime;
		TimeStampT CurrentTime;
	};

	typedef FHighResolutionTimer FHighResTimer;

	inline void FHighResolutionTimer::Reset()
	{
		const TimeStampT TimeStamp = ClockT::now();

		PreviousTime = TimeStamp;
		CurrentTime = TimeStamp;
	}

	inline void FHighResolutionTimer::Update()
	{
		const TimeStampT TimeStamp = ClockT::now();

		PreviousTime = CurrentTime;
		CurrentTime = TimeStamp;
	}

	template <class T>
	T FHighResolutionTimer::GetDeltaSeconds()
	{
		static_assert(std::is_floating_point<T>::value, "This template must be a floating point type.");
		using namespace std::chrono;

		const TDuration<T> Duration = duration_cast<TDuration<T>>(CurrentTime - PreviousTime);

		const T DeltaSeconds = Duration.count();
		return DeltaSeconds;
	}

	template <class T>
	T FHighResolutionTimer::GetTimeInSeconds()
	{
		static_assert(std::is_floating_point<T>::value, "This template must be a floating point type.");

		const TimeStampT TimeStamp = ClockT::now();
		const TDuration<T> Duration = TimeStamp.time_since_epoch();

		const T TimeInSeconds = Duration.count();
		return TimeInSeconds;
	}
}

#endif
