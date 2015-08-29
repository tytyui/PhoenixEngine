#ifndef PHOENIX_MEMORY_H
#define PHOENIX_MEMORY_H

#include <memory>

namespace Phoenix
{
	template<class T>
	using TUniquePtr = std::unique_ptr<T>;

	template <class T>
	using TSharedPtr = std::shared_ptr<T>;

	template <class T>
	using TWeakPtr = std::weak_ptr<T>;
}
#endif
