#ifndef PHOENIX_THREAD_H
#define PHOENIX_THREAD_H

#include <chrono>
#include <thread>

#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	typedef std::thread FThread;

	namespace FThr // #FIXME: Come up with a solid naming convention.
	{
		//	--------------------------------------------------------------------------------
		/*! \brief Puts the thread to sleep for an approximate duration. */
		static inline void SleepThread(const UInt32 Milliseconds)
		{
			const std::chrono::milliseconds Duration(Milliseconds);
			std::this_thread::sleep_for(Duration);
		}
	}

	//#FIXME Find a good name for this
	class FThreadRAII
	{
	public:
		FThreadRAII() = default;
		//Intentionally non explicit - so it can be constructed directly from an FThread
		FThreadRAII(FThread&& Thread);

		FThreadRAII(const FThreadRAII&) = delete;
		FThreadRAII& operator=(const FThreadRAII&) = delete;

		FThreadRAII(FThreadRAII&&) = default;
		FThreadRAII& operator=(FThreadRAII&&) = default;

		~FThreadRAII();

		//Can be removed if we wrap *everthing* in std::thread
		FThread& Get();

		void Join();

	private:
		FThread Thread;
	};
}

#endif
