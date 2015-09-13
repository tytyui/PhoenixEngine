#ifndef PHOENIX_THREAD_SAFE_VECTOR_H
#define PHOENIX_THREAD_SAFE_VECTOR_H

#include "Utility/Containers/Vector.h"
#include "Utility/Misc/Primitives.h"
#include "Utility/Threading/Mutex.h"

namespace Phoenix
{
	template <class T>
	class TThreadSafeVector
	{
	public:
		typedef TVector<T> ContainerT;

		TThreadSafeVector() = default;

		TThreadSafeVector(const TThreadSafeVector&) = delete;
		TThreadSafeVector& operator=(const TThreadSafeVector&) = delete;

		TThreadSafeVector(TThreadSafeVector&&) = delete;
		TThreadSafeVector& operator=(TThreadSafeVector&&) = delete;

		void Clear();

		void Empty();

		void AddEntry(const T& AddedEntry);

		void AddEntry(T&& AddedEntry);

		void AddData(const ContainerT& AddedData);

		void AddData(ContainerT&& MovedData);

		void Reserve(const SizeT Size);

		void Resize(const SizeT Size);

		void GetDataAndClear(ContainerT& OutItems);

		SizeT GetCapacity();

		SizeT GetSize();

	private:
		FMutex Lock;
		ContainerT Data;
	};

	template <class T>
	void TThreadSafeVector<T>::Clear()
	{
		FMutexLock Guard(Lock);
		Data.clear();
	}

	template <class T>
	void TThreadSafeVector<T>::Empty()
	{
		FMutexLock Guard(Lock);
		Data = std::move(ContainerT());
	}

	template <class T>
	void TThreadSafeVector<T>::AddEntry(const T& AddedEntry)
	{
		FMutexLock Guard(Lock);
		Data.push_back(AddedEntry);
	}

	template <class T>
	void TThreadSafeVector<T>::AddEntry(T&& AddedEntry)
	{
		FMutexLock Guard(Lock);
		Data.push_back(std::move(AddedEntry));
	}

	template <class T>
	void TThreadSafeVector<T>::AddData(const ContainerT& AddedData)
	{
		FMutexLock Guard(Lock);

		for (const auto& Entry : AddedData)
		{
			Data.push_back(Entry);
		}
	}

	template <class T>
	void TThreadSafeVector<T>::AddData(ContainerT&& MovedData)
	{
		FMutexLock Guard(Lock);

		for (auto& Entry : MovedData)
		{
			Data.push_back(std::move(Entry));
		}
	}

	template <class T>
	void TThreadSafeVector<T>::Reserve(const SizeT Size)
	{
		FMutexLock Guard(Lock);
		Data.reserve(Size);
	}

	template <class T>
	void TThreadSafeVector<T>::Resize(const SizeT Size)
	{
		FMutexLock Guard(Lock);
		Data.resize(Size);
	}

	template <class T>
	void TThreadSafeVector<T>::GetDataAndClear(ContainerT& OutItems)
	{
		FMutexLock Guard(Lock);

		for (auto& Entry : Data)
		{
			OutItems.push_back(std::move(Entry));
		}

		Data.clear();
	}

	template <class T>
	SizeT TThreadSafeVector<T>::GetCapacity()
	{
		FMutexLock Guard(Lock);
		const SizeT Capacity = Data.capacity();
		return Capacity;
	}

	template <class T>
	SizeT TThreadSafeVector<T>::GetSize()
	{
		FMutexLock Guard(Lock);
		const SizeT Size = Data.size();
		return Size;
	}
}

#endif
