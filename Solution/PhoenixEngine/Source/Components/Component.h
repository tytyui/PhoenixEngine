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
		__int32 OwnerID;
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

		template<typename T>
		bool GetComponent(T* OutComponentHandle)
		{
			OutComponentHandle = static_cast<T*>(&Storage->GetComponentById(OwnerID, T::GetTypeId()));
			return (OutComponentHandle != nullptr);
		}

		template<typename T>
		T* RequireComponent()
		{
			BaseComponent* TComponent = &Storage->GetComponentById(OwnerID, T::GetTypeId());
			if (!TComponent)
			{
				assert("Expected component T");
			}
			return static_cast<T*>(TComponent);
		}

		// Each component must update each loop
		virtual void Update(float dt)
		{
		}
	};
	typedef std::vector<std::reference_wrapper<BaseComponent>> ComponentArray;
}