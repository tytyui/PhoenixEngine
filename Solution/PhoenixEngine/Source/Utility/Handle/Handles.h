#ifndef PHOENIX_HANDLES_H
#define PHOENIX_HANDLES_H

#include "Utility/Debug/Debug.h"
#include "Utility/Handle/Handle.h"
#include "Utility/Handle/HandleData.h"

namespace Phoenix
{
	template <class T>
	class THandles : private THandlesData<T>
	{
	public:
		typedef THandle<T> HandleT;

		THandles() = default;

		THandles(const THandles&) = delete;
		THandles& operator=(const THandles&) = delete;

		THandles(THandles&&) = delete;
		THandles& operator=(THandles&&) = delete;

		template <class... Arguments>
		THandle<T> CreateHandle(Arguments&&... Args);

		TVector<T>& GetData();
		
		const TVector<T>& GetData() const;

		SizeT GetDataSize() const;

		T& operator[](const SizeT Index);

		const T& operator[](const SizeT Index) const;

	protected:
	private:
	};

	template <class T>
	template <class... Arguments>
	THandle<T> THandles<T>::CreateHandle(Arguments&&... Args)
	{
		THandle<T> Handle;

		const SizeT DataIndex = Data.size();
		Data.push_back(T(std::forward<Arguments>(Args)...));

		const SizeT UnusedHIDataSize = UnusedHIData.size();

		const bool CanReuseHIData = UnusedHIDataSize != 0;
		if (CanReuseHIData)
		{
			const SizeT HIDataIndex = UnusedHIData[UnusedHIDataSize - 1];
			UnusedHIData.pop_back();
			
			THandleItemData<T>& ReusedHIData = HIData[HIDataIndex];
			
			ReusedHIData.DataIndex = DataIndex;
			ReusedHIData.RefCount = 1;

			Handle.Init(this, HIDataIndex);
			return Handle;
		}

		THandleItemData<T> NewHIData;

		NewHIData.DataIndex = DataIndex;
		NewHIData.RefCount = 1;

		const SizeT HIDataIndex = HIData.size();
		HIData.push_back(NewHIData);

		Handle.Init(this, HIDataIndex);
		return Handle;
	}

	template <class T>
	TVector<T>& THandles<T>::GetData()
	{
		return Data;
	}

	template <class T>
	const TVector<T>& THandles<T>::GetData() const
	{
		return Data;
	}

	template <class T>
	SizeT THandles<T>::GetDataSize() const
	{
		const SizeT DataSize = Data.size();
		return DataSize;
	}

	template <class T>
	T& THandles<T>::operator[](const SizeT Index)
	{
		T& Item = Data[Index];
		return Item;
	}

	template <class T>
	const T& THandles<T>::operator[](const SizeT Index) const
	{
		const T& Item = Data[Index];
		return Item;
	}
}

#endif
