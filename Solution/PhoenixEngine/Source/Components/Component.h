#pragma once
#include <string>
#include <vector>
#include <assert.h>
#include "Utility/Misc/ClassTypeId.h"

namespace Phoenix
{
	class BaseComponent
	{
	public:
		int OwnerID;
		class ComponentStorage* Storage;
		class FGameScene* GameScene;

		BaseComponent() = default;
		~BaseComponent() = default;
		virtual void Init() = 0;
	};

	template<typename T>
	class Component
		: public BaseComponent
	{
	public:

		static TypeId GetTypeId()
		{
			return ClassTypeId<BaseComponent>::GetTypeId<T>();
		}

		// Each component must update each loop
		virtual void Update(float dt)
		{
		}
	};
	typedef std::vector<std::reference_wrapper<BaseComponent>> ComponentArray;
}