#ifndef PHOENIX_MEMORY_H_
#define PHOENIX_MEMORY_H_

#include <memory>

namespace Phoenix
{
	template<class T>
	using TUnique = std::unique_ptr<T>;
}
#endif // PHOENIX_MEMORY_H_
