#ifndef PHOENIX_HANDLE_H
#define PHOENIX_HANDLE_H

#include "Utility/Debug/Assert.h"
#include "Utility/Debug/Debug.h"
#include "Utility/Handle/HandleData.h"
#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	template <class T>
	class THandle
	{
	public:
		THandle() = default;

		THandle(const THandle&);
		THandle& operator=(const THandle&);

		THandle(THandle&&);
		THandle& operator=(THandle&&);

		~THandle();

		void Init(THandlesData<T>* InHandleData, const SizeT InHIDataIndex);

		bool IsValid() const;

		void DeInit();

		SizeT GetRefCount() const;

		T& Get();

		const T& Get() const;

		T& operator*();

		const T& operator*() const;

		T* operator->();

		const T* operator->() const;

	protected:
	private:
		THandlesData<T>* HandleData{ nullptr };
		SizeT HIDataIndex{ 0 };

		template <bool AssertValidRefCount = true>
		THandleItemData<T>& GetHandleItemData();

		SizeT& GetRefCountReference();

		const SizeT& GetRefCountReference() const;

		void PostMoveReset();
	};

	template <class T>
	THandle<T>::THandle(const THandle<T>& RHS)
		: HandleData(RHS.HandleData)
		, HIDataIndex(RHS.HIDataIndex)
	{
		if (HandleData)
		{
			SizeT& RefCount = GetRefCountReference();
			++RefCount;
		}
	}

	template <class T>
	THandle<T>& THandle<T>::operator=(const THandle<T>& RHS)
	{
		F_Assert(this != &RHS, "Self assignment is illegal.");
		DeInit();

		HandleData = RHS.HandleData;
		HIDataIndex = RHS.HIDataIndex;

		if (HandleData)
		{
			SizeT& RefCount = GetRefCountReference();
			++RefCount;
		}

		return *this;
	}

	template <class T>
	THandle<T>::THandle(THandle<T>&& RHS)
		: HandleData(RHS.HandleData)
		, HIDataIndex(RHS.HIDataIndex)
	{
		RHS.PostMoveReset();
	}

	template <class T>
	THandle<T>& THandle<T>::operator=(THandle<T>&& RHS)
	{
		F_Assert(this != &RHS, "Self assignment is illegal.");
		DeInit();

		HandleData = RHS.HandleData;
		HIDataIndex = RHS.HIDataIndex;

		RHS.PostMoveReset();
		return *this;
	}

	template <class T>
	THandle<T>::~THandle()
	{
		DeInit();
	}

	template <class T>
	void THandle<T>::Init(THandlesData<T>* InHandleData, const SizeT InHIDataIndex)
	{
		DeInit();

		F_Assert(InHandleData, "InHandleData is null.");
		F_Assert(InHIDataIndex < InHandleData->HIData.size(), 
			"ID of " << InHIDataIndex << " is too large for container size of " << InHandleData->HIData.size());

		HandleData = InHandleData;
		HIDataIndex = InHIDataIndex;
	}

	template <class T>
	bool THandle<T>::IsValid() const
	{
		const bool Result = HandleData != nullptr;
		return Result;
	}

	template <class T>
	void THandle<T>::DeInit()
	{
		if (!HandleData)
		{
			return;
		}

		SizeT& ReferenceCount = GetRefCountReference();

		F_Assert(ReferenceCount > 0, 
			"When HandleData is not null, ReferenceCount should be at least 1.");
		--ReferenceCount;

		if (ReferenceCount == 0)
		{
			F_Assert(HandleData->Data.size(), "A non-zero size was expected.");

			THandleItemData<T>& HIData = GetHandleItemData<false>();

			const SizeT CurrentDataIndex = HIData.DataIndex;
			const SizeT LastDataIndex = HandleData->Data.size() - 1;

			F_Assert(CurrentDataIndex <= LastDataIndex,
				CurrentDataIndex << " is higher than the container size of " << LastDataIndex);

			F_DebugCode(bool IsIndexFree = false);
			if (CurrentDataIndex != LastDataIndex)
			{
				HandleData->Data[CurrentDataIndex] = std::move(HandleData->Data[LastDataIndex]);
				const SizeT HIDataSize = HandleData->HIData.size();

				// #FIXME: Best Case: O(1), Worst Case: O(N), Avg: O(N / 2).  Improve this.
				for (SizeT I = 0; I < HIDataSize; ++I)
				{
					THandleItemData<T>& Item = HandleData->HIData[I];

					const bool ItemWasInLastSlot = Item.DataIndex == LastDataIndex;
					if (ItemWasInLastSlot)
					{
						F_DebugCode(F_Assert(!IsIndexFree, "Index is being set twice."));
						F_DebugCode(IsIndexFree = true);

						HandleData->HIData[HIDataIndex] = THandleItemData<T>();
						Item.DataIndex = CurrentDataIndex;
						F_DebugCode(continue);
						break;
					}
				}
			}

			HandleData->UnusedHIData.push_back(HIDataIndex);
			HandleData->Data.pop_back();
		}

		HandleData = nullptr;
		HIDataIndex = 0;
	}

	template <class T>
	T& THandle<T>::Get()
	{
		THandleItemData<T>& HIData = GetHandleItemData();
		T& Item = HandleData->Data[HIData.DataIndex];
		return Item;
	}

	template <class T>
	SizeT THandle<T>::GetRefCount() const
	{
		const SizeT RefCount = GetRefCountReference();
		return RefCount;
	}

	template <class T>
	const T& THandle<T>::Get() const
	{
		THandleItemData<T>& HIData = GetHandleItemData();
		T& Item = HandleData->Data[HIData.DataIndex];
		return Item;
	}

	template <class T>
	T& THandle<T>::operator*()
	{
		T& Item = Get();
		return Item;
	}

	template <class T>
	const T& THandle<T>::operator*() const
	{
		const T& Item = Get();
		return Item;
	}

	template <class T>
	T* THandle<T>::operator->()
	{
		THandleItemData<T>& HIData = GetHandleItemData();
		T* const Item = &HandleData->Data[HIData.DataIndex];
		return Item;
	}

	template <class T>
	const T* THandle<T>::operator->() const
	{
		THandleItemData<T>& HIData = GetHandleItemData();
		const T* const Item = &HandleData->Data[HIData.DataIndex];
		return Item;
	}

	template <class T>
	template <bool AssertValidRefCount>
	THandleItemData<T>& THandle<T>::GetHandleItemData()
	{
		F_Assert(IsValid(), "Handle is not valid.");
		THandleItemData<T>& HIData = HandleData->HIData[HIDataIndex];

		if (AssertValidRefCount)
		{
			F_Assert(HIData.RefCount > 0, 
				"Invalid reference count of " << HIData.RefCount);
		}

		return HIData;
	}

	template <class T>
	SizeT& THandle<T>::GetRefCountReference()
	{
		F_Assert(IsValid(), "Handle is not valid.");
		THandleItemData<T>& HIData = HandleData->HIData[HIDataIndex];
		return HIData.RefCount;
	}

	template <class T>
	const SizeT& THandle<T>::GetRefCountReference() const
	{
		F_Assert(IsValid(), "Handle is not valid.");
		THandleItemData<T>& HIData = HandleData->HIData[HIDataIndex];
		return HIData.RefCount;
	}

	template <class T>
	void THandle<T>::PostMoveReset()
	{
		HandleData = nullptr;
		HIDataIndex = 0;
	}
}

#endif
