#ifndef PHOENIX_NAMED_ITEM_CACHE_H
#define PHOENIX_NAMED_ITEM_CACHE_H

#include "Utility/Containers/Array.h"
#include "Utility/Containers/UnorderedMap.h"
#include "Utility/Handle/Handles.h"
#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	template <class T>
	class TNamedItemCache
	{
	public:
		typedef FString KeyT;
		typedef T ValueT;

		bool AddEntry(const KeyT& Key, const ValueT& Value);

		bool AddEntry(KeyT&& Key, ValueT&& Value);

		void Clear();

		T* GetItem(const KeyT& Key);

		const T* GetItem(const KeyT& Key) const;

		bool HasItem(const KeyT& Key) const;

		SizeT GetItemCount() const;

		bool RemoveItem(const KeyT& Key);

	protected:
	private:
		typedef TUnorderedMap<KeyT, ValueT> ItemsT;

		ItemsT Items;
	};

	template <class T>
	bool TNamedItemCache<T>::AddEntry(const KeyT& Key, const ValueT& Value)
	{
		const auto Pair = Items.try_emplace(Key, Value);
		const bool WasEntryAdded = Pair.second;
		return WasEntryAdded;
	}

	template <class T>
	bool TNamedItemCache<T>::AddEntry(KeyT&& Key, ValueT&& Value)
	{
		const auto Pair = Items.try_emplace(std::move(Key), std::move(Value));
		const bool WasEntryAdded = Pair.second;
		return WasEntryAdded;
	}

	template <class T>
	void TNamedItemCache<T>::Clear()
	{
		Items.clear();
	}

	template <class T>
	T* TNamedItemCache<T>::GetItem(const KeyT& Key)
	{
		const auto Iter = Items.find(Key);
		const bool WasItemFound = Iter != Items.end();

		if (WasItemFound)
		{
			T* const Value = &Iter->second;
			return Value;
		}

		return nullptr;
	}

	template <class T>
	const T* TNamedItemCache<T>::GetItem(const KeyT& Key) const
	{
		const auto Iter = Items.find(Key);
		const bool WasItemFound = Iter != Items.end();

		if (WasItemFound)
		{
			const T* const Value = &Iter->second;
			return Value;
		}

		return nullptr;
	}

	template <class T>
	bool TNamedItemCache<T>::HasItem(const KeyT& Key) const
	{
		const auto Iter = Items.find(Key);
		const bool WasItemFound = Iter != Items.end();
		return WasItemFound;
	}

	template <class T>
	SizeT TNamedItemCache<T>::GetItemCount() const
	{
		const SizeT ItemCount = Items.size();
		return ItemCount;
	}

	template <class T>
	bool TNamedItemCache<T>::RemoveItem(const KeyT& Key)
	{
		const auto Iter = Items.erase(Key);
		const bool WasItemRemoved = Iter == 1;
		return WasItemRemoved;
	}
}

#endif

