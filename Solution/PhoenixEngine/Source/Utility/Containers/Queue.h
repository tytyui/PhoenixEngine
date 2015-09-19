#ifndef PHOENIX_QUEUE_H
#define PHOENIX_QUEUE_H

#include <queue>

namespace Phoenix
{
	template <class T, class Container>
	using TQueue = std::queue<T, Container>;
}

#endif
