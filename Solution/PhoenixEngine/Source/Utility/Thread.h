#ifndef PHOENIX_THREAD_H
#define PHOENIX_THREAD_H

#include <chrono>
#include <thread>

#include "Utility/Primitives.h"

namespace Phoenix
{
	typedef std::thread FThread;

	namespace FThr // FIXME: Come up with a solid naming convention.
	{
		//	--------------------------------------------------------------------------------
		/*! \brief Puts the thread to sleep for an approximate duration. */
		static inline void SleepThread(const UInt32 Milliseconds)
		{
			const std::chrono::milliseconds Duration(Milliseconds);
			std::this_thread::sleep_for(Duration);
		}
	}
}

#endif
