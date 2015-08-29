#ifndef PHOENIX_MUTEX_H
#define PHOENIX_MUTEX_H

#include <mutex>

namespace Phoenix
{
	using FMutex = std::mutex;
	using FTimedMutex = std::timed_mutex;

	template <class T>
	using TLockGuard = std::lock_guard<T>;

	template <class T>
	using TUniqueLock = std::unique_lock<T>;

	using FMutexLock = TLockGuard<FMutex>;
	using FTimedMutexLock = TLockGuard<FTimedMutex>;
}

#endif
