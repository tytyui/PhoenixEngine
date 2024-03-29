#pragma once
#include "Components/Component.h"
#include "Math/Vector3D.h"

namespace Phoenix
{
	class Transform :
		public Component<Transform>
	{
	public:
		FVector3D Position;
		FVector3D Scale;
		FVector3D Rotation;

		float Angle;

		Transform();
		virtual ~Transform();

		// Separate init from construction code.
		virtual void Init() final;

		void SetPosition(const FVector3D& InPosition);
	};
}