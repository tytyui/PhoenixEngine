#ifndef PHOENIX_IMAGE_CACHE_H
#define PHOENIX_IMAGE_CACHE_H

#include "Utility/Containers/NamedItemCache.h"
#include "Utility/Handle/Handle.h"
#include "Rendering/Image.h"

namespace Phoenix
{
	class FImageCache : public TNamedItemCache<THandle<FImage>>
	{
	};
}

#endif
