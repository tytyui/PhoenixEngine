#ifndef PHOENIX_CAMERA_H
#define PHOENIX_CAMERA_H

#include "Utility/Misc/Primitives.h"
#include "Math/Matrix4D.h"
#include "Math/Vector3D.h"

namespace Phoenix
{
	struct FCamera
	{
	public:
		static const FVector3D DefaultDirection;
		static const FVector3D DefaultUpVector;

		FCamera() = default;

		void SetPerspective(
			const Float32 FieldOfView,
			const Float32 AspectRatio,
			const Float32 Near,
			const Float32 Far);

		void SetOrthographic(
			const Float32 Left,
			const Float32 Right,
			const Float32 Bottom,
			const Float32 Top);

		void SetPosition(const FVector3D& InPosition);

		void SetDirection(const FVector3D& InDirection);

		void SetLookAtTarget(const FVector3D& Target);

		void SetUpVector(const FVector3D& InUpVector);

		void UpdateViewMatrix();

		const FMatrix4D& GetProjection() const;

		const FMatrix4D& GetView() const;

		const FVector3D& GetPosition() const;

		const FVector3D& GetDirection() const;

		const FVector3D& GetUpVector() const;

		const Float32* const GetProjectionPtr() const;

		const Float32* const GetViewPtr() const;

	protected:
	private:
		FMatrix4D Projection;
		FMatrix4D View;
		FVector3D Position;
		FVector3D Direction{ FCamera::DefaultDirection };
		FVector3D UpVector{ FCamera::DefaultUpVector };
	};
}

#endif
