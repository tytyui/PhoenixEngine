#ifndef PHOENIX_HANDLE_DATA_H
#define PHOENIX_HANDLE_DATA_H

#include "Utility/Containers/Vector.h"
#include "Utility/Misc/Primitives.h"

#undef max

namespace Phoenix
{
	template <class T>
	struct THandleItemData
	{
		SizeT DataIndex{ TNumericLimits<SizeT>::max() };
		SizeT RefCount{ 0 };
	};

	template <class T>
	struct THandlesData
	{
		TVector<T> Data;
		TVector<THandleItemData<T>> HIData;
		TVector<SizeT> UnusedHIData;
	};
}

#endif
